#ifndef TORRENT_TRACKER_PROTOCOL_H
#define TORRENT_TRACKER_PROTOCOL_H

class Protocol {
public:
    virtual void serve(int connectionFD, struct sockaddr_in clientAddress) = 0;

    virtual ~Protocol() = default;
};

#endif //TORRENT_TRACKER_PROTOCOL_H
