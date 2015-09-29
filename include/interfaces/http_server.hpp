#ifndef HTTP_SERVER_INTERFACE
#define HTTP_SERVER_INTERFACE

#include <stdexcept>
#include <string>

using namespace std;

struct no_more_strings : runtime_error {
  no_more_strings() : runtime_error("No more strings in the buffer") { ; }
};

struct iHttpRequest {
  virtual string get_request_header(const string& header) = 0;

  virtual size_t get_request_data(void *out_buf, size_t out_buf_len) = 0;
  virtual string read_request_string() = 0;

  virtual void add_response_header(const string& header, const string& value) = 0;
  virtual void add_response_string(const string& data) = 0;
  virtual void add_response_data(void *data, size_t data_len) = 0;

  virtual void send_reply(int code, const string& status) = 0;
  virtual void send_error(int code, const string& error) = 0;

  virtual ~iHttpRequest() { ; }
};

struct iHttpServer {
  virtual void start(const string& address, int port) = 0;
  virtual void stop() = 0;
  virtual void register_route_handler(const string& route, void (*handler) (iHttpRequest& req)) = 0;

  virtual ~iHttpServer() { ; }
};

#endif
