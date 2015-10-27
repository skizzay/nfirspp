// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/incident_time_keeper.h"
#include "business/events/dispatched_to_incident.h"
#include "business/events/firefighter_arrived_on_scene.h"
#include "infrastructure/fire_department_service.h"
#include <boost/uuid/nil_generator.hpp>
#include <algorithm>

namespace firepp {
namespace business {

incident_time_keeper::incident_time_keeper(cddd::cqrs::artifact &a,
                                           infrastructure::fire_department_service &fds) :
   cddd::cqrs::artifact_view{a},
   responses{},
   fire_department_service{fds},
   controlled_time{}
{
   add_handler([this](const dispatched_to_incident &e) {
         on_dispatched_to_incident(e);
      });
   add_handler([this](const firefighter_arrived_on_scene &e) {
         on_firefighter_arrived_on_scene(e);
      });
}


void incident_time_keeper::on_dispatched_to_incident(const dispatched_to_incident &e) {
   fd_response &response = responses.get_response(e.fire_department_id());
   response.alarm_time = e.alarm_time();
}


void incident_time_keeper::on_firefighter_arrived_on_scene(const firefighter_arrived_on_scene &e) {
   id_type fire_department_id = fire_department_service.get_fire_department_id_for_firefighter(e.firefighter_id());
   fd_response &response = responses.get_response(fire_department_id);
   if ((e.arrival_time() < response.arrival_time) || (response.arrival_time.is_not_a_date_time())) {
      response.arrival_time = e.arrival_time();
   }
}

}
}
