// vim: sw=3 ts=3 expandtab cindent
#include "business/values/address.h"
#include <gtest/gtest.h>
#include <random>

namespace {

using namespace nfirspp::business;

inline uint16_t random(uint16_t low, uint16_t high) {
   std::mt19937_64::result_type seed = static_cast<std::mt19937_64::result_type>(::testing::UnitTest::GetInstance()->random_seed());
   std::mt19937_64 engine{seed};
   std::uniform_int_distribution<uint16_t> generate{low, high};
   return generate(engine);
}

inline uint16_t random(uint16_t low) {
   return random(low, std::numeric_limits<uint16_t>::max());
}


TEST(us_street_tests, valid_given_valid_name_and_type_should_return_true) {
   // given
   us_street target{street_name{"Booyah"}, street_type::drive};

   // when
   bool actual = target.valid();

   // then
   ASSERT_TRUE(actual);
}


TEST(us_street_tests, valid_after_default_construction_should_return_false) {
   // given
   us_street target;

   // when
   bool actual = target.valid();

   // then
   ASSERT_FALSE(actual);
}


TEST(us_street_tests, constructor_given_invalid_name_should_throw_invalid_argument) {
   // given, when, then
   ASSERT_THROW(us_street({}, street_type::cove), std::invalid_argument);
}


TEST(us_street_tests, constructor_given_invalid_type_should_throw_invalid_argument) {
   // given, when, then
   ASSERT_THROW(us_street(street_name{"Blammo"}, street_type{}), std::invalid_argument);
}


TEST(fips_county_code_tests, constructor_given_0_should_throw_invalid_argument) {
   // given, when, then
   ASSERT_THROW(fips_county_code{0}, std::invalid_argument);
}


TEST(fips_county_code_tests, constructor_given_too_large_value_should_throw_invalid_argument) {
   // given, when, then
   ASSERT_THROW(fips_county_code{random(0)}, std::invalid_argument);
}


TEST(fips_county_code_tests, valid_after_default_construction_should_return_false) {
   // given
   fips_county_code target;

   // when
   bool actual = target.valid();

   // then
   ASSERT_FALSE(actual);
}


TEST(fips_county_code_tests, valid_after_valid_construction_should_return_true) {
   // given
   fips_county_code target{random(1, 999)};

   // when
   bool actual = target.valid();

   // then
   ASSERT_TRUE(actual);
}

}
