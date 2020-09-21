#include "Peer.h"

Peer::Peer(unsigned int ip, unsigned short port) : ip(ip), port(port) {
}

unsigned int Peer::getIp() const {
    return ip;
}

unsigned short Peer::getPort() const {
    return port;
}


bool operator==(const Peer &a, const Peer &b) {
    return a.port == b.port && a.ip == b.ip;
}