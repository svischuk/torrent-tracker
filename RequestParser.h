#ifndef TORRENT_TRACKER_REQUESTPARSER_H
#define TORRENT_TRACKER_REQUESTPARSER_H

#include <map>
#include <regex>
#include <arpa/inet.h>
#include <iostream>
#include <algorithm>
#include "TrackerRequest.h"
#include "StringToPrimitivesParser.h"
#include "HTTPRequest.h"

class RequestParser {
public:
    static TrackerRequest parse(HTTPRequest &request);

private:
    static int parsePort(const std::string &str, TrackerRequest &request);

    static int parseLeft(const std::string &str, TrackerRequest &request);

    static int parseIP(const std::string &str, TrackerRequest &request);

    static int parseNumWant(const std::string &str, TrackerRequest &request);

    static int parseTrackerID(const std::string &str, TrackerRequest &request);

    static int parseInfoHash(std::string str, TrackerRequest &request);

    static void replaceAll(std::string &str, const std::string &from, const std::string &to);
};


#endif //TORRENT_TRACKER_REQUESTPARSER_H
