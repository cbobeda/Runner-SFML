#include "LevelGenerator.h"


using Complex = std::complex<double>;
const double PI = 3.14159265358979323846;

// ----------------- utilities -----------------
static inline bool isPowerOfTwo(std::size_t x) {
    return x && ((x & (x - 1)) == 0);
}

static std::size_t previousPowerOfTwo(std::size_t x) {
    if (x == 0) return 0;
    std::size_t p = 1;
    while (p * 2 <= x) p *= 2;
    return p;
}

// In-place radix-2 Cooley-Tukey FFT
static void fft(std::vector<Complex>& a) {
    const std::size_t n = a.size();
    if (n <= 1) return;
    // bit reversal
    std::size_t j = 0;
    for (std::size_t i = 1; i < n; ++i) {
        std::size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (std::size_t len = 2; len <= n; len <<= 1) {
        double ang = 2.0 * PI / (double)len;
        Complex wlen(std::cos(ang), std::sin(ang));
        for (std::size_t i = 0; i < n; i += len) {
            Complex w(1.0, 0.0);
            for (std::size_t k = 0; k < len / 2; ++k) {
                Complex u = a[i + k];
                Complex v = a[i + k + len / 2] * w;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
}

// Hann window generator
static std::vector<double> makeHann(std::size_t N) {
    std::vector<double> w(N);
    if (N == 0) return w;
    for (std::size_t n = 0; n < N; ++n) {
        w[n] = 0.5 * (1.0 - std::cos(2.0 * PI * n / (N - 1)));
    }
    return w;
}

// Parabolic interpolation for peak refinement
static double parabolicInterpolation(const std::vector<double>& mags, std::size_t k) {
    if (k == 0 || k + 1 >= mags.size()) return static_cast<double>(k);
    double alpha = mags[k - 1];
    double beta = mags[k];
    double gamma = mags[k + 1];
    double denom = (alpha - 2.0 * beta + gamma);
    if (std::abs(denom) < 1e-12) return static_cast<double>(k);
    double p = 0.5 * (alpha - gamma) / denom;
    return static_cast<double>(k) + p;
}

// Convert interleaved int16 samples to mono normalized [-1,1], optional start frame
static std::vector<double> interleavedToMonoFloat(const std::vector<std::int16_t>& interleaved, unsigned int channels, std::size_t startFrame = 0)
{
    std::vector<double> mono;
    if (channels == 0) return mono;
    std::size_t totalSamples = interleaved.size();
    if (totalSamples < channels) return mono;
    std::size_t totalFrames = totalSamples / channels;
    if (startFrame >= totalFrames) return mono;

    std::size_t framesToCopy = totalFrames - startFrame;
    mono.resize(framesToCopy);
    for (std::size_t f = 0; f < framesToCopy; ++f) {
        std::size_t srcFrame = startFrame + f;
        if (channels == 1) {
            mono[f] = static_cast<double>(interleaved[srcFrame]) / 32768.0;
        }
        else {
            double sum = 0.0;
            for (unsigned int c = 0; c < channels; ++c) {
                sum += static_cast<double>(interleaved[srcFrame * channels + c]);
            }
            mono[f] = (sum / static_cast<double>(channels)) / 32768.0;
        }
    }
    return mono;
}

// ----------------- CSV helpers -----------------
static bool writeSpectrogramCSV(const std::string& filename,
    const std::vector<double>& times,
    const std::vector<double>& freqBins,
    const std::vector<std::vector<double>>& mags)
{
    std::ofstream ofs(filename, std::ios::out);
    if (!ofs) return false;
    ofs << std::setprecision(6) << std::fixed;
    // header: time, bin0_freq, bin1_freq, ...
    ofs << "time";
    for (double fb : freqBins) {
        ofs << "," << fb;
    }
    ofs << "\n";
    // rows: time, mag0, mag1,...
    for (std::size_t t = 0; t < times.size(); ++t) {
        ofs << times[t];
        const auto& row = mags[t];
        for (double m : row) ofs << "," << m;
        ofs << "\n";
    }
    return true;
}

static bool writeDominantCSV(const std::string& filename,
    const std::vector<double>& times,
    const std::vector<double>& domFreqs)
{
    std::ofstream ofs(filename, std::ios::out);
    if (!ofs) return false;
    ofs << std::setprecision(6) << std::fixed;
    ofs << "time,dominant_frequency\n";
    for (std::size_t i = 0; i < times.size(); ++i) {
        ofs << times[i] << "," << domFreqs[i] << "\n";
    }
    return true;
}

// ----------------- LevelGenerator constructor: full-file spectrogram -----------------
LevelGenerator::LevelGenerator(std::string filePath)
{
    // Open file for streaming/reading
    sf::InputSoundFile infile;
    if (!infile.openFromFile(filePath)) {
        std::cerr << "Error while loading audio file: " << filePath << std::endl;
        return;
    }

    sampleRate = infile.getSampleRate();
    channelCount = infile.getChannelCount();
    std::uint64_t totalSamples = infile.getSampleCount(); // interleaved samples
    totalFrames = totalSamples / channelCount;

    std::cout << "Sample rate: " << sampleRate << " Hz\n";
    std::cout << "Channels: " << channelCount << "\n";
    std::cout << "Total samples: " << totalSamples << " (frames = " << totalFrames << ")\n";

    // Read entire file into interleaved int16 buffer (if file too large, convert to streaming processing)
    const std::size_t blockFrames = 4096;
    const std::size_t blockSamples = blockFrames * channelCount;
    std::vector<std::int16_t> tmp(blockSamples);
    std::vector<std::int16_t> allSamples;
    allSamples.reserve(static_cast<std::size_t>(std::min<std::uint64_t>(totalSamples, (std::uint64_t)blockSamples * 8)));

    std::int64_t readCount = 0;
    while ((readCount = infile.read(tmp.data(), static_cast<std::int64_t>(tmp.size()))) > 0) {
        allSamples.insert(allSamples.end(), tmp.begin(), tmp.begin() + static_cast<std::size_t>(readCount));
    }
    std::size_t totalSamplesRead = allSamples.size();
    if (totalSamplesRead == 0) {
        std::cerr << "No samples could be read from the file.\n";
        return;
    }
    std::size_t readFramesActual = totalSamplesRead / channelCount;
    std::cout << "Total samples read: " << totalSamplesRead << " (frames = " << readFramesActual << ")\n";

    // Convert to mono (no skipping) so we analyze the whole file "tout au long du fichier"
    m_monoSamples = interleavedToMonoFloat(allSamples, channelCount, 0);
    if (m_monoSamples.empty()) {
        std::cerr << "Conversion to mono failed or produced empty buffer.\n";
        return;
    }

    // Analysis parameters (tweakable)
    std::size_t N = 4096;                 // window size (power of two)
    std::size_t hop = sampleRate;             // 50% overlap
    if (m_monoSamples.size() < N) {
        // reduce N to the largest power of two <= available samples
        N = previousPowerOfTwo(m_monoSamples.size());
        if (N < 32) {
            std::cerr << "Not enough samples for FFT analysis.\n";
            return;
        }
        hop = N / 2;
        std::cout << "Reduced FFT size to " << N << " due to short file.\n";
    }
    // Precompute Hann window and frequency bins
    std::vector<double> hann = makeHann(N);
    const std::size_t half = N / 2; // keep bins [0..half-1]
    m_freqBins.resize(half);
    for (std::size_t k = 0; k < half; ++k) m_freqBins[k] = static_cast<double>(k) * static_cast<double>(sampleRate) / static_cast<double>(N);

    // Sliding windows
    std::size_t numFrames = 1 + (m_monoSamples.size() >= N ? (m_monoSamples.size() - N) / hop : 0);
    if (numFrames == 0) numFrames = 1;
    m_spectrogram.clear();
    m_spectrogram.reserve(numFrames);
    m_times.clear();
    m_times.reserve(numFrames);
    m_dominantFrequencies.clear();
    m_dominantFrequencies.reserve(numFrames);

    std::cout << "Analyzing windows: windowSize=" << N << " hop=" << hop << " frames=" << numFrames << "\n";

    std::vector<Complex> buffer(N);
    std::vector<double> mags(half);

    for (std::size_t frame = 0, start = 0; start + N <= m_monoSamples.size(); ++frame, start += hop) {
        // Copy window and apply Hann & remove mean (DC)
        double mean = 0.0;
        for (std::size_t i = 0; i < N; ++i) mean += m_monoSamples[start + i];
        mean /= static_cast<double>(N);
        for (std::size_t i = 0; i < N; ++i) {
            double v = (m_monoSamples[start + i] - mean) * hann[i];
            buffer[i] = Complex(v, 0.0);
        }

        // FFT
        fft(buffer);

        // compute magnitudes for bins 0..half-1
        for (std::size_t k = 0; k < half; ++k) {
            mags[k] = std::abs(buffer[k]);
        }

        // store magnitudes (move copy)
        m_spectrogram.emplace_back(mags);

        // compute time (center of window)
        double centerSample = static_cast<double>(start) + static_cast<double>(N) / 2.0;
        double timeSec = centerSample / static_cast<double>(sampleRate);
        m_times.push_back(timeSec);

        // find dominant frequency (peak) and refine with parabolic interpolation
        std::size_t kmax = 1;
        double maxmag = mags[1];
        // set threshold to avoid selecting noise: relative threshold 1% of max in window
        for (std::size_t k = 2; k < half; ++k) {
            if (mags[k] > maxmag) { maxmag = mags[k]; kmax = k; }
        }
        double domFreq = 0.0;
        if (maxmag > 1e-12) {
            double kref = parabolicInterpolation(mags, kmax);
            domFreq = kref * static_cast<double>(sampleRate) / static_cast<double>(N);
        }
        m_dominantFrequencies.push_back(domFreq);
    }

    std::cout << "Analysis complete (" << m_spectrogram.size() << " time frames, " << half << " freq bins).\n";
}


std::vector<double> LevelGenerator::getTime()
{
    return m_times;
}

std::vector<double> LevelGenerator::getDomfreq()
{
    return m_dominantFrequencies;
}