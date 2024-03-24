#pragma once

#include <string>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer(std::string ip_address, int port);
        int StartServer();
        void StopServer();
        ~TcpServer();

    private:
        std::string m_ip_address;
        int m_port;
        int m_socket;
      int m_new_socket;
      long m_incomingMessage;
    // struct sockaddr_in m_socketAddress;
    unsigned int m_socketAddres_len;
    std::string m_serverMessage;
    };
}
