#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <regex>
#include <variant>

using node_value_t = std::variant<std::string, double, int>;

struct regex_t {
  std::string str;
  std::regex r;

  regex_t(const std::string& base_str);
  bool operator==(const regex_t& other) const;
};

namespace std {
  template <class T1, class T2>
  struct hash<pair<T1, T2>> {
    size_t operator()(const std::pair<T1,T2>& p) const;
  };

  template <>
  struct hash<regex_t> {
    size_t operator()(const regex_t& regex) const;
  };

  std::string to_string(const std::vector<std::string>& string_vec);
  std::string to_string(const node_value_t& var);
}

#endif
