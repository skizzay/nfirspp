// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/incident_dispatcher.h"
#include "business/events/dispatched_to_incident.h"
#include <boost/uuid/nil_generator.hpp>
#include <algorithm>

namespace firepp {
namespace business {

incident_dispatcher::incident_dispatcher(cddd::cqrs::artifact &a) :
   cddd::cqrs::artifact_view{a},
   responses{}
{
   add_handler([this](const dispatched_to_incident &e) {
         on_dispatched_to_incident(e);
      });
}


void incident_dispatcher::on_dispatched_to_incident(const dispatched_to_incident &e) {
   fd_response &response = responses.get_response(e.fire_department_id());
   response.incident_number = e.incident_number();
   response.aid_type = e.mutual_aid();
}

}
}
