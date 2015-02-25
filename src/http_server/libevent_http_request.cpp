#include <http_server/libevent_http_request.hpp>
#include <cstdlib>
#include <event2/buffer.h>

LibeventHttpRequest::LibeventHttpRequest(evhttp_request *libevent_request)
  : libevent_request(libevent_request)
{ ; }

string LibeventHttpRequest::get_request_header(const string& header)
{
  evkeyvalq *request_headers = evhttp_request_get_input_headers(libevent_request);
  const char *header_value = evhttp_find_header(request_headers, header.c_str());
  return string(header_value);
}

size_t LibeventHttpRequest::get_request_data(void *out_buf, size_t out_buf_len)
{
  evbuffer *request_buffer = _get_request_buffer();
  return evbuffer_copyout(request_buffer, out_buf, out_buf_len);
}

string LibeventHttpRequest::read_request_string()
{
  evbuffer *request_buffer = _get_request_buffer();
  char *line = evbuffer_readln(request_buffer, nullptr, EVBUFFER_EOL_CRLF);
  if (!line) { throw no_more_strings{}; }

  const string& ret = string(line);
  free(line);
  return ret;
}

void LibeventHttpRequest::add_response_header(const string& header, const string& value)
{
  evkeyvalq *response_headers = evhttp_request_get_output_headers(libevent_request);
  evhttp_add_header(response_headers, header.c_str(), value.c_str());
}

void LibeventHttpRequest::add_response_string(const string& data)
{
  evbuffer *response_buffer = _get_response_buffer();
  size_t data_len = data.length() * sizeof(string::value_type);
  evbuffer_add(response_buffer, data.c_str(), data_len);
}

void LibeventHttpRequest::add_response_data(void *data, size_t data_len)
{
  evbuffer *response_buffer = _get_request_buffer();
  evbuffer_add(response_buffer, data, data_len);
}

void LibeventHttpRequest::send_reply(int code, const string& status)
{
  evhttp_send_reply(libevent_request, code, status.c_str(), _get_response_buffer());
}

void LibeventHttpRequest::send_error(int code, const string& error)
{
  evhttp_send_error(libevent_request, code, error.c_str());
}

