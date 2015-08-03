// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "business/values/fdid.h"
#include "business/values/location.h"
#include "business/values/mutual_aid_type.h"
#include "infrastructure/optional.h"
#include "infrastructure/session.h"
#include "cqrs/artifact.h"
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace firepp {
namespace business {

class incident : public cddd::cqrs::artifact {
public:
   using id_type = boost::uuids::uuid;
   using timestamp_type = boost::gregorian::date;

   incident(infrastructure::session &session,
            cddd::messaging::dispatcher<> dispatcher,
            const id_type &id);

   void dispatch_as_primary_response(const id_type &fire_department_id,
                                     const timestamp_type &alarm_time,
                                     const location &where);
   void dispatch_as_mutual_aid(const id_type &fire_department_id,
                               const timestamp_type &alarm_time,
                               const mutual_aid_type &type);

private:
   struct fd_response {
      id_type fire_department_id;
      fdid fd_id;
      std::size_t incident_number;
      timestamp_type alarm_time;
      timestamp_type arrival_time;
      mutual_aid_type aid_type;
   };

   timestamp_type date;
   infrastructure::details_::optional_value<timestamp_type> controlled_time;
   infrastructure::details_::optional_value<timestamp_type> last_unit_cleared_time;
   location where;
};

}
}
