// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__

namespace firepp {
namespace business {

class firefighter_enrolled_into_fire_department {
public:
   firefighter_enrolled_into_fire_department(const cddd::cqrs::object_id &firefighter_id, const cddd::cqrs::object_id &fire_department_id) :
      firefighter_id_(firefighter_id),
      fire_department_id_(fire_department_id)
   {
   }
                                        
   firefighter_enrolled_into_fire_department() = delete;
   firefighter_enrolled_into_fire_department(const firefighter_enrolled_into_fire_department &) = default;
   firefighter_enrolled_into_fire_department(firefighter_enrolled_into_fire_department &&) = default;
   firefighter_enrolled_into_fire_department & operator =(const firefighter_enrolled_into_fire_department &) = default;
   firefighter_enrolled_into_fire_department & operator =(firefighter_enrolled_into_fire_department &&) = default;

   const cddd::cqrs::object_id firefighter_id() const {
      return firefighter_id_;
   }

   const cddd::cqrs::object_id fire_department_id() const {
      return fire_department_id_;
   }

private:
   cddd::cqrs::object_id firefighter_id_;
   cddd::cqrs::object_id fire_department_id_;
};

}
}

#endif
