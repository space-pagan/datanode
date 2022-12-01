#ifndef DATANODE_H
#define DATANODE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <optional>
#include <fstream>
#include "util.h"

class datanode {
  private:
    std::optional<node_value_t> content;
    std::vector<std::string> childname_vec;
    std::unordered_map<std::string, datanode> children;

  public:
    const std::optional<std::string> GetString() const;
    const std::optional<double> GetReal() const;
    const std::optional<int> GetInt() const;
    const std::optional<node_value_t> find(const std::string& search_string);

    datanode& operator[](const std::string& childname);
    datanode& operator=(const node_value_t& value);

    void save(
      std::ostream& of,
      std::string indent = ""
    ) const;

    void save(const std::string& location) const;
};

#endif
