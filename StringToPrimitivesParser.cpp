#include "StringToPrimitivesParser.h"

int StringToPrimitivesParser::parse(const std::string &str, unsigned short *value) {

    try {
        int temp = std::stoi(str);
        if (temp < 0 || temp > UINT16_MAX) {
            return -2;
        }
        *value = temp;
        return 0;
    }

    catch (const std::invalid_argument &ia) {
        return -1;
    }

    catch (const std::out_of_range &oor) {
        return -2;
    }

    catch (const std::exception &e) {
        return -3;
    }

}

int StringToPrimitivesParser::parse(const std::string &str, unsigned long *value) {

    try {
        *value = std::stoul(str);
        return 0;
    }

    catch (const std::invalid_argument &ia) {
        return -1;
    }

    catch (const std::out_of_range &oor) {
        return -2;
    }

    catch (const std::exception &e) {
        return -3;
    }
}


int StringToPrimitivesParser::parse(const std::string &str, bool *value) {
    if (str == "1") {
        *value = true;
        return 0;
    } else if (str == "0") {
        *value = false;
        return 0;
    } else {
        return -1;
    }
}
