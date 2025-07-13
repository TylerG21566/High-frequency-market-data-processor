cmake_minimum_required(VERSION 3.12)
project(cp_perfrom)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only include .cpp files, not .h files
add_executable(cp_perfrom
    src/main.cpp
    # Remove this line: dotenv_loader.cpp
)

# Find packages through vcpkg
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Link libraries
target_link_libraries(cp_perfrom
    PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

target_compile_options(cp_perfrom PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3>
)