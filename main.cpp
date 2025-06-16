#include <chrono>
#include <thread>
#include <string>

#include "Timestamp.cpp"
#include "MetricStorage.h"
#include "DumpToFile.h"
#include "MetricDumper.h"

int main() {
    auto start_time = std::chrono::system_clock::now();
    std::string filename = "Metrics_" + ToTimeStampForFile(start_time) + ".txt";

    MetricStorage storage;
    DumpToFile dumper(filename);
    MetricDumper metric_dumper(storage, std::chrono::milliseconds{1000}, dumper);

    storage.Add_Metric("CPU", 0.42);
    storage.Add_Metric("Memory usage MB", 128);
    std::this_thread::sleep_for(std::chrono::seconds{2});
    storage.Add_Metric("HTTP requests RPS", 256);
    storage.Add_Metric("Service", std::string("auth"));
    std::this_thread::sleep_for(std::chrono::seconds{1});
    storage.Add_Metric("Error rate", 0.01);

    return 0;
}



