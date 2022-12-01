#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include "token.h"
#include "datanode.h"

class parse_exception : public std::exception {
  private:
    std::string except_msg;

  public:
    parse_exception(
      const std::string& file_loc,
      const size_t row,
      const size_t col,
      const std::string& msg
    );

    const char* what() const noexcept override {
      return except_msg.c_str();
    }
};

class parser {
  private:
    static state current_state;
    static state next_state;
    static std::string file_loc;
    static std::ifstream file;
    static int row;
    static int col;

    static void read_whitespace();
    static void set_next_state();
    static token parse_token();
    static token parse_token(const state& expected_token);
    static token parse_number();
    static token parse_node_name();
    static datanode parse_values();
    static datanode parse_node();

  public:
    static datanode load(const std::string& location);
};
#endif
