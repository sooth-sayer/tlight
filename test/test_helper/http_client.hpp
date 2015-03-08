#ifndef TEST_HELPER_HTTP_CLIENT
#define TEST_HELPER_HTTP_CLIENT

#include <curl_easy.h>
#include <curl_pair.h>
#include <curl_sender.h>
#include <curl_receiver.h>
#include <sstream>

using curl::curl_easy;
using curl::curl_pair;
using curl::curl_sender;
using curl::curl_receiver;

using namespace std;

namespace test { namespace test_helper {

class HttpClient {
  public:
    static string get(string url) {
      curl_easy easy;
      easy.add(curl_pair<CURLoption, string>(CURLOPT_URL, url));
      easy.add(curl_pair<CURLoption, bool>(CURLOPT_CONNECT_ONLY, true));
      easy.perform();

      curl_sender<string> sender(easy);
      sender.send("GET / HTTP/1.1\r\n\r\n");

      stringstream result{};

      for (;;) {
        try {
          curl_receiver<char, 65536> receiver;
          receiver.receive(easy);

          if (receiver.get_received_bytes()) {
            for (size_t i = 0; i < receiver.get_received_bytes(); ++i) {
              result << receiver.get_buffer()[i];
            }
            easy.reset();
          }
        } catch (curl_easy_exception e) {
          break;
        }
      }

      return result.str();
    }
};

}}

#endif
