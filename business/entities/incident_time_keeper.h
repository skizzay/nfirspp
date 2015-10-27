// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "cqrs/artifact_view.h"
#include "business/entities/bits/response_table.h"
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <vector>

namespace firepp {
namespace infrastructure {
class fire_department_service;
}

namespace business {

class dispatched_to_incident;
class firefighter_arrived_on_scene;

class incident_time_keeper final : public cddd::cqrs::artifact_view {
public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::posix_time::ptime;

   incident_time_keeper(cddd::cqrs::artifact &artifact,
                        infrastructure::fire_department_service &fds);

   struct fd_response {
      id_type fire_department_id;
      timestamp_type alarm_time;
      timestamp_type arrival_time;
      timestamp_type last_unit_cleared_time;
   };

private:
   void on_dispatched_to_incident(const dispatched_to_incident &);
   void on_firefighter_arrived_on_scene(const firefighter_arrived_on_scene &);

   details_::response_table<fd_response, &fd_response::fire_department_id> responses;
   infrastructure::fire_department_service &fire_department_service;
   timestamp_type controlled_time;
};

}
}
