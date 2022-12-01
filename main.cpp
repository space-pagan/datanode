#include <iostream>
#include "datanode.h"
#include "parser.h"

auto main() -> int {
  datanode config = parser::load("test.txt");
  config.save(std::cout);
  return 0;
}
