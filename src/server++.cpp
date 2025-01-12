#include <iostream>
#include <cstdlib>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " sourcefile.cpp" << std::endl;
        return 1;
    }

    std::string sourceFile = argv[1];
    std::string outputFile = sourceFile.substr(0, sourceFile.find_last_of('.')) + ".exe"; // or ".out" for Unix-like systems

    // Get the directory of the executable
    std::string exePath = fs::canonical(argv[0]).parent_path().string();

    // Construct the include and lib paths (absolute paths)
    std::string includePath = fs::canonical(exePath + "/../include").string();
    std::string libPath = fs::canonical(exePath + "/../lib").string();
    std::string gccPath = fs::canonical(exePath + "/gcc-14.2.0").string(); // Path to your GCC folder

    // Construct the compilation command
    std::string command = gccPath + "/bin/g++ -std=c++14 -I" + includePath + " -L" + libPath + " " + sourceFile + " -lhttp_socket";
    
    // Add the Winsock library on Windows
    #ifdef _WIN32
    command += " -lws2_32";
    #endif

    command += " -o " + outputFile;
    
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Compilation failed!" << std::endl;
        return 1;
    }

    std::cout << "Compilation succeeded! Output: " << outputFile << std::endl;
    return 0;
}
