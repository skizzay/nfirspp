// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/values/address.h"
#include <cstdint>
#include <boost/variant.hpp>

namespace firepp {
namespace business {

enum class location_type : uint8_t {
   street_address = 1,
   intersection = 2,
   in_front_of = 3,
   rear_of = 4,
   adjacent_to = 5,
   directions = 6
   // TODO: U.S. National Grid
};


enum class address_type : uint8_t {
   street_address = 1,
   in_front_of = 3,
   rear_of = 4,
   adjacent_to = 5
};


class location final {
public:
   struct incident_address final {
      address_type type;
      address value;
   };

   struct intersection final {
      us_street street1;
      us_street street2;
   };

   struct directions final {
      std::string value;
   };

   template<class VisitorType>
   constexpr auto apply_visitor(VisitorType visitor) const {
      return boost::apply_visitor(visitor, value);
   }

   constexpr location_type type() const {
      return apply_visitor(location_type_extractor{});
   }

   static location from_address(address_type type, address value) {
      return location{incident_address{type, value}};
   }

   static location from_intersection(const us_street &street1, const us_street &street2) {
      return location{intersection{street1, street2}};
   }

   static location from_directions(std::string dirs) {
      return location{directions{std::move(dirs)}};
   }

private:
   template<class T>
   explicit constexpr location(T &&t) :
      value{std::move(t)}
   {
   }

   struct location_type_extractor final : boost::static_visitor<location_type> {
      location_type operator()(const incident_address &addr) const {
         return static_cast<location_type>(addr.type);
      }

      location_type operator()(const directions &) const {
         return location_type::directions;
      }

      location_type operator()(const intersection &) const {
         return location_type::intersection;
      }
   };

   boost::variant<incident_address, intersection, std::string> value;
};

}
}
