#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>
#include <string>
#include <windows.h>

namespace fs = std::filesystem;
using namespace std;

void printUsage() {
    cout << "Usage: program_name <directory> <file_pattern> [options]\n";
    cout << "Options:\n";
    cout << "-h, --help \n";
}

bool matchesPattern(const string& filename, const string& pattern) {
    string regex_pattern = pattern;
    regex_pattern = regex_replace(regex_pattern, regex(R"(\.)"), R"(\.)");
    regex_pattern = regex_replace(regex_pattern, regex(R"(\*)"), R"(.*)");
    regex_pattern = regex_replace(regex_pattern, regex(R"(\?)"), R"(.)");
    regex re(regex_pattern);
    return regex_match(filename, re);
}

bool isHidden(const fs::path& p) {
    DWORD attrs = GetFileAttributes(p.c_str());
    if (attrs == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (attrs & FILE_ATTRIBUTE_HIDDEN) != 0;
}

uintmax_t calculateDirectorySize(const fs::path& directory, const string& pattern) {
    uintmax_t total_size = 0;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && !isHidden(entry.path())) {
            const string file_name = entry.path().filename().string();
            cout << "Checking file: " << file_name << endl;
            if (matchesPattern(file_name, pattern)) {
                total_size += entry.file_size();
                cout << "Matched file: " << entry.path().string() << " Size: " << entry.file_size() << " bytes\n";
            }
        }
    }
    return total_size;
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printUsage();
    cout << endl;

    if (argc < 3) {
        cout << "Uncorrect format of command line";
        return 1;
    }

    string directory = argv[1];
    string pattern = argv[2];

    cout << "Directory: " << directory << endl;
    cout << "Pattern: " << pattern << endl;
    cout << endl;

    for (int i = 3; i < argc; ++i) {
        string option = argv[i];
        if (option == "-h" || option == "--help") {
            printUsage();
            return 0;
        }
        else {
            cerr << "Unknown option: " << option << "\n";
            printUsage();
            return 1;
        }
    }

    try {
        if (!fs::exists(directory) || !fs::is_directory(directory)) {
            cerr << "Error: The specified path is not a directory or does not exist.\n";
            return 2;
        }

        uintmax_t total_size = calculateDirectorySize(directory, pattern);
        cout << endl;
        cout << "Total size of matching files in " << directory << ": " << total_size << " bytes\n";

    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << "\n";
        return 3;
    }

    return 0;
}