// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_ENROLL_FIREFIGHTER_INTO_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_ENROLL_FIREFIGHTER_INTO_FIRE_DEPARTMENT_H__

#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace business {

class enroll_firefighter_into_fire_department {
public:
   typedef boost::uuids::uuid id_type;

   enroll_firefighter_into_fire_department(const id_type &firefighter_id, const id_type &fire_department_id) :
      firefighter_id_(firefighter_id),
      fire_department_id_(fire_department_id)
   {
   }
                                        
   enroll_firefighter_into_fire_department() = delete;
   enroll_firefighter_into_fire_department(const enroll_firefighter_into_fire_department &) = default;
   enroll_firefighter_into_fire_department(enroll_firefighter_into_fire_department &&) = default;
   enroll_firefighter_into_fire_department & operator =(const enroll_firefighter_into_fire_department &) = default;
   enroll_firefighter_into_fire_department & operator =(enroll_firefighter_into_fire_department &&) = default;

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
