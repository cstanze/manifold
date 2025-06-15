#include <manifold/os/str.hpp>

namespace manifold::str {

auto ends_with(const std::string &str, const std::string &suffix) -> bool {
  if (str.length() >= suffix.length()) {
    return (0 == str.compare(str.length() - suffix.length(), suffix.length(), suffix));
  }

  return false;
}

auto starts_with(const std::string &str, const std::string &prefix) -> bool {
  if (str.length() >= prefix.length()) {
    return (0 == str.compare(0, prefix.length(), prefix));
  }

  return false;
}

auto split(const std::string &str, const std::string &delim) -> std::vector<std::string> {
  if (str.empty())
    return {};
  
  if (delim.empty()) {
    // split into chars
    std::vector<std::string> result;
    for (size_t i = 0; i < str.length(); i++) {
      result.push_back(str.substr(i, 1));
    }

    return result;
  }

  std::vector<std::string> result;
  auto start = 0;
  auto end = str.find(delim);
  while (end != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + delim.size();
    end = str.find(delim, start);
  }

  result.push_back(str.substr(start, end));
  return result;
}

auto replace_all(const std::string &str, const std::string &from,
                const std::string &to) -> std::string {
  std::string result = str;
  size_t start_pos = 0;

  while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
    result.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }

  return result;
}

auto join(const std::vector<std::string> &strs, const std::string &delim)
    -> std::string {
  std::string result;
  for (size_t i = 0; i < strs.size(); i++) {
    result += strs[i];
    if (i != strs.size() - 1)
      result += delim;
  }

  return result;
}

auto to_lower(const std::string &str) -> std::string {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

auto to_upper(const std::string &str) -> std::string {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

auto trim(const std::string &str) -> std::string {
  std::string result = str;
  result.erase(result.begin(),
               std::find_if(result.begin(), result.end(),
                            [](int ch) { return !std::isspace(ch); }));
  result.erase(std::find_if(result.rbegin(), result.rend(),
                            [](int ch) { return !std::isspace(ch); })
                   .base(),
               result.end());
  return result;
}

auto as_cstr(const std::string &str) -> const i8 * {
  auto *cstr = new i8[str.length() + 1];
  std::strcpy(const_cast<char*>(cstr), str.c_str());
  cstr[str.length()] = '\0';

  return cstr;
}
}
