// vim: sw=3 ts=3 expandtab cindent
#include "business/values/address.h"
#include <gtest/gtest.h>
#include <random>

extern std::mt19937 twister;

namespace {

using namespace firepp::business;

auto random = [] (auto ... a) {
   std::uniform_int_distribution<std::common_type_t<decltype(a)...>> generate{a...};
   return generate(twister);
};


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
   ASSERT_THROW(fips_county_code{random(uint16_t{0})}, std::invalid_argument);
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
   fips_county_code target{random(uint16_t{1}, uint16_t{999})};

   // when
   bool actual = target.valid();

   // then
   ASSERT_TRUE(actual);
}

}
