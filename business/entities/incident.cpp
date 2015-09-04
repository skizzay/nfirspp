// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/entities/incident.h"
#include "business/events/dispatched_as_primary_response.h"
#include "utils/validation.h"
#include <boost/uuid/uuid_io.hpp>

namespace firepp {
namespace business {

incident::incident(infrastructure::session &session_,
                   const id_type &id_) :
   cddd::cqrs::artifact{id_},
   session{session_}
{
   add_handler([this](const dispatched_as_primary_response &e) {
         on_dispatched_as_primary_response(e);
      });
}


void incident::dispatch_as_primary_response(const id_type &fire_department_id,
                                            const timestamp_type &alarm_time,
                                            size_t incident_number,
                                            const id_type &location_id,
                                            uint8_t incident_type_code) {
   if (!fire_department_responses.empty()) {
      std::ostringstream error;
      error << "Fire department '" << fire_department_id << "' cannot be dispatched as primary response to incident '" << id() << "'.";
      throw cddd::cqrs::utils::entity_exists{error.str()};
   }

   dispatched_as_primary_response change{session.user_id(),
                                         session.time(),
                                         id(),
                                         fire_department_id,
                                         alarm_time,
                                         incident_number,
                                         location_id,
                                         incident_type_code};
   apply_change(change);
}


void incident::dispatch_as_mutual_aid(const id_type &fire_department_id,
                                      const timestamp_type &alarm_time,
                                      size_t incident_number,
                                      const mutual_aid_type &type) {
   if (has_fire_department_been_dispatched(fire_department_id)) {
      std::ostringstream error;
      error << "Fire department '" << fire_department_id << "' already dispatched to incident '" << id() << "'.";
      throw cddd::cqrs::utils::entity_exists{error.str()};
   }

   dispatched_as_mutual_aid change{session.user_id(),
                                   session.time(),
                                   id(),
                                   fire_department_id,
                                   alarm_time,
                                   incident_number,
                                   type};
   apply_change(change);
}


bool incident::has_fire_department_been_dispatched(const id_type &fire_department_id) const {
   auto end = std::end(fire_department_responses);
   return std::find_if(std::begin(fire_department_responses), end, [&fd_id=fire_department_id] (const auto &response) {
         return fd_id == response.fire_department_id;
      }) != end;
}


void incident::on_dispatched_as_primary_response(const dispatched_as_primary_response &e) {
   fd_response response;
   response.fire_department_id = e.fire_department_id();
   response.incident_number = e.incident_number();
   response.alarm_time = e.alarm_time();
   fire_department_responses.push_back(response);

   date = e.alarm_time();
   location_id = e.location_id();
   incident_type_code = e.incident_type_code();
}

}
}
