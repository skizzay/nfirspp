// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/uuid/uuid.hpp>

namespace firepp {
namespace infrastructure {

class session {
public:
   virtual ~session() = default;

   virtual const boost::uuids::uuid & id() const = 0;
   virtual const boost::uuids::uuid & user_id() const = 0;
   virtual const boost::posix_time::ptime & time() const = 0;
};

}
}
