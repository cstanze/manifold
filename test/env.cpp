#include <manifold/os/env.hpp>
#include <gtest/gtest.h>
#include <random>
#include <ctime>

class EnvironmentTest : public testing::Test {
protected:
  EnvironmentTest() : mt(time(nullptr)), rnum(mt()) {}

  std::mt19937 mt;
  u64 rnum;
};

TEST_F(EnvironmentTest, SetGetEnvVar) {
  manifold::env::set("__MANIFOLD_TEST_VAR", std::to_string(rnum));
  EXPECT_EQ(manifold::env::get("__MANIFOLD_TEST_VAR"), std::to_string(rnum));
}

TEST_F(EnvironmentTest, ProcessorCount) {
  // more of a sanity check, less of a real test
  ASSERT_EQ(manifold::env::processor_count(), std::thread::hardware_concurrency());
}
