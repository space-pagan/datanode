#ifndef TOKEN_H
#define TOKEN_H

#include <unordered_map>
#include <string>
#include "util.h"

enum state {
  START_TK,
  NODE_NAME_TK,
  NEWLINE_TK,
  L_BRACE_TK,
  R_BRACE_TK,
  EQUALS_TK,
  L_QUOTE_TK,
  STR_TK,
  R_QUOTE_TK,
  INT_TK,
  REAL_TK,
  EOF_TK,
};

inline std::unordered_map<state, std::string> state_name = {
  {START_TK,      "START_TK"},
  {NODE_NAME_TK,  "NODE_NAME_TK"},
  {NEWLINE_TK,    "NEWLINE_TK"},
  {L_BRACE_TK,    "L_BRACE_TK"},
  {R_BRACE_TK,    "R_BRACE_TK"},
  {EQUALS_TK,     "EQUALS_TK"},
  {L_QUOTE_TK,    "L_QUOTE_TK"},
  {STR_TK,        "STR_TK"},
  {R_QUOTE_TK,    "R_QUOTE_TK"},
  {INT_TK,        "INT_TK"},
  {REAL_TK,       "REAL_TK"},
  {EOF_TK,        "EOF_TK"},
};

inline std::unordered_map<state, std::unordered_map<regex_t, state>> transition_map = {
  {NODE_NAME_TK,
    {
      {regex_t("[^\\n={}]"), NODE_NAME_TK},
      {regex_t("\\n"), NEWLINE_TK},
      {regex_t("="), EQUALS_TK},
    }},

  {NEWLINE_TK,
    {
      {regex_t("[{]"), L_BRACE_TK},
      {regex_t("[}]"), R_BRACE_TK},
      {regex_t("[^\\n={}]"), NODE_NAME_TK},
    }},

  {L_BRACE_TK,
    {
      {regex_t("\\n"), NEWLINE_TK},
    }},

  {R_BRACE_TK,
    {
      {regex_t("\\n"), NEWLINE_TK},
    }},

  {EQUALS_TK,
    {
      {regex_t("[\"]"), L_QUOTE_TK},
      {regex_t("[0-9]"), REAL_TK},
    }},

  {L_QUOTE_TK,
    {
      {regex_t("[^\"\\n]"), STR_TK},
      {regex_t("[\"]"), R_QUOTE_TK},
    }},

  {STR_TK,
    {
      {regex_t("[^\"\\n]"), STR_TK},
      {regex_t("[\"]"), R_QUOTE_TK},
    }},

  {R_QUOTE_TK,
    {
      {regex_t("[\n]"), NEWLINE_TK},
    }},

  {REAL_TK,
    {
      {regex_t("[0-9.]"), REAL_TK},
      {regex_t("[\n]"), NEWLINE_TK},
    }},
};

struct token {
  state token_state;
  std::string data;
};

#endif
