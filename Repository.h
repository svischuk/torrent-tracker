#ifndef TORRENT_TRACKER_REPOSITORY_H
#define TORRENT_TRACKER_REPOSITORY_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <mutex>
#include <unordered_set>
#include <queue>
#include <functional>
#include "Peer.h"

struct Hash {
    size_t operator()(const Peer &peer) const noexcept {
        return peer.getIp() * 31 + peer.getPort();
    }
};

struct Peers {
    std::unordered_set<Peer, Hash> set{};
    std::queue<Peer> queue{};
};

class Repository {
public:
    Repository(unsigned long maxShares, unsigned long maxPeers);

    std::unordered_set<Peer, Hash> getPeers(const std::string &shareHash);

    void addPeer(const std::string &shareHash, Peer peer);

private:
    std::map<std::string, Peers> peers{};
    std::queue<std::string> sharesQueue{};
    const unsigned long maxShares;
    const unsigned long maxPeers;
    std::mutex lock;

};


#endif //TORRENT_TRACKER_REPOSITORY_H
