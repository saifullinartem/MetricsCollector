#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Metrics.h"
#include "Timestamp.cpp"

class DumpToFile {
public:
    explicit DumpToFile(std::string filename)
      : filename_(std::move(filename))
    {}

    void operator()(std::vector<Metric> metrics) {
        std::ofstream file{filename_, std::ios::out | std::ios::app};
        if (!file.is_open()) {
            std::cerr << "File: " << filename_ << "was not opened" << "\n";
            return;
        }
        for (auto& m : metrics) {
            file << ToTimeStamp(m.timestamp) << " \"" << m.name << "\" " << m.value->toString() << "\n";
        }
        file << "\n";
    }

private:
    std::string filename_;
};
