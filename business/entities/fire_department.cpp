// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include "business/events/fire_department_acquired_station.h"
#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "cqrs/utils/validation.h"
#include <boost/uuid/uuid_io.hpp>

namespace firepp {
namespace business {

using cddd::cqrs::artifact;
using cddd::cqrs::basic_domain_event;
using boost::uuids::uuid;

fire_department::fire_department(std::unique_ptr<id_collection> firefighters_, std::unique_ptr<id_collection> stations_,
                                 std::shared_ptr<infrastructure::session> session_,
                                 std::shared_ptr<cddd::messaging::dispatcher<>> dispatcher_, const id_type &id_) :
   artifact{std::move(dispatcher_), id_},
   firefighters{std::move(firefighters_)},
   stations{std::move(stations_)},
   session{session_}
{
   add_handler([](const firefighter_enrolled_into_fire_department &e){
         firefighters->put(e.firefighter_id());
      });
   add_handler([](const fire_department_acquired_station &e){
         stations->put(e.fire_station_id());
      });
}


void fire_department::enroll_firefighter(const id_type &firefighter_id) {
   cddd::utils::validate_id(firefighter_id);
   if (firefighters->has(firefighter_id)) {
      std::ostringstream error;
      error << "Firefighter '" << firefighter_id << "' already enrolled in department '" << id() << "'.";
      throw cddd::cqrs::utils::entity_exists{error.str()};
   }
   apply_change(firefighter_enrolled_into_fire_department{user_id, ts, firefighter_id, id()});
}


void fire_department::acquire_station(const id_type &station_id) {
   cddd::utils::validate_id(station_id);
   if (stations->has(station_id)) {
      std::ostringstream error;
      error << "Fire station '" << station_id << "' already acquired by department '" << id() << "'.";
      throw cddd::cqrs::utils::entity_exists{error.str()};
   }
   apply_change(fire_department_acquired_station{user_id, ts, id(), station_id});
}

}
}
