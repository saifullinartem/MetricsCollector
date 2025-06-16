cmake_minimum_required(VERSION 3.29)
project(MetricsCollector)

set(CMAKE_CXX_STANDARD 20)

add_executable(MetricsCollector main.cpp
        Timestamp.cpp
        Metrics.h
        MetricStorage.h
        DumpToFile.h
        MetricDumper.h)
