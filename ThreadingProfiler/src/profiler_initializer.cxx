#include "../include/logging/Logger.hxx"
#include "../include/logging/FileLogger.hxx"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <filesystem>
#include <iostream>

inline void load_env_file(const std::filesystem::path &path = "../ThreadingProfiler/.env")
{
    fprintf(stderr, "[PROFILER] Loading the environment variables\n");
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("COULDN'T FIND ENV FILE: " + path.string());

    fprintf(stderr, "[PROFILER] Found the following\n");
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        auto pos = line.find("=");
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        fprintf(stderr, "[PROFILER] %s = %s\n", key.c_str(), value.c_str());
        setenv(key.c_str(), value.c_str(), 1);
    }
}

__attribute__((constructor)) static void initialize_logger()
{
    load_env_file();

    auto logger = Logger::get_instance();
    const char *log_path_env = std::getenv("LOGGER_PATH");
    std::filesystem::path log_path = log_path_env ? std::filesystem::path(log_path_env) : std::filesystem::path("/tmp/thread_log.txt");
    logger->add_logger(std::make_unique<FileLogger>(log_path));
    fprintf(stderr, "[PROFILER] added a logger\n");
}

__attribute__((destructor)) static void shutdown_logger()
{
}