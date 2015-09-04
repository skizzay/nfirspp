// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "infrastructure/optional.h"
#include <array>
#include <cstdint>

namespace firepp {
namespace business {

class incident_type final {
public:
   class incident_category final {
   public:
      constexpr uint8_t value() const {
         return 0;
      }
   };

   class incident_subcategory final {
   public:
      constexpr uint8_t value() const {
         return 0;
      }
   };

   constexpr uint8_t value() const {
      return category.value() + subcategory.value() + code;
   }

   static const incident_type & from_value(uint8_t value) {
      return *table.at(value);
   }

private:
   constexpr incident_type(incident_category &c, incident_subcategory &sc, uint8_t code_, const char *desc) :
      category{c},
      subcategory{sc},
      description{description_},
      code{code_}
   {
      table[value()] = *this;
   }

   incident_category &category;
   incident_subcategory &subcategory;
   const char *description_;
   uint8_t code;

   // 1009 is the smallest upper bound of value range which is prime
   static std::array<infrastructure::details_::optional_value<incident_type>, 1009> table = {};
};

}
}
