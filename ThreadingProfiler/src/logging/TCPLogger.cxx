#include "../../include/logging/TCPLogger.hxx"

#include <nlohmann/json.hpp>
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>

inline void to_json(nlohmann::json &j, const ThreadInfo &thread_info)
{
    j = nlohmann::json{
        {"threadID", thread_info.tid},
        {"systemID", thread_info.system_tid},
        {"blocking resource", thread_info.blocking_resource}};
}

void to_json(nlohmann::json &j, const MutexInfo &m)
{
    j = nlohmann::json{
        {"mid", m.mid},
        {"ptr", reinterpret_cast<uintptr_t>(m.ptr)},
        {"owner_tid", m.owner_tid}};
}

void to_json(nlohmann::json &j, const DeadlockInfo &d)
{
    j = nlohmann::json{
        {"hello", "hi"}};
}

inline void to_json(nlohmann::json &j, const LogMessage &msg)
{
    j = nlohmann::json{
        {"type", to_string(msg.type)},
        {"severity", to_string(msg.severity)},
        {"time", std::chrono::duration_cast<std::chrono::milliseconds>(msg.time.time_since_epoch()).count()}};
    std::visit([&j](auto &&arg)
               { j["data"] = arg; }, msg.data);
}

TCPLogger::TCPLogger(int port)
{
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
        throw std::runtime_error("Server Socket failed");

    int opt = 1;
    setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = INADDR_ANY;

    if (bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
        throw std::runtime_error("Failed to bind server");

    if (listen(this->server_fd, 1) < 0)
        throw std::runtime_error("Failed to listen");

    fprintf(stderr, "[PROFILER] Waiting for frontend...\n");

    socklen_t addrlen = sizeof(address);
    this->client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (this->client_fd < 0)
        throw std::runtime_error("Failed to accept frontend connection");

    // Get and print client IP and port
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(address.sin_port);
    fprintf(stderr, "[PROFILER] Connected to frontend: %s:%d\n", client_ip, client_port);

    this->connected = true;
    fprintf(stderr, "[PROFILER] TCP connection with frontend initialized");
}

void TCPLogger::log(const LogMessage &data)
{
    nlohmann::json j = data;
    std::string serialized = j.dump();
    send(client_fd, serialized.c_str(), serialized.size(), 0);
}

TCPLogger::~TCPLogger()
{
    if (this->connected)
        close(this->client_fd);
    close(this->server_fd);
}