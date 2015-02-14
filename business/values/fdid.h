// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FDID_H__
#define NFIRSPP_BUSINESS_FDID_H__

#include "business/bits/value_component.h"

namespace nfirspp {
namespace business {

namespace details_ {

struct fdid_tag final : regex_validation_and_assignment<fdid_tag, std::index_sequence<0>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex r{"^\\w{1,5}$"};
      return r;
   }

   static inline const char * type_name() noexcept {
      return "FDID";
   }
};

}


using fdid = details_::value_component<details_::fdid_tag, 5>;

}
}

#endif
