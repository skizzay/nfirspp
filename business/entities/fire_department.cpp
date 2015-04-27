// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include "business/events/fire_department_acquired_station.h"
#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "cqrs/exceptions.h"

namespace firepp {
namespace business {

using cddd::cqrs::artifact;
using cddd::cqrs::basic_domain_event;
using cddd::cqrs::null_id_exception;

fire_department::fire_department(const id_type &id_) :
   artifact{},
   fire_department_id(id_)
{
   add_handler([](const basic_domain_event<firefighter_enrolled_into_fire_department> &){});
}


void fire_department::enroll_firefighter(const id_type &firefighter_id) {
   if (firefighter_id.is_nil()) {
      throw null_id_exception{"firefighter id"};
   }
   apply_change(firefighter_enrolled_into_fire_department{firefighter_id, id()});
}


void fire_department::acquire_station(const id_type &station_id) {
   if (station_id.is_nil()) {
      throw null_id_exception{"fire station id"};
   }
   apply_change(fire_department_acquired_station{id(), station_id});
}

}
}
