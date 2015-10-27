// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace infrastructure {

class fire_department_service {
public:
   using id_type = boost::uuids::uuid;

   virtual ~fire_department_service() noexcept = default;

   virtual id_type get_fire_department_id_for_firefighter(const id_type &) const = 0;
};

}
}
