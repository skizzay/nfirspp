#include <iostream>
#include <random>
#include <gmock/gmock.h>

std::mt19937 twister;

namespace {

void seed_rng() {
   int seed = ::testing::GTEST_FLAG(random_seed);
   if (seed == 0) {
      std::random_device generate_seed;
      // This is the acceptable range from Google.
      while (!((0 < seed) && (seed < 100000))) {
         seed = generate_seed();
      }
   }
   std::cout << "To reproduce results, specify '--gtest_random_seed=" << seed << "' on the command line." << std::endl;
   twister.seed(seed);
}

}

int main(int argc, char **argv) {
   ::testing::InitGoogleMock(&argc, argv);
   seed_rng();
   return RUN_ALL_TESTS();
}
