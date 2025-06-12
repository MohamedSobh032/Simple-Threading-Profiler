#ifndef _FILE_LOGGER
#define _FILE_LOGGER

#include "ILogger.hxx"
#include <filesystem>
#include <fstream>
#include <string>

class FileLogger : public ILogger
{
private:
    std::filesystem::path log_file_path;
    std::ofstream log_stream;

public:
    FileLogger(const std::filesystem::path &path);
    void log(const LogMessage &data) override;
    ~FileLogger();
};

#endif