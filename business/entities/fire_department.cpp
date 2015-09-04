// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include "business/events/fire_department_acquired_station.h"
#include "business/events/firefighter_enrolled_into_fire_department.h"
#include "utils/validation.h"
#include <boost/uuid/uuid_io.hpp>

namespace firepp {
namespace business {

using cddd::cqrs::artifact;
using cddd::cqrs::basic_domain_event;
using boost::uuids::uuid;

namespace {

template<class T, class A>
inline bool has(const std::vector<T, A> &collection, const T &item) {
   using std::begin;
   using std::end;
   using std::find;

   auto e = end(collection);
   return e != find(begin(collection), e, item);
}

}

fire_department::fire_department(id_collection &firefighters_, id_collection &stations_,
                                 infrastructure::session &s, const id_type &id_) :
   artifact{id_},
   firefighters{firefighters_},
   stations{stations_},
   session_{s}
{
   add_handler([this](const firefighter_enrolled_into_fire_department &e){
         firefighters.push_back(e.firefighter_id());
      });
   add_handler([this](const fire_department_acquired_station &e){
         stations.push_back(e.fire_station_id());
      });
}


void fire_department::enroll_firefighter(const id_type &firefighter_id, const boost::gregorian::date &effective_date) {
   cddd::utils::validate_id(firefighter_id);
   if (has(firefighters, firefighter_id)) {
      std::ostringstream error;
      error << "Firefighter '" << firefighter_id << "' already enrolled in department '" << id() << "'.";
      throw cddd::utils::entity_exists{error.str()};
   }
   else if (effective_date.is_not_a_date()) {
      std::ostringstream error;
      error << "Effective date is not a date. Firefighter id is '" << firefighter_id << "'. Fire department id is '" << id() << "'.";
      throw std::invalid_argument{error.str()};
   }
   auto evt = firefighter_enrolled_into_fire_department(session_.user_id(), session_.time(), firefighter_id, id(), effective_date);
   apply_change(std::move(evt));
}


void fire_department::acquire_station(const id_type &station_id) {
   cddd::utils::validate_id(station_id);
   if (has(stations, station_id)) {
      std::ostringstream error;
      error << "Fire station '" << station_id << "' already acquired by department '" << id() << "'.";
      throw cddd::utils::entity_exists{error.str()};
   }
   apply_change(fire_department_acquired_station{session_.user_id(), session_.time(), id(), station_id});
}

}
}
