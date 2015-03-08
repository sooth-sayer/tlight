#include <memory>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <event2/event.h>
#include <event2/http.h>

#include <event2/buffer.h>

using namespace std;

const char *SrvAddress = "127.0.0.1";
const std::uint16_t SrvPort = 5555;

class TestM {
  public:
    TestM(int y) {
      _y = new int(y);
      cout << "_y address " << _y << endl;
      cout << "this address " << this << endl;
    }

    TestM(const TestM& obj) {
      cout << "Copying constructor" << endl;
      _y = new int(*(obj._y));
    }

    void method() {
      *_y = 10;
    }

    void method2() const {
    }

    ~TestM() {
      cout << "Destructor" << endl;
      if (_y) { delete _y; }
    }

    int *_y;

    TestM(TestM&& obj) {
      cout << "Moving constructor " << this << endl;
      _y = obj._y;
      obj._y = nullptr;
    }

    TestM& operator=(const TestM& obj) {
      cout << "Copying operator=" << endl;
      _y = new int(*(obj._y));
      return *this;
    }

    TestM& operator=(TestM&& obj) {
      cout << "Moving operator=" << endl;
      std::swap(obj._y, _y);
      return *this;
    }
};

TestM getTestM() {
  return TestM(4);
}

int main()
{
  std::unique_ptr<event_base, decltype(&event_base_free)> EventBase(event_base_new(), &event_base_free);
  std::unique_ptr<evhttp, decltype(&evhttp_free)> Server(evhttp_new(EventBase.get()), &evhttp_free);

  if (!Server)
  {
    std::cerr << "Failed to init http server." << std::endl;
    return -1;
  }

  if (evhttp_bind_socket(Server.get(), SrvAddress, SrvPort) == -1) {
    cout << "Failed to bind to socket." << endl;
  }

  void (*OnReq)(evhttp_request *req, void *) = [] (evhttp_request *req, void *)
  {
    auto *OutBuf = evhttp_request_get_output_buffer(req);
    if (!OutBuf)
      return;
    evbuffer_add_printf(OutBuf, "<html><body><center><h1>Hello Wotld!</h1></center></body></html>");
    evhttp_send_reply(req, HTTP_OK, "", OutBuf);
  };

  evhttp_set_gencb(Server.get(), OnReq, nullptr);

  /* if (event_base_dispatch(EventBase.get()) == -1) */
  /* { */
  /*   std::cerr << "Failed to run messahe loop." << std::endl; */
  /*   return -1; */
  /* } */

  TestM tm = getTestM();
  return 0;
}
