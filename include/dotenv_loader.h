#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <cstdlib>



inline bool load_dotenv(const std::string& filename = ".env") {

    std::ifstream file(filename);
    if (!file.is_open()) {
        // throw std::runtime_error("Could not open .env file: " + filename);
        return false;
    }
    int line_count = 0;
    std::string line;
    while (std::getline(file, line)){
         line_count++;
        // remove comments
        auto comment_pos = line.find('#');
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
        }
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))  {
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t\r\n"));
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);
            if (!key.empty() && !value.empty()) {
                // Set environment variable
                setenv(key.c_str(), value.c_str(), 1); // 1 = overwrite
            }
        }
    }
    return true;
}