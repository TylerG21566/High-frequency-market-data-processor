#include <curl/curl.h>

#include <ctime>       // for std::localtime
#include <filesystem>  // C++17 feature
#include <iomanip>     // for std::put_time
#include <iostream>
#include <nlohmann/json.hpp>

#include "../include/common.h"
#include "../include/dotenv_loader.h"

const std::string APPLE_SYMBOL = "AAPL";  // Example stock symbol
const std::string basic_interval =
    "1min";                        // Default interval for intraday data
const int basic_outputsize = 100;  // Default output size for data

std::vector<MarketTick> fetchMarketData(const std::string &api_key,
                                        const std::string &symbol = "APPL",
                                        const std::string &interval = "1min",
                                        int outputsize = 100) {
  try {
    AlphaVantageAPI api(api_key);

    std::cout << "Fetching " << interval << " data for " << symbol << " (max "
              << outputsize << " points)..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Fetch the data
    std::vector<MarketTick> intraday_data =
        api.getIntradayData(symbol, interval, outputsize);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    if (intraday_data.empty()) {
      std::cerr << "Warning: No data received for symbol " << symbol
                << ". Check if symbol exists or API key is valid." << std::endl;
      return {};
    }

    // Data validation
    int valid_ticks = 0;
    for (const auto &tick : intraday_data) {
      if (tick.open > 0 && tick.close > 0 && tick.volume >= 0) {
        valid_ticks++;
      }
    }

    std::cout << "✓ Successfully parsed " << intraday_data.size()
              << " data points for " << symbol << " (" << valid_ticks
              << " valid) in " << duration.count() << "ms" << std::endl;

    MarketTick tick = intraday_data.front();

    std::cout << "first tick: \n"
              << "timestamp: (" << tick.timestampStr << ")"
              << "open: " << tick.open << "close: " << tick.close
              << "high: " << tick.high << "low: " << tick.low << std::endl;

    return intraday_data;
  } catch (const std::exception &e) {
    std::cerr << "Error fetching market data for " << symbol << ": " << e.what()
              << std::endl;
    return {};
  }
};

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::cout << "This project uses C++17 standard." << std::endl;
  std::cout << "Current working directory: " << std::filesystem::current_path()
            << std::endl;

  // Check if .env file exists
  if (std::filesystem::exists(".env")) {
    std::cout << ".env file exists!" << std::endl;
  } else {
    std::cout << ".env file NOT found in current directory" << std::endl;
    return 1;  // Exit with error code
  }

  // Try loading with full path feedback
  if (!load_dotenv()) {
    std::cout << "Failed to load .env file" << std::endl;
    return 1;  // Exit with error code
  } else {
    std::cout << "Successfully loaded .env file" << std::endl;
  }

  // Access variables
  const char *api_key = getenv("API_KEY");
  if (api_key) {
    std::cout << "API Key loaded: " << api_key << std::endl;
  } else {
    std::cout << "No API_KEY found in environment" << std::endl;
    return 1;
  }

  /***  Fetch and Parse JSON data using AlphaVantageAPI, return MarketTick
   * vector ***/
  std::vector<MarketTick> data =
      fetchMarketData(api_key, APPLE_SYMBOL, basic_interval, basic_outputsize);
  if (data.empty()) {
    std::cout << "No data fetched for " << APPLE_SYMBOL << std::endl;
  } else {
    std::cout << "Fetched " << data.size() << " data points for "
              << APPLE_SYMBOL << std::endl;
  }

  return 0;
}
