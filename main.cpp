#include <cstdio>
#include <csignal>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "Server.h"
#include "TrackerService.h"
#include "HTTPProtocol.h"

#define CONFIG "config"
#define IP "ip"
#define PORT "port"
#define HEADER_MAX_LENGTH "headerMaxLength"
#define MAX_CONNECTIONS "maxConnections"
#define INTERVAL "interval"
#define MIN_INTERVAL "minInterval"
#define NUM_WANT "numWant"
#define MAX_SHARES "maxShares"
#define MAX_PEERS "maxPeers"
#define IP_V4_STR_LENGTH 16
#define TIMEOUT 10000

char ip[IP_V4_STR_LENGTH] = "0.0.0.0";
unsigned short port = 80;
unsigned long headerMaxLength = 8 * 1024;
unsigned long maxConnections = 30;
unsigned long interval = 60;
unsigned long minInterval = 60;
unsigned long numWant = 30;
unsigned long maxShares = 1000;
unsigned long maxPeers = 100;

std::condition_variable condition;
bool signalFlag = false;

void signalHandler(int sig) {
    signalFlag = sig;
    condition.notify_one();
    printf("Stopping server..\n");
}

int readConfig() {

    int errors = 0;
    std::ifstream configFile(CONFIG);
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream inputStringStream(line);
        std::string stringBuffer;
        inputStringStream >> stringBuffer;
        if (stringBuffer == IP) {
            if (!(inputStringStream >> stringBuffer)) {
                errors++;
                continue;
            }
            strcpy(ip, stringBuffer.c_str());
        } else if (stringBuffer == PORT) {
            if (!(inputStringStream >> port)) {
                errors++;
            }
        } else if (stringBuffer == HEADER_MAX_LENGTH) {
            if (!(inputStringStream >> headerMaxLength)) {
                errors++;
            }
        } else if (stringBuffer == MAX_CONNECTIONS) {
            if (!(inputStringStream >> maxConnections)) {
                errors++;
            }
        } else if (stringBuffer == INTERVAL) {
            if (!(inputStringStream >> interval)) {
                errors++;
            }
        } else if (stringBuffer == MIN_INTERVAL) {
            if (!(inputStringStream >> minInterval)) {
                errors++;
            }
        } else if (stringBuffer == NUM_WANT) {
            if (!(inputStringStream >> numWant)) {
                errors++;
            }
        } else if (stringBuffer == MAX_SHARES) {
            if (!(inputStringStream >> maxShares)) {
                errors++;
            }
        } else if (stringBuffer == MAX_PEERS) {
            if (!(inputStringStream >> maxPeers)) {
                errors++;
            }
        } else {
            errors++;
        }
    }
    return 0;
}

#define DELIMETR ": "

void showConfig() {
    std::cout << IP << DELIMETR << ip << std::endl;
    std::cout << PORT << DELIMETR << port << std::endl;
    std::cout << HEADER_MAX_LENGTH << DELIMETR << headerMaxLength << std::endl;
    std::cout << MAX_CONNECTIONS << DELIMETR << maxConnections << std::endl;
    std::cout << INTERVAL << DELIMETR << interval << std::endl;
    std::cout << MIN_INTERVAL << DELIMETR << minInterval << std::endl;
    std::cout << NUM_WANT << DELIMETR << numWant << std::endl;
    std::cout << MAX_SHARES << DELIMETR << maxShares << std::endl;
    std::cout << MAX_PEERS << DELIMETR << maxPeers << std::endl;
}

bool fileExist(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}

int main() {

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGABRT, signalHandler);
    if (fileExist(CONFIG)) {
        int errors = readConfig();
        if (errors) {
            printf("Config file loaded with %d errors..\n", errors);
        } else {
            printf("Config file loaded successfully..\n");
        }
    } else {
        printf("Config file not found. Using default settings..\n");
    }
    showConfig();
    Repository repository(maxShares, maxPeers);
    TrackerService service(interval, minInterval, numWant, repository);
    HTTPProtocol protocol(service, headerMaxLength);
    Server server(ip, port, maxConnections, &protocol);
    if (server.start()) {
        printf("Server starting failed..\n");
        return server.stop();
    }
    printf("Server started successfully..\n");
    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait_for(lock, std::chrono::seconds(TIMEOUT), []() { return signalFlag; });
    if (server.stop()) {
        printf("Server stopped with errors..\n");
    }
    printf("Server stopped successfully..\n");
    return 0;

}

#undef CONFIG
#undef IP
#undef PORT
#undef HEADER_MAX_LENGTH
#undef MAX_CONNECTIONS
#undef INTERVAL
#undef MIN_INTERVAL
#undef NUM_WANT
#undef MAX_SHARES
#undef MAX_PEERS
#undef IP_V4_STR_LENGTH
#undef TIMEOUT
#undef DELIMETR
