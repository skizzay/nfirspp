// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/uuid/uuid.hpp>
#include <cstring>

namespace firepp {
namespace business {

class event_base {
public:
   using user_id_type = boost::uuids::uuid;
   using timestamp_type = boost::posix_time::ptime;

   event_base(const user_id_type &id, const timestamp_type &ts) :
      id_(id),
      ts_{ts}
   {
   }

   inline const user_id_type & user_id() const {
      return id_;
   }

   inline const timestamp_type & timestamp() const {
      return ts_;
   }

private:
   user_id_type id_;
   timestamp_type ts_;
};

}
}
