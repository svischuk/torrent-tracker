//
// Created by user on 9/14/20.
//

#ifndef TORRENT_TRACKER_SERVICE_H
#define TORRENT_TRACKER_SERVICE_H

#include "Request.h"
#include "Response.h"

class Service {
public:
    virtual void serve(Request &, Response &) = 0;

    virtual ~Service() = default;
};


#endif //TORRENT_TRACKER_SERVICE_H
