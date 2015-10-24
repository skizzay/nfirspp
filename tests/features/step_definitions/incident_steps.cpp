// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/incident.h"
#include "business/events/dispatched_to_incident.h"
#include "infrastructure/incident_number_provider.h"
#include "infrastructure/optional.h"
#include "cqrs/domain_event.h"
#include <fakeit.hpp>
#include <kerchow/kerchow.h>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <gtest/gtest.h>
#include <cucumber-cpp/defs.hpp>

using cucumber::ScenarioScope;
using namespace cddd::cqrs;
using namespace firepp::business;
using namespace fakeit;
namespace bu = boost::uuids;
typedef bu::uuid id_type;
using firepp::infrastructure::details_::optional_value;


namespace std {

void PrintTo(deque<shared_ptr<cddd::cqrs::domain_event>>::iterator i, ostream *os) {
   *os << *i;
}

}


namespace {

bu::string_generator string_to_uuid;
inline auto now() {
   return boost::posix_time::microsec_clock::universal_time();
}


class active_incident {
public:
   bu::basic_random_generator<decltype(kerchow::picker)> generate_id{kerchow::picker};

   Mock<firepp::infrastructure::session> session;
   Mock<firepp::infrastructure::incident_number_provider> incident_number_provider;
   id_type session_id = generate_id();
   id_type session_user_id = generate_id();
   id_type location_id = generate_id();
   optional_value<incident> target;
};


GIVEN("^I have an incident '(.*)'") {
   REGEX_PARAM(std::string, incident_id);
   ScenarioScope<active_incident> context;
   context->target.emplace(context->session.get(), context->incident_number_provider.get(), string_to_uuid(incident_id));
}


WHEN("^I dispatch the fire department '(.*)' as (.*) response") {
   REGEX_PARAM(std::string, fire_department_id);
   REGEX_PARAM(std::string, dispatch_type);
   ScenarioScope<active_incident> context;
   When(Method(context->session, user_id)).Return(context->session_user_id);
   When(Method(context->session, time)).Return(now());
   When(Method(context->incident_number_provider, get_incident_number_for)).Return(kerchow::picker.pick<size_t>());

   mutual_aid_type mutual_aid{mutual_aid_type::primary};

   if (dispatch_type == "automatic") {
      mutual_aid = mutual_aid_type::automatic;
   }
   else if (dispatch_type == "requested") {
      mutual_aid = mutual_aid_type::requested;
   }
   else if (dispatch_type == "other") {
      mutual_aid = mutual_aid_type::other;
   }

   context->target->dispatch_for_response(string_to_uuid(fire_department_id),
                                          boost::posix_time::microsec_clock::universal_time(),
                                          mutual_aid);
}


THEN("^the fire department '(.*)' should have been (.*) dispatched") {
   REGEX_PARAM(std::string, fire_department_id);
   REGEX_PARAM(std::string, dispatch_type);
   ScenarioScope<active_incident> context;
   mutual_aid_type mutual_aid = mutual_aid_type::primary;

   if (dispatch_type == "automatic") {
      mutual_aid = mutual_aid_type::automatic;
   }
   else if (dispatch_type == "requested") {
      mutual_aid = mutual_aid_type::requested;
   }
   else if (dispatch_type == "other") {
      mutual_aid = mutual_aid_type::other;
   }

   auto events = context->target->uncommitted_events();
   auto e = end(events);
   auto i = find_if(begin(events), e, [&](const auto &evt) {
         if (is_event<dispatched_to_incident>(*evt)) {
            const dispatched_to_incident &response = unsafe_event_cast<dispatched_to_incident>(*evt);
            return response.mutual_aid() == mutual_aid &&
                   response.fire_department_id() == string_to_uuid(fire_department_id);
         }
         return false;
      });
   ASSERT_NE(i, e);
}

}
