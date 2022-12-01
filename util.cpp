#include "util.h"

regex_t::regex_t(const std::string& base_str) : str(base_str), r(base_str) {}

bool regex_t::operator==(const regex_t& other) const {
  return str == other.str;
}

template <class T1, class T2>
size_t std::hash<std::pair<T1, T2>>::operator()(const std::pair<T1,T2>& p) const {
  return (std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1));
}

size_t std::hash<regex_t>::operator()(const regex_t& regex) const {
  return std::hash<std::string>{}(regex.str);
}

std::string std::to_string(const std::vector<std::string>& string_vec) {
  std::string concat;
  for (auto const& s : string_vec) {
    concat += s;
  }
  return concat;
}

std::string std::to_string(const node_value_t& var) {
  if (const std::string* s = std::get_if<std::string>(&var)) {
    return "\"" + *s + "\"";
  } else if (const double* d = std::get_if<double>(&var)) {
    return std::to_string(*d);
  } else {
    return std::to_string(std::get<int>(var));
  }
}
