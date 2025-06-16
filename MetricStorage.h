#pragma once

#include <vector>
#include <mutex>
#include "Metrics.h"

class MetricStorage {
public:
    template<typename V>
    void Add_Metric(const std::string& name, const V& value) {
        std::lock_guard lock(mutex_);
        Metrics.emplace_back(name, value);
    }

    std::vector<Metric> GetMetric() {
        std::lock_guard lock(mutex_);
        std::vector<Metric> tmp = std::move(Metrics);
        Metrics.clear();
        return tmp;
    }

private:
    std::mutex mutex_;
    std::vector<Metric> Metrics;
};
