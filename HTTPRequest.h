#ifndef TORRENT_TRACKER_HTTPREQUEST_H
#define TORRENT_TRACKER_HTTPREQUEST_H

#include <string>
#include <map>
#include "Request.h"

class HTTPRequest : public Request {
public:
    HTTPRequest(unsigned int ip, unsigned short port);

    void addParameter(const std::string &key, const std::string &value);

    std::string getParameter(const std::string &key);

    std::string &operator[](const std::string &key);

    bool contains(const std::string &key);

    unsigned short getPort() const;

    unsigned int getIp() const;

private:
    const unsigned short port;
    const unsigned int ip;
    std::map<std::string, std::string> parameters{};
};


#endif //TORRENT_TRACKER_HTTPREQUEST_H
