#ifndef TORRENT_TRACKER_HTTPPROTOCOL_H
#define TORRENT_TRACKER_HTTPPROTOCOL_H

#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <regex>
#include <utility>
#include <iostream>
#include "Protocol.h"
#include "Service.h"
#include "HTTPResponse.h"
#include "TrackerRequest.h"
#include "RequestParser.h"
#include "HTTPRequest.h"

class HTTPProtocol : public Protocol {

public:

    HTTPProtocol(Service &service, unsigned long maxRequestLength);

    void serve(int connectionFD, struct sockaddr_in clientAddress) override;

private:
    Service &service;

    const unsigned long maxRequestLength;

    static std::vector<std::string> split(std::string string, const std::string &delimiter);

    static void fillParameters(std::string s, HTTPRequest &request);
};


#endif //TORRENT_TRACKER_HTTPPROTOCOL_H
