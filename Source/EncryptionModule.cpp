#include "EncryptionModule.hpp"

#include <filesystem>
#include <cstdlib> // for system()
#include <fstream>
#include <random>

void EncryptionModule::TryCreateArchive(std::string archiveName) {
    // Check if 7z is usable
    int check = system("7z >nul 2>&1");
    // MacOS/Linux: system("7z > /dev/null 2>&1");
    if (check != 0) {
        std::cerr << "7-Zip is not installed or not in PATH.\n";
        return;
    }

    // Check if archive already exists
    if (std::filesystem::exists(archiveName)) {
        std::cerr << "Archive \"" << archiveName << "\" already exists.\n";
        return;
    }

    // Create an empty archive as a test
    std::string command = "7z a \"" + archiveName + "\" -mx=0 >nul";
    int result = system(command.c_str());
    if (result == 0)
        std::cout << "Archive created: " << archiveName << "\n";
    else
        std::cerr << "Failed to create archive: " << archiveName << "\n";
}

void EncryptionModule::EncryptAndAddFiles(AccessControlMatrix& acm) {
    // Since ACM provides no file accessors, simulate what we'd do:
    std::cerr << "[EncryptAndAddFiles] No file list in ACM. This function requires ACM to expose file data.\n";
    // Example:
    // for (const auto& file : acm.GetFiles())
    //     Encrypt file with acm.GetEncryptionKey(file)
}

void EncryptionModule::EncryptAndAddACM(AccessControlMatrix& acm, std::vector<std::string>& accessKeysOut) {
    // Again, AccessControlMatrix has no method to generate or expose the keys or save them
    // We’ll stub this out as a placeholder for future implementation

    std::cerr << "[EncryptAndAddACM] ACM does not support exporting keys or structure yet.\n";

    // Simulate true random key generation for four roles
    const int keyLength = 16;
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    accessKeysOut.clear();
    for (int i = 0; i < 4; ++i) {
        std::string key;
        for (int j = 0; j < keyLength; ++j)
            key += charset[dist(gen)];
        accessKeysOut.push_back(key);
    }

    std::cout << "Generated random keys for 4 roles (Admin, Privileged, User, Guest):\n";
    for (int i = 0; i < 4; ++i)
        std::cout << "Key " << i << ": " << accessKeysOut[i] << "\n";

    // You might also write these keys to a temporary CSV and encrypt that, but ACM doesn't allow export.
}
