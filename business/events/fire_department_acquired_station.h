// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_ACQUIRED_STATION_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_ACQUIRED_STATION_H__

#include "business/values/address.h"
#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace business {

class fire_department_acquired_station {
public:
   typedef boost::uuids::uuid id_type;

   fire_department_acquired_station(const id_type &fire_department_id, const id_type &fire_station_id) :
      fire_department_id_(fire_department_id),
      fire_station_id_(fire_station_id)
   {
   }
                                        
   fire_department_acquired_station() = delete;
   fire_department_acquired_station(const fire_department_acquired_station &) = default;
   fire_department_acquired_station(fire_department_acquired_station &&) = default;
   fire_department_acquired_station & operator =(const fire_department_acquired_station &) = default;
   fire_department_acquired_station & operator =(fire_department_acquired_station &&) = default;

   const id_type & fire_department_id() const {
      return fire_department_id_;
   }

   const id_type & fire_station_id() const {
      return fire_station_id_;
   }

private:
   id_type fire_department_id_;
   id_type fire_station_id_;
};

}
}

#endif
