#include <gtest/gtest.h>
#include <manifold/adt/bitflags.hpp>

enum class Permission { Read, Write };

using namespace manifold::adt;

class BitFlagTest : public testing::Test {
protected:
  BitFlagTest()
      : bp0(Permission::Write), bp1(Permission::Read, Permission::Write) {}

  BitFlags<Permission> bp0;
  BitFlags<Permission> bp1;
};

TEST_F(BitFlagTest, EqualityOperations) {
  EXPECT_TRUE(bp0 != bp1);
  EXPECT_FALSE(bp0 == bp1);
}

TEST_F(BitFlagTest, MethodOperations) {
  ASSERT_NE(bp0.raw(), bp1.raw());

  // [] operator (contains)
  ASSERT_FALSE(bp0[Permission::Read]);
  ASSERT_TRUE(bp1[Permission::Read]);

  // set/contains methods
  bp0.set(Permission::Read, true);
  ASSERT_TRUE(bp0.contains(Permission::Read));

  // clear/empty methods
  bp1.clear();
  ASSERT_TRUE(bp1.empty());
  ASSERT_FALSE(bp1.contains(Permission::Read));
}
