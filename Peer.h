#ifndef TORRENT_TRACKER_PEER_H
#define TORRENT_TRACKER_PEER_H

#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <utility>
#include <chrono>

class Peer {
public:
    Peer(unsigned int ip, unsigned short port);


    unsigned int getIp() const;

    unsigned short getPort() const;

    friend bool operator==(const Peer &a, const Peer &b);

private:
    const unsigned int ip;
    const unsigned short port;
};


#endif //TORRENT_TRACKER_PEER_H
