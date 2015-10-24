// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace infrastructure {

class session {
public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::posix_time::ptime;

   virtual ~session() = default;

   virtual const id_type & id() const = 0;
   virtual const id_type & user_id() const = 0;
   virtual const timestamp_type & time() const = 0;
};

}
}
