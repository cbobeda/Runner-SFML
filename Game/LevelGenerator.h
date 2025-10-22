#pragma once

#include <SFML/Audio.hpp>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <complex>
#include <fstream>
#include <iomanip>
#include <algorithm>
class LevelGenerator
{
	public:
		LevelGenerator(std::string filePath = "assets/music/test.ogg");
		std::vector<double> getTime();
		std::vector<double> getDomfreq();
	private:
		sf::InputSoundFile buf;
		unsigned int sampleRate;
		unsigned int channelCount;
		std::uint64_t totalFrames;
		std::vector<double> m_monoSamples;
		std::vector<double> m_freqBins;
		std::vector<std::vector<double>> m_spectrogram;
		std::vector<double> m_times;
		std::vector<double> m_dominantFrequencies;
		

};

