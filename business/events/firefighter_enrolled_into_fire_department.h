// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIREFIGHTER_ENROLLED_INTO_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIREFIGHTER_ENROLLED_INTO_FIRE_DEPARTMENT_H__

#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace business {

class firefighter_enrolled_into_fire_department {
public:
   typedef boost::uuids::uuid id_type;

   firefighter_enrolled_into_fire_department(const id_type &firefighter_id, const id_type &fire_department_id) :
      firefighter_id_(firefighter_id),
      fire_department_id_(fire_department_id)
   {
   }
                                        
   firefighter_enrolled_into_fire_department() = delete;
   firefighter_enrolled_into_fire_department(const firefighter_enrolled_into_fire_department &) = default;
   firefighter_enrolled_into_fire_department(firefighter_enrolled_into_fire_department &&) = default;
   firefighter_enrolled_into_fire_department & operator =(const firefighter_enrolled_into_fire_department &) = default;
   firefighter_enrolled_into_fire_department & operator =(firefighter_enrolled_into_fire_department &&) = default;

   const id_type & firefighter_id() const {
      return firefighter_id_;
   }

   const id_type & fire_department_id() const {
      return fire_department_id_;
   }

private:
   id_type firefighter_id_;
   id_type fire_department_id_;
};

}
}

#endif
