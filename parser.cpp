#include <iostream>
#include <sstream>
#include "token.h"
#include "parser.h"

state parser::current_state = START_TK;
state parser::next_state = NODE_NAME_TK;
std::string parser::file_loc = "";
std::ifstream parser::file;
int parser::row = 1;
int parser::col = 1;

parse_exception::parse_exception(
  const std::string& file_loc,
  const size_t row,
  const size_t col,
  const std::string& msg
) {
  std::ostringstream oss;
  oss << file_loc << ":" << row << ":" << col << ": parse error: " << msg;
  except_msg = oss.str();
}

void parser::read_whitespace() {
  std::string s;

  while (std::regex_match(s = file.peek(), std::regex("[ \\t]"))) {
    file.get();
    col++;
  }
}

void parser::set_next_state() {
  if (current_state == START_TK) {
    next_state = NODE_NAME_TK;
    return;
  }

  if (current_state != STR_TK) read_whitespace();

  char c;
  if ((c = file.peek()) == EOF) {
    next_state = EOF_TK;
    return;
  }

  std::string s;
  auto current_transition_map = transition_map.at(current_state);
  for (auto const& [regex, map_next_state] : current_transition_map) {
    if (std::regex_match(s = c, regex.r)) {
      next_state = map_next_state;
      return;
    }
  }
  throw parse_exception(file_loc, row, col, "unexpected character");
}

token parser::parse_token() {
  std::string s;
  std::vector<std::string> data;
  bool state_changed_once_flag = false;

  set_next_state();
  while (next_state == current_state || !state_changed_once_flag) {
    if (!state_changed_once_flag && (next_state != current_state)) {
      current_state = next_state;
      state_changed_once_flag = true;
    }
    data.push_back(s = file.get());
    if (s == "\n") {
      row++;
      col = 1;
    } else {
      col++;
    }
    set_next_state();
  }

  return token(current_state, std::to_string(data));
}

token parser::parse_token(const state& expected_token) {
  token t = parse_token();
  if (t.token_state == expected_token) return t;
  throw parse_exception(file_loc, row, col-1,
      "token mismatch, expected " + state_name.at(expected_token));
}

token parser::parse_number() {
  token t = parse_token();
  if (t.token_state == REAL_TK) {
    if (t.data.find('.') == std::string::npos) return token(INT_TK, t.data);
    return t;
  }
  throw parse_exception(file_loc, row, col, "token mismatch, expected " +
      state_name.at(REAL_TK) + " or " + state_name.at(INT_TK));
}

datanode parser::parse_node() {
  datanode root;
  while (current_state != EOF_TK) {
    if (next_state != NODE_NAME_TK) return root;
    token node_name = parse_token(NODE_NAME_TK);
    token nl_or_equals = parse_token();
    if (nl_or_equals.token_state == EQUALS_TK) {
      if (next_state == L_QUOTE_TK) {
        parse_token(L_QUOTE_TK);
        root[node_name.data] = parse_token(STR_TK).data;
        parse_token(R_QUOTE_TK);
      } else if (next_state == REAL_TK) {
        token t = parse_number();
        if (t.token_state == REAL_TK) root[node_name.data] = std::atof(t.data.c_str());
        else root[node_name.data] = std::atoi(t.data.c_str());
      }
      parse_token(NEWLINE_TK);
      continue;
    } else if (nl_or_equals.token_state == NEWLINE_TK) {
      parse_token(L_BRACE_TK);
      parse_token(NEWLINE_TK);
      root[node_name.data] = parse_node();
      parse_token(R_BRACE_TK);
      parse_token(NEWLINE_TK);
      continue;
    }
    throw parse_exception(file_loc, row, col, "unable to parse node");
  }
  return root;
}

datanode parser::load(const std::string& location) {
  file_loc = location;
  file.open(location, std::ifstream::in);
  datanode dn = parse_node();
  file.close();
  return dn;
}
