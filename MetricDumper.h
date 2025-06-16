#pragma once

#include <thread>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include "MetricStorage.h"
#include "DumpToFile.h"

class MetricDumper {
public:
    MetricDumper(MetricStorage& storage, std::chrono::milliseconds interval, DumpToFile dumper) :
    storage_(storage), interval_(interval), dumper_(std::move(dumper)), is_stopped_(0) {
        thread_ = std::thread(&MetricDumper::Run , this);
    }

    ~MetricDumper() {
        is_stopped_.store(true);
        if(thread_.joinable()) {
            thread_.join();
        }
    }

private:
    void Run() {
        while(!is_stopped_.load()) {
            std::this_thread::sleep_for(interval_);
            auto metrics = storage_.GetMetric();
            if(!metrics.empty()) {
                dumper_(std::move(metrics));
            }
        }
        auto metrics = storage_.GetMetric();
        if(!metrics.empty()) {
            dumper_(std::move(metrics));
        }
    }

    MetricStorage& storage_;
    std::chrono::milliseconds interval_;
    DumpToFile dumper_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable condition_variable_;
    std::atomic<bool> is_stopped_;
};
