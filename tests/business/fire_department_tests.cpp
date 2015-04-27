// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include <sequence.h>
#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>
#include <random>

extern std::mt19937 twister;

namespace {

typedef boost::uuids::uuid id_type;
using sequencing::select;
using sequencing::single;
using sequencing::where;
using namespace cddd::cqrs;
using namespace firepp::business;

auto random = [] (auto ... a) {
   std::uniform_int_distribution<std::common_type_t<decltype(a)...>> generate{a...};
   return generate(twister);
};

class fire_department_tests : public ::testing::Test {
public:
   fire_department_tests() :
      ::testing::Test{},
      generate_uuid{twister},
      target{generate_uuid()}
   {
   }

   boost::uuids::basic_random_generator<std::mt19937> generate_uuid{twister};
   fire_department target;
};


TEST_F(fire_department_tests, when_enroll_firefighter_then_firefighter_should_be_enrolled) {
   // given
   id_type firefighter_id = generate_uuid();

   // when
   target.enroll_firefighter(firefighter_id);

   // then
   const auto &actual = target.uncommitted_events() |
                          where([] (auto evt) { return evt->type() == typeid(firefighter_enrolled_into_fire_department); }) |
                          select([] (auto evt) {
                                return static_cast<const basic_domain_event<firefighter_enrolled_into_fire_department> &>(*evt).event();
                             }) |
                          single();
   ASSERT_EQ(firefighter_id, actual.firefighter_id());
}

}
