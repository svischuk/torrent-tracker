#ifndef TORRENT_TRACKER_STATUS_H
#define TORRENT_TRACKER_STATUS_H

#define STATUS(X) \
    (X) == OK ? "OK" :\
    (X) == NOT_FOUND ? "Not Found" :\
    (X)==INTERNAL_SERVER_ERROR? "Internal Server Error": \
    (X)==BAD_REQUEST? "Bad Request":"Unknown Error"

enum StatusCode {
    OK = 200,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    BAD_REQUEST = 400

};
#endif //TORRENT_TRACKER_STATUS_H
