#include "HTTPResponse.h"

#define SPACE " "
#define NL "\r\n"

void HTTPResponse::appendContent(const char *src, unsigned long length) {

    if (content) {
        content = static_cast<char *>(reallocarray(content, contentLength + length, sizeof(char)));
    } else {
        content = (char *) malloc(length);
    }
    memcpy(content + contentLength, src, length);
    contentLength += length;
}

void HTTPResponse::appendContent(const std::string &src) {
    appendContent(src.c_str(), src.size());
}

char *HTTPResponse::getResponse() {
    std::string headerString;
    headerString.append(protocol);
    headerString.append(SPACE);
    headerString.append(std::to_string(statusCode));
    headerString.append(SPACE);
    headerString.append(STATUS (statusCode));
    headerString.append(NL);
    headerString.append("Content-type: ");
    headerString.append(contentType);
    headerString.append(NL);
    headerString.append("Content-Length: ");
    headerString.append(std::to_string(contentLength));
    headerString.append(NL);
    headerString.append(NL);

    const char *header = headerString.c_str();
    auto headerLength = headerString.size();

    response = (char *) realloc(response, headerLength + contentLength);

    memcpy(response, header, headerLength);
    memcpy(response + headerLength, content, contentLength);

    responseLength = headerLength + contentLength;
    return response;
}

HTTPResponse::HTTPResponse(std::string aProtocol, std::string contentType) : protocol(std::move(aProtocol)),
                                                                             contentType(std::move(contentType)) {
    statusCode = OK;

}

unsigned long HTTPResponse::getResponseLength() const {
    return responseLength;
}

unsigned short HTTPResponse::getStatusCode() const {
    return statusCode;
}

void HTTPResponse::setStatusCode(unsigned short statusCode) {
    HTTPResponse::statusCode = statusCode;
}
