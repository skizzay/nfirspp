// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/values/fdid.h"
#include "business/values/location.h"
#include "business/values/mutual_aid_type.h"
#include "infrastructure/optional.h"
#include "infrastructure/session.h"
#include "cqrs/artifact.h"
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace firepp {
namespace business {

class dispatched_as_primary_response;
class dispatched_as_mutual_aid;
#if 0
class incident_under_control;
class incident_terminated;
class firefighter_responded_in_apparatus;
class firefighter_responded_in_pov;
class apparatus_responded;
class apparatus_arrived_on_location;
class firefighter_arrived_on_location_in_pov;
class incident_command_established;
#endif

class incident final : public cddd::cqrs::artifact {
public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::gregorian::date;

   incident(infrastructure::session &session,
            const id_type &id);

   void dispatch_as_primary_response(const id_type &fire_department_id,
                                     const timestamp_type &alarm_time,
                                     size_t incident_number,
                                     const id_type &location_id,
                                     uint8_t incident_type_code);
   void dispatch_as_mutual_aid(const id_type &fire_department_id,
                               const timestamp_type &alarm_time,
                               size_t incident_number,
                               const mutual_aid_type &type);
#if 0
   void mark_as_controlled(const timestamp_type &controlled_time);
   void clear_all(const timestamp_type &clear_time);
   void have_firefighter_respond_in_apparatus(const id_type &firefighter_id,
                                              const id_type &apparatus);
   void have_firefighter_respond_in_pov(const id_type &firefighter_id,
                                        const timestamp_type &dispatch_time);
   void have_firefighter_respond_to_station(const id_type &firefighte_idr,
                                            const id_type &station_id,
                                            const timestamp_type &dispatch_time);
   void show_apparatus_responding(const id_type &apparatus_id,
                                  const timestamp_type &dispatch_time);
   void show_apparatus_on_location(const id_type &apparatus_id,
                                   const id_type &location_id,
                                   const timestamp_type &arrival_time);
   void show_firefighter_in_pov_on_location(const id_type &firefighter_id,
                                            const timestamp_type &arrival_time);
   void establish_incident_commander(const id_type &firefighter_id,
                                     const timestamp_type &arrival_time);
   void establish_staging(const id_type &location_id,
                          const timestamp_type &time_established);
   void transfer_command(const id_type &new_incident_commander_id,
                         const timestamp_type &time_of_transfer);
   void involve_person(const id_type &person_id, bool owner);
   void involve_person_from_business(const id_type &person_id,
                                     const id_type &business_id, bool owner);
#endif

private:
   template<class T>
   using optional_ = infrastructure::details_::optional_value<T>;

   struct fd_response {
      id_type fire_department_id;
      std::size_t incident_number;
      timestamp_type alarm_time;
      timestamp_type arrival_time;
      timestamp_type cleared_time;
      optional_<mutual_aid_type> aid_type;
      id_type officer_in_charge;
      id_type member_making_report;
   };

   struct involement {
      id_type person_id;
      id_type business_id;
      bool owner;
   };

   infrastructure::session &session;
   std::vector<fd_response> fire_department_responses;
   timestamp_type date;
   optional_<timestamp_type> controlled_time;
   optional_<timestamp_type> last_unit_cleared_time;
   id_type location_id;
   uint8_t incident_type_code;
   std::vector<involement> involements;

   bool has_fire_department_been_dispatched(const id_type &fire_department_id) const;
   void on_dispatched_as_primary_response(const id_type &fire_department_id);
};

}
}
