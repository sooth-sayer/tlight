#ifndef LIB_DI
#define LIB_DI

#include <utility>
#include "bind.hpp"
#include "ctor.hpp"

namespace lib { namespace di {

  template <typename... T>
    class Injector;

  template <typename... T, typename... U>
    class Injector<Bind<T, U>...> : public Bind<T, U>...
    {
      using self = Injector<Bind<T, U>...>;

      public:
        Injector(const Bind<T, U>&... args) : Bind<T, U>(args)... {}

        template <typename Tp>
          Tp& get_instance() {
            return (Tp&)*this;
          }

        template <typename Tp>
          Injector<Bind<T, U>...>& get_bind_for() {
            return *this;
          }

        template <typename Tp>
          Tp create() {
            using inj_tuple = InjectorTuple<typename std::remove_reference<decltype(std::declval<self>().template get_bind_for<T>())>::type...>;
            using constructor = Ctor<self, inj_tuple>;
            return constructor::template create<Tp>(*this);
          }
    };

  template <typename... T>
    Injector<T...> make_injector(const T&... bindings)
    {
      return Injector<T...>(bindings...);
    }

}}

#endif
