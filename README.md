# MetricsCollector

MetricsCollector — это набор классов на C++ для сбора, агрегации и записи метрик в текстовый файл. Позволяет отслеживать произвольные именованные события с любыми возможными типами значений и сохранять их в файл с таймстампом.

# Пример выходного файла

2025-06-16 19:37:25.671 "CPU" 0.420000
2025-06-16 19:37:25.671 "Memory usage MB" 128

2025-06-16 19:37:27.677 "HTTP requests RPS" 256
2025-06-16 19:37:27.677 "Service" "auth"

2025-06-16 19:37:28.680 "Error rate" 0.010000
# Пример использования

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
Выходной файл имеет название, содержащее точное время запуска программы, например:

Metrics_2025-06-16_19.37.25.671.txt
# Примеры метрик

Средняя утилизация CPU за секунду
Значения — вещественные числа в диапазоне от 0 до N, где N — количество ядер процессора.
Значение 0 — полное отсутствие загруженности CPU, значение 2 — 100% загрузка двух ядер.
Количество принятых HTTP запросов за секунду
Значения — целые числа от 0 до INT_MAX.
# Формат вывода

Каждая запись метрик — отдельная строка:

2025-06-16 19:37:25.671 "CPU" 0.420000
# Дополнительно

Запись метрик не блокирует потоки, в которых она происходит.
 После записи в файл накопленные значения обнуляются.
