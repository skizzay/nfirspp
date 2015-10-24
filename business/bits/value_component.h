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

   constexpr value_component() noexcept :
      value()
   {
      value[0] = '\0';
   }

   template<class... Args>
   explicit constexpr value_component(std::experimental::string_view v, Args && ... args) :
      value()
   {
      using std::forward;
      if (!Tag::validate_and_assign(value, v, forward<Args>(args)...)) {
         throw std::invalid_argument{"Invalid value"};
      }
      n = static_cast<uint8_t>(v.size());
   }

   constexpr inline bool valid() const noexcept {
      return value[0] != '\0';
   }

   constexpr inline std::experimental::string_view to_string() const noexcept {
      return valid() ? std::experimental::string_view{value, n} : std::experimental::string_view{nullptr, 0};
   }

   constexpr inline bool operator==(const value_component &rhs) const noexcept {
      using std::equal;
      return equal(&value[0], &value[n], &rhs.value[0]);
   }

   constexpr inline bool operator!=(const value_component &rhs) const noexcept {
      return !(*this == rhs);
   }

private:
   char value[N+1];
   uint8_t n;
};


struct length_validation_and_assignment {
   template<std::size_t N>
   constexpr static inline bool validate_and_assign(char (&value)[N], std::experimental::string_view v) {
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
constexpr inline void copy_to_value(const Matches &, char *value, std::index_sequence<>) noexcept {
   *value = '\0';
}


template<class Matches, std::size_t I, std::size_t... Indices>
constexpr inline void copy_to_value(const Matches &matches, char *value, std::index_sequence<I, Indices...>) noexcept {
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
   constexpr static inline bool validate_and_assign(char *value, std::experimental::string_view v, const Alloc &alloc={}) {
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
   constexpr static inline const char *type_name() noexcept {
      return CRTP::type_name();
   }
};


template<class CRTP, std::size_t AbbreviatedSize>
class abbreviated_and_full {
   friend CRTP;

public:
   constexpr abbreviated_and_full() = default;
   constexpr abbreviated_and_full(const abbreviated_and_full &) noexcept = default;
   constexpr abbreviated_and_full(abbreviated_and_full &&) noexcept = default;
   ~abbreviated_and_full() noexcept = default;

   constexpr abbreviated_and_full & operator =(const abbreviated_and_full &) noexcept = default;
   constexpr abbreviated_and_full & operator =(abbreviated_and_full &&) noexcept = default;

   constexpr inline std::experimental::string_view abbreviated() const noexcept {
      return abbreviated_.to_string();
   }

   constexpr inline std::experimental::string_view full() const noexcept {
      return full_;
   }

   constexpr inline bool valid() const noexcept {
      return !(abbreviated().empty() || full().empty());
   }

private:
   value_component<crtp_adaptor_tag<CRTP>, AbbreviatedSize> abbreviated_ = {};
   std::experimental::string_view full_ = {nullptr, 0};

   constexpr inline abbreviated_and_full(const char *a, const char *f) noexcept :
      abbreviated_{a},
      full_{f}
   {
   }
};

}
}
}

#endif
