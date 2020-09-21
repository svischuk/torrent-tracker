#include "TrackerRequest.h"

std::string TrackerRequest::getInfoHash() const {
    return infoHash;
}

void TrackerRequest::setInfoHash(const std::string &infoHash) {
    TrackerRequest::infoHash = infoHash;
}


unsigned short TrackerRequest::getPort() const {
    return port;
}

void TrackerRequest::setPort(unsigned short port) {
    TrackerRequest::port = port;
}


unsigned long TrackerRequest::getLeft() const {
    return left;
}

void TrackerRequest::setLeft(unsigned long left) {
    TrackerRequest::left = left;
}

unsigned int TrackerRequest::getIP() const {
    return ip;
}

void TrackerRequest::setIP(unsigned int ip) {
    TrackerRequest::ip = ip;
}

unsigned short TrackerRequest::getNumWant() const {
    return numWant;
}

void TrackerRequest::setNumWant(unsigned short numWant) {
    TrackerRequest::numWant = numWant;
}


std::string TrackerRequest::getTrackerID() const {
    return trackerID;
}

void TrackerRequest::setTrackerID(const std::string &trackerID) {
    TrackerRequest::trackerID = trackerID;
}

