#include "datanode.h"

const std::optional<std::string> datanode::GetString() const {
  if (content.has_value()) {
    if (const std::string* s = std::get_if<std::string>(&(content.value()))) {
      return *s;
    }
  }
  return {};
}

const std::optional<double> datanode::GetReal() const {
  if (content.has_value()) {
    if (const double* d = std::get_if<double>(&(content.value()))) {
      return *d;
    }
  }
  return {};
}

const std::optional<int> datanode::GetInt() const {
  if (content.has_value()) {
    if (const int* i = std::get_if<int>(&(content.value()))) {
      return *i;
    }
  }
  return {};
}

const std::optional<node_value_t> datanode::find(const std::string& search_string) {
  if (children.contains(search_string)) {
    return children[search_string].content;
  }
  return {};
}

datanode& datanode::operator[](const std::string& childname) {
  if (!children.contains(childname)) {
    children[childname] = datanode();
    childname_vec.push_back(childname);
  }
  return children[childname];
}

datanode& datanode::operator=(const node_value_t& value) {
  childname_vec.clear();
  children.clear();
  content = value;
  return *this;
}

void datanode::save(
  std::ostream& of,
  std::string indent
) const {
  for (auto const& childname : childname_vec) {
    auto const& child = children.at(childname);
    if (child.content.has_value()) {
      of << indent << childname << " = ";
      of << std::to_string(child.content.value()) << "\n";
    } else {
      of << indent << childname << "\n";
      of << indent << "{\n";
      child.save(of, indent + "  ");
      of << indent << "}\n";
    }
  }
}

void datanode::save(const std::string& location) const {
  std::ofstream file(location);
  save(file);
  file.close();
}
