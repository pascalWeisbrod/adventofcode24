#include "helper.h"
#include <windows.h>
#include <iostream>
#include <fstream>  // For file handling
#include <string>   // For using string

Helper::Helper(){}
Helper::~Helper(){}

std::string Helper::read_file(std::string file_path) {
    std::ifstream file(file_path); // Open the file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return "";
    }

    std::string text = "";
    std::string line;
    while (std::getline(file, line)) { // Read line by line
        std::cout << line << std::endl; // Output the line to the console
        text += line;
    }

    file.close(); // Close the file
    return text;
}


std::string Helper::get_executing_input_file() {
    char path[MAX_PATH]; // Buffer to store the file path
    HMODULE hModule = nullptr; // Handle to the current module (nullptr means the current process)

    // Get the full path of the executable
    if (GetModuleFileName(hModule, path, MAX_PATH) != 0) {
        std::cout << "Executing file: " << path << std::endl;
    } else {
        std::cerr << "Error: Unable to get the file path. Error code: " << GetLastError() << std::endl;
    }

    std::string file_path = "";
    char c = 'a';
    int i = 0;
    while (c != '.')
    {
        c = path[i++];
        file_path += c;
    }

    while(i >= 0 && c != '\\')
    {
        c = path[--i];
    }

    file_path = file_path.substr(0, i);
    file_path += "\\input.txt";

    std::cout << "Executable is located in: " << file_path << std::endl;

    return file_path;
}

int Helper::readLines()
{
    std::string path = get_executing_input_file();
    std::cout << path << std::endl;

    read_file("C:/Users/pe190/Desktop/GitHub/aoc/adventofcode24/code/helper/input.txt");

    return 0;
}
