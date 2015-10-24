// vim: sw=3 ts=3 expandtab cindent smartindent autoindent
#pragma once

#include "business/bits/value_component.h"

namespace firepp {
namespace business {

namespace details_ {

struct mutual_aid_tag final : length_validation_and_assignment {
   constexpr static auto type_name() noexcept {
      return "mutual aid";
   }
};

}

class mutual_aid_type final : public details_::value_component<details_::mutual_aid_tag, 15> {
public:
   using details_::value_component<details_::mutual_aid_tag, 15>::value_component;

   static const mutual_aid_type primary;
   static const mutual_aid_type automatic;
   static const mutual_aid_type requested;
   static const mutual_aid_type other;
};

}
}
