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
TcpServer::TcpServer(std::string ip_address, int port)
    : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
      m_incomingMessage(), m_socketAddress(),
      m_socketAddress_len(sizeof(m_socketAddress)), m_serverMessage() {
  m_socketAddress.sin_family = PF_INET;
  m_socketAddress.sin_port = htons(m_port);
  m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
}

int TcpServer::StartServer() {
  m_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (m_socket < 0) {
    exitWithError("Cannot create socket");
    return 1;
  }

  // Must cast sockaddr_in* to sockaddr*.
  if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
    exitWithError("Cannot bind socket");
    return 1;
  }
  return 0;
}

void TcpServer::StopServer() {
  close(m_socket);
  exit(0);
}

TcpServer::~TcpServer() {
  close(m_socket);
  close(m_new_socket);
  exit(0);
}
} // namespace http
