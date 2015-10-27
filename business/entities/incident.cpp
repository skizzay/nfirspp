// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/incident.h"
#include "business/events/dispatched_to_incident.h"
#include "business/events/incident_sized_up.h"
#include "infrastructure/fire_department_service.h"
#include "infrastructure/incident_number_provider.h"
#include "utils/validation.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace firepp {
namespace business {

using std::begin;
using std::end;
using std::find_if_not;
using std::find_if;
using std::for_each;
using std::tie;


incident::incident(infrastructure::session &session_,
                   infrastructure::incident_number_provider &inp,
                   infrastructure::fire_department_service &fds,
                   const id_type &id_) :
   cddd::cqrs::artifact{id_},
   session{session_},
   incident_number_provider_{inp},
   time_keeper_{*this, fds},
   dispatcher_{*this},
   location_id(boost::uuids::nil_uuid()),
   incident_type_code(std::numeric_limits<uint16_t>::max())
{
   add_handler([this](const incident_sized_up &e) {
         on_sizeup(e);
      });
}


void incident::establish_initial_sizeup(const id_type &location_id,
                                        uint16_t incident_type_code,
                                        const optional<id_type> &reporter) {
   (void)reporter; // Use this when we start tracking people.
   incident_sized_up sizeup{session.user_id(),
                            session.time(),
                            id(),
                            location_id,
                            incident_type_code};
   apply_change(sizeup);
}


void incident::update_sizeup(const id_type &location_id,
                             uint8_t incident_type_code) {
#if 0
   // Need to figure out how to perform validation
   if (!has_been_sized_up()) {
   }
#endif
   incident_sized_up sizeup{session.user_id(),
                            session.time(),
                            id(),
                            location_id,
                            incident_type_code};
   apply_change(sizeup);
}


void incident::dispatch_for_response(const id_type &fire_department_id,
                                     const timestamp_type &alarm_time,
                                     const mutual_aid_type &type) {
   size_t incident_number = incident_number_provider_.get_incident_number_for(id(),
                                                                              fire_department_id,
                                                                              alarm_time);
   dispatched_to_incident change(session.user_id(),
                                 session.time(),
                                 id(),
                                 fire_department_id,
                                 alarm_time,
                                 incident_number,
                                 type);
   apply_change(change);
}


void incident::dispatch_multiple_units(const timestamp_type &alarm_time,
                                       std::vector<std::tuple<id_type, mutual_aid_type>> responding_department_ids) {
   if (responding_department_ids.empty()) {
      std::ostringstream error;
      error << "Dispatching multiple units to incident '" << id() << "', but no units have been sepcified.";
      throw std::runtime_error{error.str()};
   }
   id_type fire_department_id;
   mutual_aid_type type_of_mutual_aid;

   for_each(begin(responding_department_ids), end(responding_department_ids),
      [&](const auto &response) {
         tie(fire_department_id, type_of_mutual_aid) = response;
         this->dispatch_for_response(fire_department_id, alarm_time, type_of_mutual_aid);
      });
}


void incident::on_sizeup(const incident_sized_up &e) {
   location_id = e.location_id();
   incident_type_code = e.incident_type_code();
}


#if 0
bool incident::has_different_alarm_time(const timestamp_type &alarm_time) const noexcept {

   auto e = end(fire_department_responses);
   return find_if_not(begin(fire_department_responses), e, [alarm_time](const fd_response &response) {
         return response.alarm_time == alarm_time;
      }) == e;
}
#endif

}
}
