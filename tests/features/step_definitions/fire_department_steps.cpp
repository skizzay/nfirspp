// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include "infrastructure/optional.h"
#include <fakeit.hpp>
#include <kerchow/kerchow.h>
#include <boost/uuid/uuid_generators.hpp>
#include <gtest/gtest.h>
#include <cucumber-cpp/defs.hpp>

using cucumber::ScenarioScope;
using namespace firepp::business;
using namespace fakeit;
namespace bu = boost::uuids;
typedef bu::uuid id_type;
using firepp::infrastructure::details_::optional_value;

namespace {

class active_fd {
public:
   us_state state_value;
   fdid fdid_value;

   std::vector<id_type> firefighters;
   std::vector<id_type> stations;
   Mock<firepp::infrastructure::session> session;
   optional_value<fire_department> fd;
};


GIVEN("I have a fire department") {
   ScenarioScope<active_fd> context;
   bu::basic_random_generator<decltype(kerchow::picker)> generate_id{kerchow::picker};
   context->fd.emplace(context->firefighters, context->stations,
                       context->session.get(), generate_id());
}


WHEN("^I register the fire department (\\w{1,5})-([A-Z]{2})") {
   ScenarioScope<active_fd> context;
   REGEX_PARAM(std::string, fdid_str);
   context->fdid_value = fdid{fdid_str};
}


THEN("^the fire department should be registered") {
   ScenarioScope<active_fd> context;
   //ASSERT_EQ(context->fdid_value);
}

}
