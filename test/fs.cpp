#include <ctime>
#include <gtest/gtest.h>
#include <manifold/os/env.hpp>
#include <manifold/os/fs.hpp>
#include <random>
#include <string>

class FilesystemTest : public testing::Test {
protected:
  std::filesystem::path testDir;

  void SetUp() override {
    std::mt19937 mt(time(nullptr));
    u32 rnum = mt();

    testDir = std::filesystem::temp_directory_path() /
              ("mf_fs" + std::to_string(rnum));
    std::filesystem::create_directory(testDir);
  }

  void TearDown() override { std::filesystem::remove_all(testDir); }
};

/// @brief RAII compliant file, deleted when the object is deleted
class ScopedFile {
public:
  std::filesystem::path path;
  ScopedFile(const std::filesystem::path &p, const std::string &contents = "")
      : path(p) {
    std::ofstream f(p);
    f << contents;
  }

  ~ScopedFile() {
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }
};

/// cwd(), home()
TEST_F(FilesystemTest, Environment) {
  std::filesystem::current_path(testDir);
  #ifndef MANIFOLD_PLATFORM_APPLE
  EXPECT_EQ(std::filesystem::absolute(testDir), manifold::fs::cwd()); // /var vs /private/var, macOS doesn't pass this test
  #endif

  EXPECT_EQ(std::filesystem::path(manifold::env::get("HOME")),
            manifold::fs::home());
}

/// write_bytes(), read_file_bytes(), read_file()
TEST_F(FilesystemTest, ReadWriteFiles) {
  auto file = ScopedFile(testDir / "test");
  EXPECT_FALSE(manifold::fs::write_bytes(file.path, {0xAA, 0xBB, 0xCC, 0xDD})
                   .has_error());

  auto bytesResult = manifold::fs::read_file_bytes(file.path);
  EXPECT_FALSE(bytesResult.has_error());
  EXPECT_EQ(bytesResult.value(), std::vector<u8>({0xAA, 0xBB, 0xCC, 0xDD}));

  auto fileTxt = ScopedFile(testDir / "test2.txt", "hello manifold!");
  auto txtResult = manifold::fs::read_file(fileTxt.path);
  EXPECT_FALSE(txtResult.has_error());
  EXPECT_EQ(txtResult.value(), "hello manifold!");
}

/// absolute_path(), is_absolute(), relative_path(), is_relative()
TEST_F(FilesystemTest, AbsoluteRelativePath) {
  auto file = ScopedFile(testDir / "test");

  auto absPath = manifold::fs::absolute_path(file.path);
  EXPECT_FALSE(absPath.has_error());
  EXPECT_EQ(absPath.value(), std::filesystem::absolute(file.path));

  auto relPath = manifold::fs::relative_path(file.path, testDir);
  EXPECT_FALSE(relPath.has_error());
  EXPECT_EQ(relPath.value(), std::filesystem::relative(file.path, testDir));

  EXPECT_TRUE(manifold::fs::is_absolute(absPath.value()));
  EXPECT_FALSE(manifold::fs::is_absolute(relPath.value()));

  EXPECT_TRUE(manifold::fs::is_relative(relPath.value()));
  EXPECT_FALSE(manifold::fs::is_relative(absPath.value()));
}

/// is_file(), is_dir()
TEST_F(FilesystemTest, FileTypes) {
  auto file = ScopedFile(testDir / "test");

  EXPECT_TRUE(manifold::fs::is_file(file.path));
  EXPECT_FALSE(manifold::fs::is_file(testDir));

  EXPECT_TRUE(manifold::fs::is_dir(testDir));
  EXPECT_FALSE(manifold::fs::is_dir(file.path));
}

/// search()
TEST_F(FilesystemTest, SearchFiles) {
  auto file = ScopedFile(testDir / "first.test");
  auto file2 = ScopedFile(testDir / "second.test");
  auto file3 = ScopedFile(testDir / "not_a.tes");

  // expect 3 files
  EXPECT_EQ(std::count_if(std::filesystem::directory_iterator(testDir),
                          std::filesystem::directory_iterator(),
                          [](const auto &entry) {
                            return std::filesystem::is_regular_file(entry);
                          }),
            3);

  auto nonTestFileRes = manifold::fs::search(
      testDir, [](const manifold::fs::path_type &path) -> bool {
        return path.string().find("test") == std::string::npos;
      });
  EXPECT_FALSE(nonTestFileRes.has_error());
  EXPECT_EQ(nonTestFileRes.value().filename().string(), "not_a.tes");
}
