#include <curl/curl.h>

#include <chrono>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include <fstream>  // Required for std::ofstream
#include <iostream> // For std::cout

const std::string jsonIntradayFileTale = "_intraday.json";

struct MarketTick {
  /* data */
  std::chrono::system_clock::time_point timestamp;  // When the tick occurred
  double price;  // Current price of the asset
  uint64_t volume;
  std::string timestampStr;
  double open, high, low, close;
  // long volume;
};



// Add this function before your AlphaVantageAPI class
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            std::string *userp) {
  size_t total_size = size * nmemb;
  userp->append(static_cast<char *>(contents), total_size);
  return total_size;
}

class AlphaVantageAPI {
 private:
  std::string api_key;  // API key for Alpha Vantage
  std::string base_url =
      "https://www.alphavantage.co/query?";  // Base URL for API requests

 public:
  std::string get_api_key() const { return api_key; }
  std::string get_base_url() const { return base_url; }

  AlphaVantageAPI(const std::string &api_key) : api_key(api_key) {}

  void writeStringToJson(const std::string &str, const std::string &filename) {
    if (str.empty()) {
      std::cout << "empty" << std::endl;
      return;
    }
    nlohmann::json j;
    j["data"] = str;
    std::ofstream file("../src/data/" + filename);
    file << j.dump(2);
  }

  std::vector<MarketTick> jsonToMarketTickVector (const nlohmann::json &Json) {
    std::vector<MarketTick> ticks;
    for (const auto& [date, data] : Json.items()) {
       MarketTick tick;
       tick.timestampStr = date;
       tick.open = data["1. open"];
       tick.high = data["2. high"];
       tick.low = data["3. low"];
       tick.close = data["4. close"];
       tick.volume = data["5. volume"];
       tick.price = tick.close;
       tick.price = tick.close; // or whatever you want as current price
       
       ticks.push_back(tick);
       
       std::cout << "Date: " << tick.timestampStr << ", Price: " << tick.price 
                 << ", Volume: " << tick.volume << ", OHLC: " << tick.open 
                 << "/" << tick.high << "/" << tick.low << "/" << tick.close << std::endl;
   }
   return ticks;
  }

  






  std::vector<MarketTick> getIntradayData(const std::string &symbol,
                                          const std::string &interval = "1min",
                                          int outputsize = 100) {
    std::vector<MarketTick> result;
    // Change your URL to daily data:
    std::string url =
        "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" +
        symbol + "&apikey=" + api_key + "&outputsize=compact";

    // Setup curl
    CURL *curl = curl_easy_init();
    if (!curl) {
      std::cout << "DEBUG: curl_easy_init() FAILED!" << std::endl;
      throw std::runtime_error("Failed to initialize curl");
    }

    std::string response_data;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      std::cout << "DEBUG: Curl failed with error: " << curl_easy_strerror(res)
                << std::endl;
      curl_easy_cleanup(curl);
      throw std::runtime_error("Curl request failed: " +
                               std::string(curl_easy_strerror(res)));
    }

    
    std::cout << "First 1000 chars: "
              << response_data.substr(0, 2000) <<"\n\n" << std::endl;

    nlohmann::json json = nlohmann::json::parse(response_data)["Time Series (Daily)"];
    // print front of json
    std::cout << json.dump(2)<< std::endl;
    // print back of json



    return jsonToMarketTickVector(json);
  }

  std::vector<MarketTick> getDailyData(const std::string &symbol,
                                       int outputsize = 100);

  MarketTick getCurrentPrice(const std::string &symbol);

 private:
  std::string makeHttpRequest(const std::string &url);
  std::vector<MarketTick> parseJsonResponse(const std::string &json);
};
