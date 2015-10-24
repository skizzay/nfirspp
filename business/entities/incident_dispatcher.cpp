// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/incident_dispatcher.h"
#include "business/events/dispatched_to_incident.h"
#include <boost/uuid/nil_generator.hpp>
#include <algorithm>

namespace firepp {
namespace business {

using std::count_if;
using std::find_if;
using std::begin;
using std::end;


auto is_primary_response = [](const incident_dispatcher::fd_response &response) -> bool {
   return response.aid_type == mutual_aid_type::primary;
};


incident_dispatcher::incident_dispatcher(cddd::cqrs::artifact &a) :
   cddd::cqrs::artifact_view{a},
   fire_department_responses{}
{
   add_handler([this](const dispatched_to_incident &e) {
         on_dispatched_to_incident(e);
      });
}


void incident_dispatcher::on_dispatched_to_incident(const dispatched_to_incident &e) {
   fd_response &response = get_response_for_fire_department(e.fire_department_id());
   response.incident_number = e.incident_number();
   response.aid_type = e.mutual_aid();
}


incident_dispatcher::fd_response& incident_dispatcher::get_response_for_fire_department(const id_type &fire_department_id) {
   auto e = end(fire_department_responses);
   auto i = find_if(begin(fire_department_responses), end(fire_department_responses), [fire_department_id](const fd_response &response) -> bool {
         return fire_department_id == response.fire_department_id;
      });

   if (i == e) {
      fd_response response;
      response.fire_department_id = fire_department_id;
      fire_department_responses.emplace_back(response);
      return fire_department_responses.back();
   }

   return *i;
}

}
}
