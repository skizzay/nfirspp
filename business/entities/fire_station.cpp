// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_station.h"

namespace firepp {
namespace business {

fire_station::fire_station(const id_type &id_) :
   cddd::cqrs::artifact{0},
   fire_station_id{id_},
   station_address{}
{
}


void fire_station::acquire_building(const address &building_address) {
   station_address = building_address;
}


void fire_station::relocate_to(const address &new_address) {
   station_address = new_address;
}

}
}
