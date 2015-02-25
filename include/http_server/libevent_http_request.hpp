#ifndef LIBEVENT_HTTP_REQUEST
#define LIBEVENT_HTTP_REQUEST

#include <interfaces/http_server.hpp>
#include <event2/http.h>
#include <event2/http_struct.h>

using namespace std;

class LibeventHttpRequest : public iHttpRequest {
  public:
    LibeventHttpRequest(evhttp_request *libevent_request);
    string get_request_header(const string& header);

    size_t get_request_data(void *out_buf, size_t out_buf_len);
    string read_request_string();

    void add_response_header(const string& header, const string& value);
    void add_response_string(const string& data);
    void add_response_data(void *data, size_t data_len);

    void send_reply(int code, const string& status);
    void send_error(int code, const string& error);

  private:
    evbuffer *_get_request_buffer() { return evhttp_request_get_input_buffer(libevent_request); }
    evbuffer *_get_response_buffer() { return evhttp_request_get_output_buffer(libevent_request); }
    evhttp_request *libevent_request;
};

#endif
