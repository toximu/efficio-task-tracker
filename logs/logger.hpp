#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <string>

class Logger {
public:
    static Logger &get_instance() {
        static Logger instance;
        return instance;
    }

    Logger() {
        log_path_ = absolute(
            std::filesystem::path(__FILE__).parent_path() / "logs.txt"
        );

        {
            const std::ofstream clear_file(log_path_, std::ios::trunc);
            if (!clear_file) {
                throw std::runtime_error(
                    "Failed to clear log file: " + log_path_.string()
                );
            }
        }

        log_file_.open(log_path_, std::ios::app);
        if (!log_file_) {
            throw std::runtime_error(
                "Failed to open log file: " + log_path_.string()
            );
        }

        *this << "[LOGGER] : SESSION STARTED\n";
    }

    ~Logger() {
        if (log_file_.is_open()) {
            *this << "[LOGGER] : SESSION ENDED\n";
            log_file_.close();
        }
    }

    template <typename T>
    Logger &operator<<(const T &message) {
        std::lock_guard lock(log_mutex_);
        log_file_ << "[" << current_time() << "] " << message;
        log_file_.flush();
        return *this;
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    std::string current_time() {
        const auto now = std::chrono::system_clock::now();
        const auto now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        localtime_r(&now_time, &tm_buf);
        std::ostringstream oss;
        oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    std::filesystem::path log_path_;
    std::ofstream log_file_;
    std::mutex log_mutex_;
};

static Logger &logger = Logger::get_instance();