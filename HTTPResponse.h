#ifndef TORRENT_TRACKER_HTTPRESPONSE_H
#define TORRENT_TRACKER_HTTPRESPONSE_H

#include <set>
#include <string>
#include <map>
#include <cstring>
#include <utility>
#include "Status.h"
#include "Response.h"

class HTTPResponse : public Response {

public:
    HTTPResponse(std::string aProtocol, std::string contentType);

    ~HTTPResponse() override {
        if (content)free(content);
        if (response)free(response);
    }

    unsigned long getResponseLength() const;

    char *getResponse();

    void appendContent(const std::string &src);

    void appendContent(const char *src, unsigned long length);

private:
    unsigned short statusCode;
public:
    unsigned short getStatusCode() const;

    void setStatusCode(unsigned short statusCode);

private:
    std::string protocol;
    std::string contentType;
    unsigned long contentLength = 0;
    char *content = nullptr;
    char *response = nullptr;
    unsigned long responseLength = 0;

};


#endif //TORRENT_TRACKER_HTTPRESPONSE_H
