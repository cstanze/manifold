#include <manifold/os/env.hpp>
#include <manifold/os/fs.hpp>

namespace manifold::fs {

auto cwd() -> path_type { return std::filesystem::current_path(); }

auto home() -> path_type {
  return std::filesystem::path(manifold::env::get("HOME"));
}

auto read_file(const path_type &path)
    -> manifold::result<std::string, fs::Error> {
  if (!manifold::fs::path_exists(path)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  std::ifstream file(path);
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  return contents;
}

auto read_file_bytes(const path_type &path)
    -> manifold::result<std::vector<u8>, fs::Error> {
  if (!manifold::fs::path_exists(path)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  std::ifstream file(path, std::ios::binary);
  std::vector<u8> contents((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
  return contents;
}

auto write_bytes(const path_type &path, const std::vector<u8> &bytes)
    -> manifold::result<void, fs::Error> {
  if (!manifold::fs::path_exists(path)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  std::ofstream file(path, std::ios::binary);
  file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
  file.close();

  return manifold::result<void, fs::Error>();
}

auto path_exists(const path_type &path) -> bool {
  return std::filesystem::exists(path);
}

auto relative_path(const path_type &path, const path_type &dir)
    -> manifold::result<path_type, Error> {
  if (!manifold::fs::path_exists(path)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  return std::filesystem::relative(path, dir);
}

auto absolute_path(const path_type &path) -> manifold::result<path_type, Error> {
  if (!manifold::fs::path_exists(path)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  return std::filesystem::absolute(path);
}

auto is_absolute(const path_type &path) -> bool { return path.is_absolute(); }

auto is_relative(const path_type &path) -> bool { return path.is_relative(); }

auto is_dir(const path_type &path) -> bool {
  return std::filesystem::is_directory(path);
}

auto is_file(const path_type &path) -> bool {
  return std::filesystem::is_regular_file(path);
}

auto search(const path_type &dir,
            const std::function<bool(const path_type &path)> &matcher)
    -> manifold::result<path_type, Error> {
  if (!manifold::fs::path_exists(dir)) {
    return manifold::fail(fs::Error::NoFileExists);
  }

  for (auto &p : std::filesystem::recursive_directory_iterator(dir)) {
    if (matcher(p.path())) {
      return p.path();
    }
  }

  return manifold::fail(fs::Error::NoFileExists);
}

} // namespace manifold::fs
