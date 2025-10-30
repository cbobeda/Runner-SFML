#include "SaveManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>

SaveManager::SaveManager(const std::string& path)
    : filePath(path)
{
    std::filesystem::path p(filePath);
    if (p.has_parent_path()) {
        std::error_code ec;
        std::filesystem::create_directories(p.parent_path(), ec);
        if (ec) {
            std::cerr << "SaveManager: erreur creation dossier " << p.parent_path()
                << " : " << ec.message() << '\n';
        }
    }

    // Crée le fichier s'il n'existe pas (mode append pour ne pas tronquer)
    std::ofstream out(filePath, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "SaveManager: impossible de créer/ouvrir " << filePath << '\n';
    }
}

int SaveManager::getSavedScore()
{
    std::ifstream in(filePath);
    if (!in.is_open()) {
        std::cerr << "getSavedCoins: impossible d'ouvrir " << filePath << " en lecture\n";
        return 0;
    }

    std::string line;
    if (!std::getline(in, line) || line.empty()) {
        return 0;
    }

    if (!line.empty() && line.back() == '\r') line.pop_back();

    try {
        return std::stoi(line);
    }
    catch (...) {
        return 0;
    }
}

void SaveManager::saveScore(int coins)
{
    // ouvre en écriture et tronque le fichier (écrase l'ancien contenu)
    std::ofstream out(filePath, std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "savecoins: impossible d'ouvrir " << filePath << " en écriture\n";
        return;
    }

    out << coins << '\n';
    out.flush();
    if (!out.good()) {
        std::cerr << "savecoins: erreur lors de l'écriture dans " << filePath << '\n';
    }
}