// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__

#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "business/values/address.h"
#include "business/values/fdid.h"
#include "cqrs/artifact.h"
#include <memory>
#include <vector>

namespace firepp {
namespace business {

class fire_station;

class fire_department final : public cddd::cqrs::artifact {
public:
   typedef boost::uuids::uuid id_type;
   typedef std::vector<id_type> id_container_type;
   using cddd::cqrs::artifact::size_type;

   fire_department(const id_type &id);

   const id_type & id() const {
      return fire_department_id;
   }

   void enroll_firefighter(const id_type &id);
   void acquire_station(const id_type &station_id);

private:
   id_type fire_department_id;
};

}
}

#endif
