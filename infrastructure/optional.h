// vim: sw=3 ts=3 expandtab cindent
#pragma once

#ifdef __has_include
#  if __has_include(<optional>)
#    include <optional>
#    define FIREPP_HAS_STD_OPTIONAL
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
#    define FIREPP_HAS_STD_EXPERIMENTAL_OPTIONAL
#  elif __has_include(<boost/optional.hpp>)
#    include <boost/optional.hpp>
#    define FIREPP_HAS_BOOST_OPTIONAL
#  else
#    error "Cannot find implementation for optional."
#  endif
#endif

namespace firepp {
namespace infrastructure {
namespace details_ {
#if defined(FIREPP_HAS_STD_OPTIONAL)
   template<class T>
   using optional_value = std::optional<T>;
#elif defined(FIREPP_HAS_STD_EXPERIMENTAL_OPTIONAL)
   template<class T>
   using optional_value = std::experimental::optional<T>;
#elif defined(FIREPP_HAS_BOOST_OPTIONAL)
   template<class T>
   using optional_value = boost::optional<T>;
#endif
}
}
}
