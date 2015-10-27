// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include "cqrs/artifact_view.h"
#include "business/entities/bits/response_table.h"
#include "business/values/mutual_aid_type.h"
#include "infrastructure/optional.h"
#include "infrastructure/session.h"
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace firepp {
namespace business {

class dispatched_to_incident;


class incident_dispatcher final : public cddd::cqrs::artifact_view {
   template<class T>
   using optional = infrastructure::details_::optional_value<T>;

public:
   using id_type = boost::uuids::uuid;

   struct fd_response {
      id_type fire_department_id;
      std::size_t incident_number;
      mutual_aid_type aid_type;
   };

   incident_dispatcher(cddd::cqrs::artifact &a);

private:
   void on_dispatched_to_incident(const dispatched_to_incident &);

   details_::response_table<fd_response, &fd_response::fire_department_id> responses;
};

}
}
