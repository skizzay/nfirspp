// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/events/event_base.h"

namespace firepp {
namespace business {

class incident_sized_up final : public event_base {
public:
   using id_type = boost::uuids::uuid;

   inline incident_sized_up(const id_type &user_id,
                            const timestamp_type &ts_,
                            const id_type &incident_id,
                            const id_type &location_id,
                            uint16_t incident_type_code) :
      event_base{user_id, ts_},
      incident_id_(incident_id),
      location_id_(location_id),
      incident_type_code_(incident_type_code)
   {
   }

   inline const id_type &incident_id() const {
      return incident_id_;
   }

   inline const id_type &location_id() const {
      return location_id_;
   }

   inline uint16_t incident_type_code() const {
      return incident_type_code_;
   }

private:
   id_type incident_id_;
   id_type location_id_;
   uint16_t incident_type_code_;
};

}
}
