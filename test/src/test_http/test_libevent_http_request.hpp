// Libevent based Http request test

#include <utility>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <event2/buffer.h>
#include <interfaces/http_server.hpp>
#include <http_server/libevent_http_request.hpp>

using namespace std;

class LibeventHttpRequestTest : public CxxTest::TestSuite
{
  public:
    void setUp() {
      evhttp_req = { evhttp_request_new(nullptr, nullptr), evhttp_request_free };
      auto headers = evhttp_request_get_input_headers(evhttp_req.get());
      evhttp_add_header(headers, "Accept", ACCEPT_HEADER.c_str());
      evhttp_add_header(headers, "Connection", CONNECTION_HEADER.c_str());

      auto request_buffer = evhttp_request_get_input_buffer(evhttp_req.get());
      evbuffer_add(request_buffer, REQUEST_DATA.c_str(), REQUEST_DATA.length());

      request = unique_ptr<iHttpRequest>{new LibeventHttpRequest(evhttp_req.get())};
    }

    void tearDown() {
    }

    void testGetRequestHeaders() {
      const string& connection_header = request->get_request_header("Connection");
      TS_ASSERT_EQUALS(connection_header, CONNECTION_HEADER);
    }

    void testGetRequestData() {
      char buf[1024];
      size_t data_length = request->get_request_data(buf, sizeof(buf) / sizeof(char));
      TS_ASSERT_EQUALS(data_length, REQUEST_DATA.length());
    }

    void testGetRequestStrings() {
      const string& line1 = request->read_request_string();
      TS_ASSERT_EQUALS(line1, "test#1");
      request->read_request_string();

      const string& line2 = request->read_request_string();
      TS_ASSERT_EQUALS(line2, "test#3");

      TS_ASSERT_THROWS(request->read_request_string(), no_more_strings);
    }

  private:
    const string CONNECTION_HEADER = "close";
    const string ACCEPT_HEADER = "text/plain";
    const string REQUEST_DATA = "test#1\ntest#2\ntest#3\n";

    unique_ptr<iHttpRequest> request;
    // FIXME: Stub evhttp_request
    unique_ptr<evhttp_request, decltype(&evhttp_request_free)> evhttp_req {nullptr, evhttp_request_free};
};
