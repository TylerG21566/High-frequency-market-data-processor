#include <iostream>
#include <filesystem> // C++17 feature
#include "../include/dotenv_loader.h"
#include "../include/common.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "This project uses C++17 standard." << std::endl;
    
    // Debug: Check current working directory
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    
    // Debug: Check if .env file exists
    if (std::filesystem::exists(".env")) {
        std::cout << ".env file exists!" << std::endl;
    } else {
        std::cout << ".env file NOT found in current directory" << std::endl;
    }
    
    // Try loading with full path feedback
    if (!load_dotenv()) {
        std::cout << "Failed to load .env file" << std::endl;
    } else {
        std::cout << "Successfully loaded .env file" << std::endl;
    }
    
    // Access variables
    const char* api_key = getenv("API_KEY");
    if (api_key) {
        std::cout << "API Key loaded: " << api_key << std::endl;
    } else {
        std::cout << "No API_KEY found in environment" << std::endl;
    }
    
    return 0;
}