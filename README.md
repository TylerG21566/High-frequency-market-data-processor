# cp_perfrom C++ Project

Trading simulator

cpperfrom/
├── include/                    # All header files
│   ├── common.h               # MarketTick struct & common definitions
│   ├── alphavantage_client.h  # API client with error handling
│   ├── technical_indicators.h # SMA, EMA, RSI, MACD, Bollinger Bands
│   ├── logger.h              # High-performance async logging
│   └── threading_engine.h    # Multi-threaded processing engine
├── src/                       # Implementation files
│   ├── main.cpp              # Complete application with callbacks
│   ├── alphavantage_client.cpp
│   ├── technical_indicators.cpp
│   ├── logger.cpp
│   └── threading_engine.cpp
├── CMakeLists.txt            # Professional build configuration
├── build.sh                  # Enhanced build script
├── .env.example             # Environment configuration template
└── README.md                # Comprehensive documentation


## Setup

This project uses [CMake](https://cmake.org/) and [vcpkg](https://github.com/microsoft/vcpkg) for dependency management.

### Dependencies
- [cpr](https://github.com/libcpr/cpr) (HTTP client)
- [dotenv-cpp](https://github.com/therecipe/dotenv-cpp) (for loading .env files)

### Build Instructions

1. Install vcpkg if you haven't already:
   ```sh
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   ./bootstrap-vcpkg.sh
   ```
2. Install dependencies:
   ```sh
   ./vcpkg/vcpkg install
   ```
3. Configure and build the project:
   ```sh
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build build
   ```

### Environment Variables
- Place your Alpha Vantage API key in the `.env` file (already present).

---
No application code is included yet.




