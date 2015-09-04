// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/event_base.h"

namespace firepp {
namespace business {

class dispatched_as_primary_response final : public event_base {
public:
   using id_type = boost::uuids::uuid;

   dispatched_as_primary_response(const id_type &user_id,
                                  const timestamp_type &ts_,
                                  const id_type &incident_id,
                                  const id_type &fire_department_id,
                                  const timestamp_type &alarm_time,
                                  size_t incident_number,
                                  const id_type &location_id,
                                  uint8_t incident_type_code) :
      event_base{user_id, ts_},
      incident_id_(incident_id),
      fire_department_id_(fire_department_id),
      alarm_time_(alarm_time),
      incident_number_(incident_number),
      location_id_(location_id),
      incident_type_code_(incident_type_code)
   {
   }

   const id_type &incident_id() const {
      return incident_id_;
   }

   const id_type &fire_department_id() const {
      return fire_department_id_;
   }

   const timestamp_type &alarm_time() const {
      return alarm_time_;
   }

   size_t incident_number() const {
      return incident_number_;
   }

   const id_type &location_id() const {
      return location_id_;
   }

   uint8_t incident_type_code() const {
      return incident_type_code_;
   }

private:
   id_type incident_id_;
   id_type fire_department_id_;
   timestamp_type alarm_time_;
   size_t incident_number_;
   id_type location_id_;
   uint8_t incident_type_code_;
};

}
}
