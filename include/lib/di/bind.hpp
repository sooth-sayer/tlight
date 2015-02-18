#ifndef LIB_DI_BIND
#define LIB_DI_BIND

namespace lib { namespace di {

  template <typename T, typename U = T>
    class Bind
    {
      public:
        Bind() : value{nullptr} {}

        Bind<T, U>(const Bind<T, U>& obj) : value{obj.value} { }

        operator T&() {
          if (value == nullptr) {
            value = new U;
          }
          return *value;
        }

      private:
        T* value;
    };

  template <typename T>
    class Bind<T, T>
    {
      public:
        Bind() : value{nullptr} {}
        /* TODO: implement destructor */

        Bind<T, T>& operator ()(T& val) {
          value = &val;
          return *this;
        }

        Bind<T, T>& operator ()(const T& val) {
          value = new T(val);
          return *this;
        }

        Bind<T, T>(const Bind<T, T>& obj) : value(obj.value) {}

        operator T&() {
          return *value;
        }

      private:
        T* value;
    };

  template <typename T, typename U = T>
    Bind<T, U> bind{};

}}
#endif
