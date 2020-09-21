#include "TrackerRequestParser.h"

#define INFO_HASH "info_hash"
#define PEER_ID "peer_id"
#define PORT "port"
#define UPLOADED "uploaded"
#define DOWNLOADED "downloaded"
#define LEFT "left"
#define COMPACT "compact"
#define NO_PEER_ID "no_peer_id"
#define EVENT "event"
#define IP "ip"
#define NUMWANT "numwant"
#define KEY "key"
#define TRACKERID "trackerid"

TrackerRequest TrackerRequestParser::parse(HTTPRequest &request) {

    TrackerRequest trackerRequest{};
    if (request.contains(INFO_HASH)) {
        parseInfoHash(request[INFO_HASH], trackerRequest);
    }
    if (request.contains(PORT)) {
        parsePort(request[PORT], trackerRequest);
    }
    if (request.contains(LEFT)) {
        parseLeft(request[LEFT], trackerRequest);
    }
    if (request.contains(IP)) {
        parseIP(request[IP], trackerRequest);
    } else {
        trackerRequest.setIP(request.getIp());
    }
    if (request.contains(NUMWANT)) {
        parseNumWant(request[NUMWANT], trackerRequest);
    }
    if (request.contains(TRACKERID)) {
        parseTrackerID(request[TRACKERID], trackerRequest);
    }
    return trackerRequest;
}

int TrackerRequestParser::parseInfoHash(std::string str, TrackerRequest &request) {

    for (unsigned long i=0; i < str.size() ; i++) {
        unsigned char c=str.c_str()[i];
        if (!std::isalnum(c)&&c!='%'){
            char buf[3]{0, 0, 0};
            char temp= toHex(c >> 4);
            int index=0;
            if (temp != 0){
                buf[index++]='%';
                buf[index++]=temp;
            }
            buf[index]= toHex(c);
            str.replace(i,1,buf);
        }
    }
    std::for_each(str.begin(), str.end(), [](char &c) {
        c = static_cast<char>(std::toupper(c));
    });
    request.setInfoHash(str);
    return 0;
}
char TrackerRequestParser::toHex(unsigned char c){
    auto t = c & 0xf;
    return t += t < 10 ? '0' : 'A'-10;
}
int TrackerRequestParser::parsePort(const std::string &str, TrackerRequest &request) {
    unsigned short port = 0;
    int error = StringToPrimitivesParser::parse(str, &port);
    if (!error) {
        request.setPort(htons(port));
        return 0;
    }
    return error;
}

int TrackerRequestParser::parseLeft(const std::string &str, TrackerRequest &request) {
    unsigned long left;
    int error = StringToPrimitivesParser::parse(str, &left);
    if (!error) {
        request.setLeft(left);
        return 0;
    }
    return error;
}

int TrackerRequestParser::parseIP(const std::string &str, TrackerRequest &request) {
    unsigned int ip;
    int error = inet_net_pton(AF_INET, str.c_str(), &ip, str.size());
    if (error <= 0) {
        return -1;
    }
    request.setIP(ip);
    return 0;
}

int TrackerRequestParser::parseNumWant(const std::string &str, TrackerRequest &request) {
    unsigned short numwant;
    int error = StringToPrimitivesParser::parse(str, &numwant);
    if (!error) {
        request.setNumWant(numwant);
        return 0;
    }
    return error;
}

int TrackerRequestParser::parseTrackerID(const std::string &str, TrackerRequest &request) {
    request.setTrackerID(str);
    return 0;
}

void TrackerRequestParser::replaceAll(std::string &str, const std::string &from, const std::string &to) {
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
}

#undef INFO_HASH
#undef PEER_ID
#undef PORT
#undef UPLOADED
#undef DOWNLOADED
#undef LEFT
#undef COMPACT
#undef NO_PEER_ID
#undef EVENT
#undef IP
#undef NUMWANT
#undef KEY
#undef TRACKERID