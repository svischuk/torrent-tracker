cmake_minimum_required(VERSION 3.16)
project(torrent_tracker)

set(CMAKE_CXX_STANDARD 20)

add_executable(torrent_tracker main.cpp Server.cpp Server.h Peer.h Peer.cpp TrackerService.cpp TrackerService.h TrackerRequest.cpp TrackerRequest.h StringToPrimitivesParser.cpp StringToPrimitivesParser.h TrackerRequestParser.cpp TrackerRequestParser.h Repository.cpp Repository.h HTTPResponse.cpp HTTPResponse.h HTTPProtocol.cpp HTTPProtocol.h Protocol.h Service.h HTTPRequest.cpp HTTPRequest.h Status.h Request.h Response.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-long-long -pedantic -lresolv -pthread")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(torrent_tracker ${CMAKE_THREAD_LIBS_INIT})