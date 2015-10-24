// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <cstdint>

namespace firepp {
namespace infrastructure {

class incident_number_provider {
public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::posix_time::ptime;

   virtual ~incident_number_provider() noexcept = default;
   virtual size_t get_incident_number_for(const id_type &incident_id,
                                          const id_type &fire_department_id,
                                          const timestamp_type &alarm_time) = 0;
};

}
}
