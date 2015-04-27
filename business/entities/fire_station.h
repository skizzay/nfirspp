// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__

#include "business/values/address.h"

namespace firepp {
namespace business {

class fire_station : public cddd::cqrs::artifact {
public:
   typedef boost::uuids::uuid id_type;

   fire_station(const id_type &id);

   const id_type & id() const {
      return fire_department_id;
   }

   void acquire_building(const address &building_address);
   void relocate_to(const address &new_address);

private:
   id_type fire_station_id;
   address station_address;
};

}
}

#endif
