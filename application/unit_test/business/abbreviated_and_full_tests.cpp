// vim: sw=3 ts=3 expandtab cindent
#include "business/bits/value_component.h"
#include <gtest/gtest.h>

using namespace nfirspp::business::details_;


namespace {

const char abbreviated_value[] = "ab";
const char full_value[] = "blammo";


class aaf_testing_tag final : public abbreviated_and_full<aaf_testing_tag, 5> {
public:
   using abbreviated_and_full<aaf_testing_tag, 5>::abbreviated_and_full;

   static inline const char * type_name() noexcept {
      return "abbreviated and full testing";
   }

   static inline aaf_testing_tag create_target() {
      return aaf_testing_tag{abbreviated_value, full_value};
   }
};


TEST(abbreviated_and_full_tests, valid_given_abbreviated_should_return_true) {
   // given
   auto target = aaf_testing_tag::create_target();

   // when
   bool actual = target.valid();

   // then
   ASSERT_TRUE(actual);
}


TEST(abbreviated_and_full_tests, valid_given_default_constructed_abbreviated_should_return_false) {
   // given
   aaf_testing_tag target;

   // when
   bool actual = target.valid();

   // then
   ASSERT_FALSE(actual);
}


TEST(abbreviated_and_full_tests, abbreviated_given_valid_abbreviated_should_return_abbreviated) {
   // given
   auto target = aaf_testing_tag::create_target();

   // when
   auto actual = target.abbreviated();

   // then
   ASSERT_EQ(abbreviated_value, actual);
}


TEST(abbreviated_and_full_tests, abbreviated_given_default_constructed_abbreviated_should_return_empty_abbreviated) {
   // given
   aaf_testing_tag target;

   // when
   auto actual = target.abbreviated();

   // then
   ASSERT_TRUE(actual.empty());
}


TEST(abbreviated_and_full_tests, full_given_valid_full_should_return_full) {
   // given
   auto target = aaf_testing_tag::create_target();

   // when
   auto actual = target.full();

   // then
   ASSERT_EQ(full_value, actual);
}


TEST(abbreviated_and_full_tests, full_given_default_constructed_full_should_return_empty_full) {
   // given
   aaf_testing_tag target;

   // when
   auto actual = target.full();

   // then
   ASSERT_TRUE(actual.empty());
}

}
