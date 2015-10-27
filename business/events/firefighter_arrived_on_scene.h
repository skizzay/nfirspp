// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/event_base.h"
#include "business/values/mutual_aid_type.h"

namespace firepp {
namespace business {

class firefighter_arrived_on_scene final : public event_base {
public:
   using id_type = boost::uuids::uuid;

   inline firefighter_arrived_on_scene(const id_type &user_id,
                                       const timestamp_type &ts_,
                                       const id_type &incident_id,
                                       const id_type &firefighter_id,
                                       const timestamp_type &arrival_time) :
      event_base{user_id, ts_},
      incident_id_(incident_id),
      firefighter_id_(firefighter_id),
      arrival_time_(arrival_time)
   {
   }

   inline const id_type &incident_id() const {
      return incident_id_;
   }

   inline const id_type &firefighter_id() const {
      return firefighter_id_;
   }

   inline const timestamp_type &arrival_time() const {
      return arrival_time_;
   }

private:
   id_type incident_id_;
   id_type firefighter_id_;
   timestamp_type arrival_time_;
};

}
}
