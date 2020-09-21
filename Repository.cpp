#include "Repository.h"

void Repository::addPeer(const std::string &shareHash, Peer peer) {
    lock.lock();

    if (peers.contains(shareHash)) {

        auto subPeers = &peers.at(shareHash);

        if (!subPeers->set.contains(peer)) {
            if (subPeers->set.size() == maxPeers) {

                subPeers->set.erase(subPeers->queue.front());
                subPeers->queue.pop();
            }
            subPeers->queue.push(peer);
            subPeers->set.insert(peer);
        }
        lock.unlock();
        return;

    } else if (peers.size() == maxShares) {
        peers.erase(sharesQueue.front());
        sharesQueue.pop();
    }
    sharesQueue.push(shareHash);
    Peers subPeers{};
    subPeers.set.insert(peer);
    subPeers.queue.push(peer);
    peers.insert(std::make_pair(shareHash, subPeers));

    lock.unlock();

}

Repository::Repository(unsigned long maxShares, unsigned long maxPeers) : maxShares(maxShares), maxPeers(maxPeers) {}

std::unordered_set<Peer, Hash> Repository::getPeers(const std::string &shareHash) {
    lock.lock();
    std::unordered_set<Peer, Hash> result{};
    if (peers.contains(shareHash)) {
        result = peers[shareHash].set;
    }
    lock.unlock();
    return result;
}
