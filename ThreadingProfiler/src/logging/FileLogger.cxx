#include "../../include/logging/FileLogger.hxx"
#include <ctime>

FileLogger::FileLogger(const std::filesystem::path &path)
    : log_file_path(path), log_stream(path, std::ios::app)
{
    if (!this->log_stream.is_open())
        throw std::runtime_error("Failed to open log file: " + path.string());
}

void FileLogger::log(const LogMessage &data)
{
    if (!this->log_stream.is_open())
        throw std::runtime_error("Failed to log because the log file is not opened");
    fprintf(stderr, "[PROFILER] LOGGING IN THE LOG STREAM\n");
    std::time_t t = std::chrono::system_clock::to_time_t(data.time);
    log_stream << "[" << std::put_time(std::localtime(&t), "%F %T") << "] [";
    log_stream << to_string(data.severity) << "] [" << to_string(data.type) << "]\n";
    log_stream.flush();
    fprintf(stderr, "[PROFILER] LOGGED SUCCESSFULLY\n");
}

FileLogger::~FileLogger()
{
    if (log_stream.is_open())
        log_stream.close();
}