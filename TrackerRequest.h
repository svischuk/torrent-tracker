#ifndef TORRENT_TRACKER_TRACKERREQUEST_H
#define TORRENT_TRACKER_TRACKERREQUEST_H

#include <arpa/inet.h>
#include <string>

enum Event {
    DEFAULT, STARTED, STOPPED, COMPLETED
};

class TrackerRequest {
public:
    std::string getInfoHash() const;

    void setInfoHash(const std::string &infoHash);

    unsigned short getPort() const;

    void setPort(unsigned short port);

    unsigned long getLeft() const;

    void setLeft(unsigned long left);

    unsigned int getIP() const;

    void setIP(unsigned int ip);

    unsigned short getNumWant() const;

    void setNumWant(unsigned short numWant);

    std::string getTrackerID() const;

    void setTrackerID(const std::string &trackerID);


private:
    std::string infoHash{};
    std::string peerID{};
    unsigned short port = 0;
    unsigned long uploaded = 0;
    unsigned long downloaded = 0;
    unsigned long left = 0;
    bool compact = false;
    bool noPeerID = false;
    Event event;
    unsigned int ip = 0;
    unsigned short numWant = 0;
    std::string key{};
    std::string trackerID{};

};


#endif //TORRENT_TRACKER_TRACKERREQUEST_H
