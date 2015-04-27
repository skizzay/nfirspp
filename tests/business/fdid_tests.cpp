// vim: sw=3 ts=3 expandtab cindent
#include "business/values/fdid.h"
#include <gtest/gtest.h>

namespace {

using namespace firepp::business;

TEST(fdid_tests, valid_after_default_construction_should_return_false) {
   // Given
   fdid target;

   // When
   bool actual = target.valid();

   // Then
   ASSERT_FALSE(actual);
}


TEST(fdid_tests, valid_after_valid_construction_should_return_true) {
   // Given
   fdid target{"abs"};

   // When
   bool actual = target.valid();

   // Then
   ASSERT_TRUE(actual);
}


TEST(fdid_tests, constructor_given_invalid_input_should_throw_invalid_argument) {
   // Given, When, Then
   ASSERT_THROW(fdid{"..."}, std::invalid_argument);
   ASSERT_THROW(fdid{"not valid input"}, std::invalid_argument);
}

}
