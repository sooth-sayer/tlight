// DI test

#include <utility>
#include <cxxtest/TestSuite.h>
#include "fixtures_di.hpp"
#include <lib.hpp>

using namespace lib;

class DITest : public CxxTest::TestSuite
{
    di::Bind<IFirst, First> bind_ifirst;
    di::Bind<ISecond> bind_isecond;
    Second second;

  public:

    void setUp() {
      second = Second{1.1};
      bind_ifirst = di::bind<IFirst, First>;
      bind_isecond = di::bind<ISecond>(second);
    }

    void tearDown() {
    }

    void testBinds() {
      IFirst& first_instance = (IFirst&)bind_ifirst;
      ISecond& second_instance = (ISecond&)bind_isecond;

      TS_ASSERT_EQUALS(first_instance.run(), first_default.run());
      TS_ASSERT_EQUALS(second_instance.run(), second.run());
    }

    void testInjectorCreation(void) {
      auto injector = di::make_injector(bind_ifirst, bind_isecond, di::bind<int>(4));
      auto use_ifirst_isecond = injector.create<UseIFirstISecond>();

      TS_ASSERT_EQUALS(use_ifirst_isecond.first_run(), first_default.run());
      TS_ASSERT_EQUALS(use_ifirst_isecond.second_run(), second.run());
    }
};
