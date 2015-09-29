#include <http_server/libevent_http_server.hpp>

void LibeventHttpServer::start(const string& address, int port)
{
}

void LibeventHttpServer::stop()
{
}

void LibeventHttpServer::register_route_handler(const string& route, void (*handler) (iHttpRequest& req))
{
}
