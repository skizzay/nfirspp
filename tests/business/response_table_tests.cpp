// vim: sw=3 ts=3 expandtab cindent
#include "business/entities/bits/response_table.h"
#include "kerchow/kerchow.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <gtest/gtest.h>

using namespace firepp::business::details_;

namespace {

struct dummy_response {
   boost::uuids::uuid unique_id = boost::uuids::nil_uuid();
};


using table_type = response_table<dummy_response, &dummy_response::unique_id>;
boost::uuids::basic_random_generator<decltype(kerchow::picker)> random_uuid{kerchow::picker};


TEST(response_table_tests, get_reponse_given_unknown_id_should_return_new_entry) {
   // Given
   table_type target;
   auto expected_id = random_uuid();

   // When
   auto &actual = target.get_response(expected_id);

   // Then
   ASSERT_EQ(expected_id, actual.unique_id);
}


TEST(response_table_tests, get_reponse_given_known_id_should_return_same_entry) {
   // Given
   table_type target;
   auto id = random_uuid();
   auto &expected = target.get_response(id);

   // When
   auto &actual = target.get_response(id);

   // Then
   ASSERT_EQ(&expected, &actual);
}

}
