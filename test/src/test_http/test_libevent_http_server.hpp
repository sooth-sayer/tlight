// Libevent based Http server test

#include <test_helper.hpp>
#include <utility>
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <interfaces/http_server.hpp>
#include <http_server/libevent_http_server.hpp>

using namespace test::test_helper;

class LibeventHttpServerTest : public CxxTest::TestSuite
{
  std::unique_ptr<iHttpServer> server;

  public:
    void setUp() {
      /* server = std::unique_ptr<iHttpServer>(new LibeventHttpServer{}); */
      /* server->start("127.0.0.1", 44444); */
    }

    void tearDown() {
      /* server->stop(); */
    }

    void testServerEchoResponse(void) {
      HttpClient::get("http://google.com");
    }
};
