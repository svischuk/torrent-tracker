#ifndef TORRENT_TRACKER_SERVER_H
#define TORRENT_TRACKER_SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <poll.h>
#include "Protocol.h"

class Server {
public:

    Server(const char *ip, uint16_t port, unsigned long max_connections,
           Protocol *service);

    int start();

    int stop();

    bool isRunning() const;


private:
    int socketFD{};

    bool running = false;

    void listener() const;

    int createSocket();

    int setReuseAddress() const;

    struct sockaddr_in serverAddress{};

    int bindSocket();

    int listenSocket() const;

    const unsigned long max_connections;

    Protocol *service;


    static int destroySocket(int socket);

    static int shutdownSocket(int socket);

    static int closeSocket(int socket);
};


#endif //TORRENT_TRACKER_SERVER_H
