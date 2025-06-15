#include "../include/logging/Logger.hxx"
#include "../include/logging/FileLogger.hxx"
#include "../include/logging/TCPLogger.hxx"
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

__attribute__((constructor)) static void initialize_profiler()
{
    // needed loadings
    load_env_file();

    // file logger initialization
    const char *log_path_env = std::getenv("LOGGER_PATH");
    std::filesystem::path log_path = std::filesystem::path(log_path_env);

    // tcp logger initialization
    const char *port_path_env = std::getenv("SERVER_PORT");
    int port = atoi(port_path_env);

    // logger initialization
    Logger::get_instance()->add_logger(std::make_unique<FileLogger>(log_path));
    Logger::get_instance()->add_logger(std::make_unique<TCPLogger>(port));
}

__attribute__((destructor)) static void cleanup_profiler()
{
}