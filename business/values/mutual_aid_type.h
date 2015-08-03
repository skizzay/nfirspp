// vim: sw=3 ts=3 expandtab cindent smartindent autoindent
#pragma once

#include "business/bits/value_component.h"

namespace firepp {
namespace business {

namespace details_ {

struct mutual_aid_tag final : length_validation_and_assignment {
   static constexpr auto type_name() noexcept {
      return "last name";
   }
};

}

class mutual_aid_type final : public details_::value_component<details_::mutual_aid_tag, 15> {
public:
   using details_::value_component<details_::mutual_aid_tag, 15>::value_component;

   constexpr static mutual_aid_type received{"Mutual aid received"};
   constexpr static mutual_aid_type automatically_received{"Mutual aid automatically received"};
   constexpr static mutual_aid_type given{"Mutual aid given"};
   constexpr static mutual_aid_type automatically_given{"Mutual aid automatically given"};
   constexpr static mutual_aid_type other{"Other aid given"};
};

}
}
