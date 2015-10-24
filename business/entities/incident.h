// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/entities/incident_dispatcher.h"
#include "business/values/fdid.h"
#include "business/values/location.h"
#include "business/values/mutual_aid_type.h"
#include "infrastructure/incident_number_provider.h"
#include "infrastructure/optional.h"
#include "infrastructure/session.h"
#include "cqrs/artifact.h"
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace firepp {
namespace business {

class incident_sized_up;
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
   template<class T>
   using optional = infrastructure::details_::optional_value<T>;

public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::posix_time::ptime;

   incident(infrastructure::session &session,
            infrastructure::incident_number_provider &inp,
            const id_type &id);

   void establish_initial_sizeup(const id_type &location_id,
                                 uint16_t incident_type_code,
                                 const optional<id_type> &reporter);
   void update_sizeup(const id_type &location_id,
                      uint8_t incident_type_code);

   void dispatch_for_response(const id_type &fire_department_id,
                              const timestamp_type &alarm_time,
                              const mutual_aid_type &type);
   void dispatch_multiple_units(const timestamp_type &alarm_time,
                                std::vector<std::tuple<id_type, mutual_aid_type>> responding_department_ids);
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
   infrastructure::session &session;
   infrastructure::incident_number_provider &incident_number_provider_;
   incident_dispatcher dispatcher_;
   id_type location_id;
   uint16_t incident_type_code;

   inline bool has_been_sized_up() const {
      return !location_id.is_nil();
   }
   void on_sizeup(const incident_sized_up &e);
};

}
}
