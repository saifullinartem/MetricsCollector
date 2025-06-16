#pragma once

#include <string>
#include <memory>
#include <chrono>

struct MetricValue {
    virtual std::string toString() const = 0;
    virtual ~MetricValue() = default;
};

template<typename T>
struct MetricValueImplementation : MetricValue {
    T value;
    explicit MetricValueImplementation(T v) : value(std::move(v)) {}
    std::string toString() const override {
        if constexpr(std::is_same_v<T, std::string>)
            return "\"" + value + "\"";
        else
            return std::to_string(value);
    }
};

struct Metric {
    std::string name;
    std::unique_ptr<MetricValue> value;
    std::chrono::system_clock::time_point timestamp;
    size_t count;

    template<typename T>
    Metric(std::string n, T v, size_t cnt = 1) : name(std::move(n)), value(std::make_unique<MetricValueImplementation<T>>(std::move(v))), timestamp(std::chrono::system_clock::now()), count(cnt){}
};
