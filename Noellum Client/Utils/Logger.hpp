#pragma once
#include <vector>
#include <string>
#include <format>
#include <source_location>
#include <deque>
#include <mutex>

namespace Utils {
    struct LogEntry {
        std::string timestamp;
        std::string level;
        std::string message;
        std::string location;
    };

    class Logger {
    public:
        // Max log yang disimpan agar tidak makan RAM PC Lab
        static inline size_t max_entries = 100;
        static inline std::deque<LogEntry> logs;
        static inline std::mutex log_mutex;

        static void Log(std::string_view msg, std::string_view level = "INFO",
            const std::source_location loc = std::source_location::current()) {

            std::lock_guard<std::mutex> lock(log_mutex);

            // Format lokasi: NamaFile:Baris
            std::string location = std::format("{}:{}", loc.file_name(), loc.line());

            // Tambahkan ke deque
            logs.push_back({ "10:10", std::string(level), std::string(msg), location });

            // Hapus log lama jika kepenuhan
            if (logs.size() > max_entries)
                logs.pop_front();

            // Tetap print ke console buat backup
            printf("[%s] [%s] %s\n", level.data(), location.c_str(), msg.data());
        }
    };
}