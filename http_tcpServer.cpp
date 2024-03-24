#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_tcpServer.h"

namespace {
void log(const std::string &message) { std::cout << message << std::endl; }
void exitWithError(const std::string &message) {
  log("error: " + message);
  exit(1);
}
} // namespace

namespace http {
TcpServer::TcpServer() {}

int TcpServer::StartServer() {
  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (m_socket < 0) {
    exitWithError("Cannot create socket");
    return 1;
  }
  return 0;
}

void TcpServer::StopServer() {
  close(m_socket);
  exit(0);
}

TcpServer::~TcpServer() {}
} // namespace http
