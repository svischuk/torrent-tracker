#ifndef TORRENT_TRACKER_STRINGTOPRIMITIVESPARSER_H
#define TORRENT_TRACKER_STRINGTOPRIMITIVESPARSER_H


#include <string>
#include <stdexcept>

class StringToPrimitivesParser {
public:
    static int parse(const std::string &str, unsigned short *value);

    static int parse(const std::string &str, unsigned long *value);

    static int parse(const std::string &str, bool *value);
};


#endif //TORRENT_TRACKER_STRINGTOPRIMITIVESPARSER_H
