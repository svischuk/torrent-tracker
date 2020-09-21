#include "HTTPProtocol.h"

void HTTPProtocol::serve(int connectionFD, struct sockaddr_in clientAddress) {
    HTTPResponse httpResponse("HTTP/1.1", "text/plain; charset=utf-8");
    auto buff = new char[maxRequestLength];
    bzero(buff, maxRequestLength);
    read(connectionFD, buff, maxRequestLength);
    auto ip = clientAddress.sin_addr.s_addr;
    auto port = clientAddress.sin_port;
    HTTPRequest request(ip, port);
    fillParameters(buff, request);
    delete[] buff;

    service.serve(request, httpResponse);
    auto response = httpResponse.getResponse();
    auto responseLength = httpResponse.getResponseLength();
    write(connectionFD, response, responseLength);
}

void HTTPProtocol::fillParameters(std::string s, HTTPRequest &request) {
    std::regex keysRegex(R"(\?(.+?)[\r|\n|\$\s])");
    std::smatch keysMatches;
    if (std::regex_search(s, keysMatches, keysRegex)) {
        s = keysMatches[1].str();
        auto strings = split(s, "&");
        for (auto &string : strings) {
            auto pair = split(string, "=");
            if (pair.size() >= 2) {
                request.addParameter(pair[0], pair[1]);
            }
        }
    }
}

std::vector<std::string> HTTPProtocol::split(std::string string, const std::string &delimiter) {
    auto strings = std::vector<std::string>();
    size_t pos;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        strings.push_back(token);
        string.erase(0, pos + delimiter.length());
    }
    strings.push_back(string);
    return strings;
}

HTTPProtocol::HTTPProtocol(Service &service, unsigned long maxRequestLength) : service(service),
                                                                               maxRequestLength(maxRequestLength) {}
