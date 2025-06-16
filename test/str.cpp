#include <gtest/gtest.h>
#include <manifold/os/str.hpp>
#include <string>

TEST(StringTest, SuffixPrefixCheck) {
  std::string s = "hello manifold";

  EXPECT_TRUE(manifold::str::ends_with(s, "manifold"));
  EXPECT_FALSE(manifold::str::ends_with("", "manifold"));

  EXPECT_TRUE(manifold::str::starts_with(s, "hello"));
  EXPECT_FALSE(manifold::str::starts_with("", "hello"));
}

TEST(StringTest, SplitReplaceJoin) {
  std::string s = "hello;manifold;strings";

  auto split = manifold::str::split(s, ";");
  EXPECT_EQ(split[0], "hello");
  EXPECT_EQ(split[1], "manifold");
  EXPECT_EQ(split[2], "strings");

  auto split2 = manifold::str::split("", ";");
  EXPECT_EQ(split2.size(), 0);

  auto replace = manifold::str::replace_all(split[2], "s", "c");
  EXPECT_EQ(replace, "ctringc");

  auto replace2 = manifold::str::replace_all("", "s", "c");
  EXPECT_EQ(replace2, "");

  auto join = manifold::str::join(split, " ");
  EXPECT_EQ(join, "hello manifold strings");

  auto join2 = manifold::str::join({}, "");
  EXPECT_EQ(join2, "");
}

TEST(StringTest, UpperLower) {
  EXPECT_EQ(manifold::str::to_upper("manifold"), "MANIFOLD");
  EXPECT_EQ(manifold::str::to_upper(""), "");

  EXPECT_EQ(manifold::str::to_lower("MANIFOLD"), "manifold");
  EXPECT_EQ(manifold::str::to_lower(""), "");
}

TEST(StringTest, TrimString) {
  auto s0 = "   hello";
  auto s1 = "manifold   ";
  auto s2 = "\t    strings   \n\t";

  EXPECT_EQ(manifold::str::trim(s0), "hello");
  EXPECT_EQ(manifold::str::trim(s1), "manifold");
  EXPECT_EQ(manifold::str::trim(s2), "strings");
  EXPECT_EQ(manifold::str::trim(""), "");
}

TEST(StringTest, AsCString) {
  auto cstr = manifold::str::as_cstr("manifold");
  EXPECT_EQ(strcmp(cstr, "manifold"), 0);
}
