#ifndef TORRENT_TRACKER_TRACKER_SERVICE_H
#define TORRENT_TRACKER_TRACKER_SERVICE_H

#define BINARY_PEER_LENGTH 6

#include <map>
#include <unordered_set>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <regex>
#include <utility>
#include <iostream>
#include "Peer.h"
#include "TrackerRequest.h"
#include "HTTPResponse.h"
#include "StringToPrimitivesParser.h"
#include "RequestParser.h"
#include "Repository.h"
#include "Service.h"

class TrackerService : public Service {
public:

    TrackerService(unsigned long interval, unsigned long minInterval, unsigned long numWant, Repository &repository);

    static Peer getPeer(const TrackerRequest &request);

private:

    const unsigned long interval;
    const unsigned long minInterval;
    const unsigned long numWant;
    Repository &repository;
    static void peersToArray(const std::unordered_set<Peer, Hash> &vector, unsigned long numWant, char *res);
    void serve(Request &req, Response &res) override;
    std::string getTextPart(unsigned long peersInBytes, const std::string &trackerId) const;

};


#endif //TORRENT_TRACKER_TRACKER_SERVICE_H
