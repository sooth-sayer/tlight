#ifndef LIB_DI_CTOR
#define LIB_DI_CTOR

#include <utility>

namespace lib { namespace di {

  template <typename First, typename Second>
  struct SelectSecond { typedef Second type; };
  struct Any { Any(...); };

  template <typename Selector, typename T>
    struct ConstructorSelector {
      template <typename Ret, typename... Args>
        static Ret construct(Args... args) {
          return T::template construct<Ret>(args...);
        }
    };

  template <typename T>
    struct ConstructorSelector<std::false_type, T> {
      template <typename Ret, typename... Args>
        static Ret construct(Args... args) {
          return T::template base_construct<Ret>(args...);
        }
    };


  template <typename... Args>
    struct InjectorTuple;

  template <typename Inj, typename Tuple = InjectorTuple<>>
    struct Ctor {
    };

  template <typename Inj>
    struct Ctor<Inj, InjectorTuple<>> {
      template <typename Tp>
        static Tp construct(Inj) {
          return Tp();
        }

      template <typename Tp>
      static Tp create(Inj) {
        return Tp();
      }
    };


  template <typename Inj, typename First, typename... Injs>
    struct Ctor<Inj, InjectorTuple<First, Injs...>> : public Ctor<Inj, InjectorTuple<Injs...>> {
      using base = Ctor<Inj, InjectorTuple<Injs...>>;
      using self = Ctor<Inj, InjectorTuple<First, Injs...>>;

      template<typename... Args>
        static std::false_type creator(Inj inj, Any, Args...);

      template<typename Tp, typename... Args>
        static typename SelectSecond<decltype(Tp(std::declval<Args>()...)), std::true_type>::type creator(Inj inj, Tp, Args...);

      template <typename Tp>
        static Tp create(Inj& inj) {
          using selector = decltype(creator(inj, std::declval<Tp>(), std::declval<First>(), std::declval<Injs>()...));
          return ConstructorSelector<selector, self>::template construct<Tp>(inj);
        }

      template <typename Tp>
        static Tp construct(Inj& inj) {
          return Tp(inj.template get_bind_for<First>(), inj.template get_bind_for<Injs>()...);
        }
      template <typename Tp>
        static Tp base_construct(Inj& inj) {
          return base::template create<Tp>(inj);
        }
    };

}}

#endif
