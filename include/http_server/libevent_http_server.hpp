#ifndef LIBEVENT_HTTP_SERVER
#define LIBEVENT_HTTP_SERVER

#include <interfaces/http_server.hpp>
#include <event2/http.h>
#include <event2/http_struct.h>

using namespace std;

class LibeventHttpServer : iHttpServer {
};

#endif
