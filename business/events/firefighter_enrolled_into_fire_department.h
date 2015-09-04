// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIREFIGHTER_ENROLLED_INTO_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIREFIGHTER_ENROLLED_INTO_FIRE_DEPARTMENT_H__

#include "business/events/event_base.h"

namespace firepp {
namespace business {

class firefighter_enrolled_into_fire_department final : public event_base {
public:
   typedef boost::uuids::uuid id_type;

   inline firefighter_enrolled_into_fire_department(const id_type &user_id, const timestamp_type &ts_,
                                                    const id_type &firefighter_id, const id_type &fire_department_id,
                                                    const boost::gregorian::date &ed_) :
      event_base{user_id, ts_},
      firefighter_id_(firefighter_id),
      fire_department_id_(fire_department_id),
      effective_date_{ed_}
   {
   }
                                        
   firefighter_enrolled_into_fire_department() = delete;
   inline firefighter_enrolled_into_fire_department(const firefighter_enrolled_into_fire_department &) = default;
   inline firefighter_enrolled_into_fire_department(firefighter_enrolled_into_fire_department &&) = default;
   inline firefighter_enrolled_into_fire_department & operator =(const firefighter_enrolled_into_fire_department &) = default;
   inline firefighter_enrolled_into_fire_department & operator =(firefighter_enrolled_into_fire_department &&) = default;

   inline const id_type & firefighter_id() const {
      return firefighter_id_;
   }

   inline const id_type & fire_department_id() const {
      return fire_department_id_;
   }

   inline const boost::gregorian::date & effective_date() const {
      return effective_date_;
   }

private:
   id_type firefighter_id_;
   id_type fire_department_id_;
   boost::gregorian::date effective_date_;
};

}
}

#endif
