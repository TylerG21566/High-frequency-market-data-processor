# cp_perfrom C++17 Project

This CLI project, named "StockSignal," fetches real-world stock data using the AlphaVantage API and calculates moving averages (Simple, Exponential, Weighted, Hull) for trend analysis. Key features include:

High-frequency data processing for near real-time moving average calculations.
Customizable stock selection, timeframes, and moving average parameters.
Interactive data visualization with Matplotlib.
Data export for further analysis or backtesting.
Future plans involve adding paper trading features for strategy simulation and performance monitoring. Built with Python, StockSignal prioritizes performance and efficiency for seamless high-frequency data processing and analysis.

In essence, StockSignal offers traders and investors real-time moving average calculations and future paper trading capabilities, aiding informed decision-making and strategy enhancement.


## Setup

This project uses [CMake](https://cmake.org/) and [vcpkg](https://github.com/microsoft/vcpkg) for dependency management.

### Dependencies
- full list pending..

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
   ```zsh
   bash build_and_run
   ```

### Environment Variables
- Place your Alpha Vantage API key in the `.env` file (already present).





