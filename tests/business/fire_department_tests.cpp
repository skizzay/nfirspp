// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/fire_department.h"
#include "infrastructure/optional.h"
#include "infrastructure/session.h"
#include <fakeit.hpp>
#include <kerchow/kerchow.h>
#include <sequence.h>
#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>

namespace {

typedef boost::uuids::uuid id_type;
using sequencing::from;
using sequencing::select;
using sequencing::single;
using sequencing::where;
using firepp::infrastructure::details_::optional_value;
using namespace fakeit;
using namespace cddd::cqrs;
using namespace firepp::business;

class fire_department_tests : public ::testing::Test {
public:
   fire_department_tests() :
      ::testing::Test{},
      generate_uuid{kerchow::picker},
      firefighters{},
      stations{},
      session{},
      target{}
   {
      target.emplace(firefighters, stations, session.get(), generate_uuid());
   }

   virtual ~fire_department_tests() noexcept {}

   boost::uuids::basic_random_generator<decltype(kerchow::picker)> generate_uuid;
   std::vector<id_type> firefighters;
   std::vector<id_type> stations;
   Mock<firepp::infrastructure::session> session;
   optional_value<fire_department> target;
};


TEST_F(fire_department_tests, when_enroll_firefighter_then_firefighter_should_be_enrolled) {
   // given
   id_type firefighter_id = generate_uuid();
   auto userid = generate_uuid();
   auto now = boost::posix_time::microsec_clock::universal_time();
   auto today = now.date();

   When(Method(session, user_id)).Return(userid);
   When(Method(session, time)).Return(now);

   // when
   target->enroll_firefighter(firefighter_id, today);

   // then
   const auto &actual = from(target->uncommitted_events()) |
                          where([] (auto evt) {
                                return evt->type() == cddd::utils::type_id_generator::get_id_for_type<firefighter_enrolled_into_fire_department>();
                             }) |
                          select([] (auto evt) {
                                return static_cast<const basic_domain_event<firefighter_enrolled_into_fire_department> &>(*evt).event();
                             }) |
                          single();
   ASSERT_EQ(target->id(), actual.fire_department_id());
   ASSERT_EQ(firefighter_id, actual.firefighter_id());
   ASSERT_EQ(today, actual.effective_date());
   ASSERT_EQ(userid, actual.user_id());
   ASSERT_EQ(now, actual.timestamp());
}


TEST_F(fire_department_tests, when_enroll_firefighter_with_bad_date_then_throw_invalid_argument) {
   // given
   id_type firefighter_id = generate_uuid();

   // when & then
   ASSERT_THROW(target->enroll_firefighter(firefighter_id, boost::gregorian::date{}), std::invalid_argument);
}

}
