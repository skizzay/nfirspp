// vim: sw=3 ts=3 expandtab cindent
#include "business/bits/value_component.h"
#include <gtest/gtest.h>

using namespace firepp::business::details_;


namespace {

struct length_testing_tag final : length_validation_and_assignment {
   static inline const char * type_name() noexcept {
      return "length testing";
   }
};


struct regex_testing_tag final : regex_validation_and_assignment<regex_testing_tag, std::index_sequence<1, 3>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex r{"^([0-9]{2,4})$"};
      return r;
   }

   static inline const char * type_name() noexcept {
      return "regex testing";
   }
};


template<class Tag>
class value_component_tests : public ::testing::Test {
public:
   inline value_component<Tag, 4> create_target() {
      return value_component<Tag, 4>{value};
   }

   std::string value;
};


TYPED_TEST_CASE_P(value_component_tests);


TYPED_TEST_P(value_component_tests, constructor_given_empty_input_should_throw_invalid_argument) {
   // given
   this->value.clear();

   // when & then
   ASSERT_THROW(this->create_target(), std::invalid_argument);
}


TYPED_TEST_P(value_component_tests, constructor_given_mismatching_input_should_throw_invalid_argument) {
   // given
   this->value = "abc1234";

   // when & then
   ASSERT_THROW(this->create_target(), std::invalid_argument);
}


TYPED_TEST_P(value_component_tests, valid_given_value_should_return_true) {
   // given
   this->value = "123";
   auto target = this->create_target();

   // when
   bool actual = target.valid();

   // then
   ASSERT_TRUE(actual);
}


TYPED_TEST_P(value_component_tests, valid_given_default_constructed_value_should_return_false) {
   // given
   value_component<TypeParam, 8> target;

   // when
   bool actual = target.valid();

   // then
   ASSERT_FALSE(actual);
}


TYPED_TEST_P(value_component_tests, to_string_given_valid_value_should_return_value) {
   // given
   this->value = "89";
   auto target = this->create_target();

   // when
   auto actual = target.to_string();

   // then
   ASSERT_EQ(this->value, actual);
}


TYPED_TEST_P(value_component_tests, to_string_given_default_constructed_value_should_return_empty_value) {
   // given
   value_component<TypeParam, 8> target;

   // when
   auto actual = target.to_string();

   // then
   ASSERT_TRUE(actual.empty());
}


REGISTER_TYPED_TEST_CASE_P(value_component_tests,
                           constructor_given_empty_input_should_throw_invalid_argument,
                           constructor_given_mismatching_input_should_throw_invalid_argument,
                           valid_given_value_should_return_true,
                           valid_given_default_constructed_value_should_return_false,
                           to_string_given_valid_value_should_return_value,
                           to_string_given_default_constructed_value_should_return_empty_value);


typedef ::testing::Types<regex_testing_tag, length_testing_tag> types;
INSTANTIATE_TYPED_TEST_CASE_P(value_tests, value_component_tests, types);

}
