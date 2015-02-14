// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_NAME_H__
#define NFIRSPP_BUSINESS_NAME_H__

#include "business/bits/value_component.h"

namespace nfirspp {
namespace business {

namespace details_ {

template<class Tag, std::size_t N>
struct name_ final : value_component<Tag, N> {
   constexpr inline char initial() const noexcept {
      auto s = to_string();
      return s.empty() ? '\0' : s[0];
   }
};


struct first_name_tag final : length_validation_and_assignment<first_name_tag> {
   static inline const char * type_name() noexcept {
      return "first name";
   }
};


struct middle_name_tag final : length_validation_and_assignment<middle_name_tag> {
   static inline const char * type_name() noexcept {
      return "middle name";
   }
};


struct last_name_tag final : length_validation_and_assignment<last_name_tag> {
   static inline const char * type_name() noexcept {
      return "last name";
   }
};

}


using first_name = details_::name_<details_::first_name_tag, 15>;
using middle_name = details_::name_<details_::middle_name_tag, 15>;
using last_name = details_::name_<details_::last_name_tag, 25>;


class full_name final {
public:
   inline full_name(const first_name &f, const middle_name &m, const last_name &l) :
      first_{f},
      middle_{m},
      last_{l}
   {
      if (!valid()) {
         std::ostringstream error;
         error << '\'' << f.to_string() << "' '" << m.to_string() << "' '" << l.to_string() << "' is an invalid full name.";
         throw std::invalid_argument{error.str()};
      }
   }

   inline full_name(const last_name &l, const first_name &f, const middle_name &m={}) :
      full_name{f, m, l}
   {
   }

   inline full_name(const first_name &f, const last_name &l) :
      full_name{f, {}, l}
   {
   }

   full_name() = default;
   full_name(const full_name &) noexcept = default;
   full_name(full_name &&) noexcept = default;
   ~full_name() noexcept = default;

   full_name & operator =(const full_name &) noexcept = default;
   full_name & operator =(full_name &&) noexcept = default;

   inline bool valid() const noexcept {
      return first().valid() && last().valid();
   }

   inline const first_name & first() const noexcept {
      return first_;
   }

   inline const middle_name & middle() const noexcept {
      return middle_;
   }

   inline const last_name & last() const noexcept {
      return last_;
   }

   inline std::string initials(const std::string::allocator_type &alloc={}) const {
      std::string result{alloc};
      result.reserve(4);
      add_to_initials(first(), result);
      add_to_initials(middle(), result);
      add_to_initials(last(), result);
      return result;
   }

private:
   // We declare noexcept because the allocation has reserved.
   template<class Name>
   static inline void add_to_initials(const Name &name, std::string &s) noexcept {
      if (name.valid()) {
         s.push_back(name.initial());
      }
   }

   first_name first_;
   middle_name middle_;
   last_name last_;
};

}
}

#endif
