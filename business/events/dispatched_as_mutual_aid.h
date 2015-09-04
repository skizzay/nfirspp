// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/event_base.h"
#include "business/values/mutual_aid_type.h"

namespace firepp {
namespace business {

class dispatched_as_mutual_aid final : public event_base {
public:
   using id_type = boost::uuids::uuid;

   dispatched_as_mutual_aid(const id_type &user_id,
                            const timestamp_type &ts_,
                            const id_type &incident_id,
                            const id_type &fire_department_id,
                            const timestamp_type &alarm_time,
                            size_t incident_number,
                            const mutual_aid_type &mutual_aid) :
      event_base{user_id, ts_},
      incident_id_(incident_id),
      fire_department_id_(fire_department_id),
      alarm_time_(alarm_time),
      incident_number_(incident_number),
      mutual_aid_(mutual_aid)
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

   const mutual_aid_type &mutual_aid() const {
      return mutual_aid_;
   }

private:
   id_type incident_id_;
   id_type fire_department_id_;
   timestamp_type alarm_time_;
   size_t incident_number_;
   mutual_aid_type mutual_aid_;
};

}
}
