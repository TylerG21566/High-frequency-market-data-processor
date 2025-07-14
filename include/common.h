#include <chrono>
struct MarketTick
{
    /* data */
    std::chrono::system_clock::time_point timestamp;  // When the tick occurred
    double price;                                     // Current price of the asset
    uint64_t volume; 

};

