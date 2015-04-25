// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__

#include "business/values/address.h"
#include "business/values/fdid.h"
#include <boost/uuid/uuid.hpp>
#include <deque>
#include <memory>

namespace firepp {
namespace business {

template<class IdContainer=std::deque<boost::uuid>, class DomainEventDispatcher=cddd::messaging::dispatcher<>, class DomainEventContainer=std::deque<cddd::cqrs::domain_event_ptr>>
class fire_department final : public cddd::cqrs::basic_artifact<DomainEventDispatcher, DomainEventContainer> {
public:
   using id_container_type = IdContainer;
   using cddd::cqrs::basic_artifact<DomainEventDispatcher, DomainEventContainer>::size_type;

   fire_department(size_type revision=0,
                   std::shared_ptr<DomainEventDispatcher> dispatcher=std::make_shared<DomainEventDispatcher>()) :
      cddd::cqrs::basic_artifactor<DomainEventDispatcher, DomainEventContainer>{revision, dispatcher},
      fire_department_id{},
      address{},
      email{},
      station_ids{},
      firefighter_ids{}
   {
   }

   void enroll_firefighter(const cddd::cqrs::object_id &id) {
      if (id.is_null()) {
         throw cddd::cqrs::null_id_exception{"fire firefighter id"};
      }
      else {
         this->apply_change(firefighter_enrolled_into_fire_department{, id});
      }
   }

private:
   fdid fdid;
   address address;
   email_address email;
   id_container_type station_ids;
   id_container_type firefighter_ids;
};

}
}


namespace std {

template<class IdContainer, class Alloc>
class uses_allocator<firepp::business::fire_department<IdContainer>, Alloc> : public uses_allocator<IdContainer, Alloc> {};

}

#endif
