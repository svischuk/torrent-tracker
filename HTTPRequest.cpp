#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(unsigned int ip, unsigned short port) : port(
        port), ip(ip) {
}

void HTTPRequest::addParameter(const std::string &key, const std::string &value) {
    parameters.insert(std::make_pair(key, value));
}

std::string HTTPRequest::getParameter(const std::string &key) {
    return parameters[key];
}

std::string &HTTPRequest::operator[](const std::string &key) {
    return parameters[key];
}

bool HTTPRequest::contains(const std::string &key) {
    return parameters.contains(key);
}

unsigned short HTTPRequest::getPort() const {
    return port;
}

unsigned int HTTPRequest::getIp() const {
    return ip;
}

