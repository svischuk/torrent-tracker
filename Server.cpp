#include "Server.h"

#define SOCKET_FAILED "Socket creation failed"
#define BIND_FAILED "Socket binding failed"
#define LISTEN_FAILED "Socket listening failed"
#define ACCEPT_FAILED "Client acceptation failed"
#define SET_OPT_FAILED "Setting socket options failed"
#define CLOSE_FAILED "Socket closing failed.."
#define SHUTDOWN_FAILED "Socket shutdown failed.."
#define RESPONSE_500 "HTTP/1.1 503 Service Unavailable\r\n"
#define POLL_TIMEOUT 10000
int Server::start() {

    if (running
        || createSocket()
        || setReuseAddress()
        || bindSocket()
        || listenSocket()) {
        return -1;
    }

    running = true;
    std::thread server(&Server::listener, this);
    server.detach();
    return 0;
}

int Server::stop() {
    if (!running) {
        return -1;
    }
    running = false;

    return destroySocket(socketFD);
}

bool Server::isRunning() const {
    return running;
}

void Server::listener() const {
    int connectionFD;
    struct sockaddr_in clientAddress{};
    socklen_t socketLength = sizeof(clientAddress);
    std::atomic<unsigned long> current_connections(0);

    struct pollfd pfds{};
    pfds.fd = socketFD;
    pfds.events = POLLIN;
    while (true) {
        poll(&pfds, 1, POLL_TIMEOUT);
        if (pfds.revents & POLLIN) {
            connectionFD = accept(socketFD, (struct sockaddr *) &clientAddress, &socketLength);
            if (connectionFD == -1) {
                if (running) {
                    perror(ACCEPT_FAILED);
                    continue;
                } else {
                    return;
                }
            }
            auto task = this->service;
            if (current_connections < max_connections) {
                std::thread requestHandler = std::thread([task, connectionFD, clientAddress, &current_connections] {
                    task->serve(connectionFD, clientAddress);
                    current_connections--;
                    destroySocket(connectionFD);
                });
                current_connections++;
                requestHandler.detach();
            } else {
                write(connectionFD, RESPONSE_500, sizeof(RESPONSE_500));
                destroySocket(connectionFD);
            }
        }

    }
}

int Server::createSocket() {
    socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketFD == -1) {
        perror(SOCKET_FAILED);
        return -1;
    }
    return 0;
}

int Server::setReuseAddress() const {
    int yes = 1;
    int error = setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if (error) {
        perror(SET_OPT_FAILED);
    }
    return error;
}

int Server::bindSocket() {
    size_t socketLength = sizeof(serverAddress);
    int error = bind(socketFD, (struct sockaddr *) &serverAddress, socketLength);
    if (error) {
        perror(BIND_FAILED);
    }
    return error;
}

int Server::listenSocket() const {
    int error = listen(socketFD, 5);
    if (error) {
        perror(LISTEN_FAILED);
    }
    return error;
}

int Server::destroySocket(int socket) {
    int error = 0;
    error = shutdownSocket(socket) || error;
    error = closeSocket(socket) || error;

    return error;
}

int Server::closeSocket(int socket) {
    int error = close(socket);
    if (error) {
        perror(CLOSE_FAILED);
    }
    return error;
}

int Server::shutdownSocket(int socket) {
    int error = shutdown(socket, SHUT_RDWR);
    if (error) {
        perror(SHUTDOWN_FAILED);
    }
    return error;
}

Server::Server(const char *ip, uint16_t port, unsigned long max_connections,
               Protocol *service)
        : max_connections(max_connections), service(service) {
    size_t socketLength = sizeof(serverAddress);
    bzero(&serverAddress, socketLength);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ip);
    serverAddress.sin_port = htons(port);
}

#undef SOCKET_FAILED
#undef BIND_FAILED
#undef LISTEN_FAILED
#undef ACCEPT_FAILED
#undef SET_OPT_FAILED
#undef CLOSE_FAILED
#undef SHUTDOWN_FAILED
#undef RESPONSE_500
#undef POLL_TIMEOUT