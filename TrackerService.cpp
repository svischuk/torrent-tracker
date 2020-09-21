#include "TrackerService.h"

TrackerService::TrackerService(unsigned long interval, unsigned long minInterval, unsigned long numWant,
                               Repository &repository) : interval(interval),
                                                         minInterval(minInterval),
                                                         numWant(numWant),
                                                         repository(
                                                                 repository) {

}

Peer TrackerService::getPeer(const TrackerRequest &request) {
    return Peer(request.getIP(), request.getPort());
}


void TrackerService::serve(Request &req, Response &res) {
    auto &request = static_cast<HTTPRequest &>(req);
    auto &response = static_cast<HTTPResponse &>(res);
    TrackerRequest trackerRequest = RequestParser::parse(request);

    auto peer = getPeer(trackerRequest);
    const auto &share = trackerRequest.getInfoHash();
    if(trackerRequest.getPort()){
        repository.addPeer(share, peer);
    } else{
        response.setStatusCode(BAD_REQUEST);
    }
    auto peers=repository.getPeers(share);
    const std::string &trackerId = trackerRequest.getTrackerID();

    auto requestNumWant = trackerRequest.getNumWant();
    auto responseNumWant = requestNumWant == 0 || requestNumWant > numWant ?
                           numWant : requestNumWant;
    auto peersSize = responseNumWant > peers.size() ? peers.size() : responseNumWant;
    auto peersInBytes = peersSize * BINARY_PEER_LENGTH;

    char *peersArray = new char[peersInBytes];
    peersToArray(peers, peersSize, peersArray);
    
    response.appendContent(getTextPart(peersInBytes, trackerId));
    response.appendContent(peersArray, peersInBytes);
    response.appendContent("e");
    delete[]  peersArray;

}
std::string TrackerService::getTextPart(unsigned long peersInBytes, const std::string& trackerId) const {
    std::string response;
    response.append("d");
    if (!trackerId.empty()) {
        response.append("9:trackerid");
        response.append(std::to_string(trackerId.size()));
        response.append(":");
        response.append(trackerId);
    }
    response.append("8:intervali");
    response.append(std::to_string(interval));
    response.append("e12:min intervali");
    response.append(std::to_string(minInterval));
    response.append("e5:peers");
    response.append(std::to_string(peersInBytes));
    response.append(":");
    return response;
}
void TrackerService::peersToArray(const std::unordered_set<Peer, Hash> &vector, unsigned long numWant, char *res) {
    for (auto iterator = vector.begin(); iterator != vector.end() && numWant > 0; iterator++, numWant--) {

        unsigned int ip = iterator->getIp();
        std::memcpy(res, &ip, 4);
        res += 4;

        auto port = iterator->getPort();
        std::memcpy(res, &port, 2);
        res += 2;
    }
}
