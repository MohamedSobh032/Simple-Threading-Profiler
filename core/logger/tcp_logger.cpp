#include "tcp_logger.hpp"

#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include <stdexcept>

TCPLogger::TCPLogger(int port)
{
  this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) throw std::runtime_error("Server Socket failed");

  int opt = 1;
  setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  this->address.sin_family = AF_INET;
  this->address.sin_port = htons(port);
  this->address.sin_addr.s_addr = INADDR_ANY;

  if (bind(this->server_fd, (struct sockaddr*)&this->address, sizeof(this->address)) < 0)
    throw std::runtime_error("Failed to bind server");

  if (listen(this->server_fd, 1) < 0) throw std::runtime_error("Failed to listen");

  fprintf(stderr, "[PROFILER] Waiting for a client...\n");

  socklen_t addrlen = sizeof(address);
  this->client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
  if (this->client_fd < 0) throw std::runtime_error("Failed to accept client connection");

  // Get and print client IP and port
  char client_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
  int client_port = ntohs(address.sin_port);
  fprintf(stderr, "[PROFILER] Connected to client: %s:%d\n", client_ip, client_port);

  this->connected = true;
  fprintf(stderr, "[PROFILER] TCP connection with client initialized\n");
}

void TCPLogger::log(const Event& ev)
{
  if (!this->connected) return;
  nlohmann::json j = ev.to_json();
  std::string serialized = j.dump() + "\n";
  send(client_fd, serialized.c_str(), serialized.size(), 0);
}

TCPLogger::~TCPLogger()
{
  if (this->connected) close(this->client_fd);
  close(this->server_fd);
}