// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__
#define NFIRSPP_BUSINESS_FIRE_DEPARTMENT_H__

#include "business/values/address.h"
#include "business/values/fdid.h"
#include <boost/uuid>

namespace firepp {
namespace business {

class fire_department final {
public:
   inline const fdid & get_fdid() const noexcept {
      return fdid_;
   }

   inline us_state get_state() const noexcept {
      return get_address().state();
   }

   inline const address & get_address() const noexcept {
      return address_;
   }

   inline const & email_address get_email_address() const noexcept {
      return email_;
   }

   inline bool valid() const noexcept {
      return get_fdid().valid();
   }

private:
   fdid fdid_;
   address address_;
   email_address email_;
};

}
}

#endif
