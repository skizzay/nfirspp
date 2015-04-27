// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_BITS_VALUE_COMPONENT_H__
#define NFIRSPP_BUSINESS_BITS_VALUE_COMPONENT_H__

#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <experimental/string_view>

namespace firepp {
namespace business {
namespace details_ {

template<class Tag, std::size_t N>
class value_component {
public:
   static_assert((0 < N) && (N <= std::numeric_limits<uint8_t>::max()),
                "N must be in (0, std::numeric_limits<uint8_t>::max()].");

   inline value_component() noexcept :
      value()
   {
      value[0] = '\0';
   }

   template<class... Args>
   explicit inline value_component(std::experimental::string_view v, Args && ... args) :
      value()
   {
      using std::forward;
      if (!Tag::validate_and_assign(value, v, forward<Args>(args)...)) {
         std::ostringstream error;
         error << '\'' << v << "' is an invalid " << Tag::type_name() << '.';
         throw std::invalid_argument{error.str()};
      }
      n = static_cast<uint8_t>(v.size());
   }

   constexpr inline bool valid() const noexcept {
      return value[0] != '\0';
   }

   constexpr inline std::experimental::string_view to_string() const noexcept {
      return valid() ? std::experimental::string_view{value, n} : std::experimental::string_view{nullptr, 0};
   }

private:
   char value[N+1];
   uint8_t n;
};


struct length_validation_and_assignment {
   template<std::size_t N>
   static inline bool validate_and_assign(char (&value)[N], std::experimental::string_view v) {
      using std::copy;
      using std::begin;
      using std::end;

      if (v.empty() || (v.size() > N)) {
         return false;
      }
      copy(begin(v), end(v), begin(value));
      value[v.size()] = '\0';
      return true;
   }
};


template<class Matches>
inline void copy_to_value(const Matches &, char *value, std::index_sequence<>) noexcept {
   *value = '\0';
}


template<class Matches, std::size_t I, std::size_t... Indices>
inline void copy_to_value(const Matches &matches, char *value, std::index_sequence<I, Indices...>) noexcept {
   using std::copy;

   if (I < matches.size()) {
      auto m = matches[I];
      value = copy(m.first, m.second, value);
      copy_to_value(matches, value, std::index_sequence<Indices...>{});
   }
   else {
      copy_to_value(matches, value, std::index_sequence<>{});
   }
}


template<class, class> struct regex_validation_and_assignment;

template<class CRTP, std::size_t... Indices>
struct regex_validation_and_assignment<CRTP, std::index_sequence<Indices...>> {
   template<class Alloc=std::allocator<std::sub_match<std::experimental::string_view::const_iterator>>>
   static inline bool validate_and_assign(char *value, std::experimental::string_view v, const Alloc &alloc={}) {
      using std::copy;
      using std::begin;
      using std::end;

      std::match_results<std::experimental::string_view::const_iterator, Alloc> matches{alloc};

      if (std::regex_match(begin(v), end(v), matches, CRTP::get_regex())) {
         copy_to_value(matches, value, std::index_sequence<Indices...>{});
         return true;
      }

      return false;
   }
};


template<class CRTP>
struct crtp_adaptor_tag final : length_validation_and_assignment {
   static inline const char *type_name() noexcept {
      return CRTP::type_name();
   }
};


template<class CRTP, std::size_t AbbreviatedSize>
class abbreviated_and_full {
   friend CRTP;

public:
   abbreviated_and_full() = default;
   abbreviated_and_full(const abbreviated_and_full &) noexcept = default;
   abbreviated_and_full(abbreviated_and_full &&) noexcept = default;
   ~abbreviated_and_full() noexcept = default;

   abbreviated_and_full & operator =(const abbreviated_and_full &) noexcept = default;
   abbreviated_and_full & operator =(abbreviated_and_full &&) noexcept = default;

   inline std::experimental::string_view abbreviated() const noexcept {
      return abbreviated_.to_string();
   }

   inline std::experimental::string_view full() const noexcept {
      return full_;
   }

   inline bool valid() const noexcept {
      return !(abbreviated().empty() || full().empty());
   }

private:
   value_component<crtp_adaptor_tag<CRTP>, AbbreviatedSize> abbreviated_ = {};
   std::experimental::string_view full_ = {nullptr, 0};

   inline abbreviated_and_full(const char *a, const char *f) noexcept :
      abbreviated_{a},
      full_{f}
   {
   }
};

}
}
}

#endif
