# datanode API
A personal implementation of a configuration file format and parser

## Building
A mock `test.txt` file and `main.cpp` are included for your benefit. This project is not designed
to be stand-alone and benefits most from inclusion in other codebases. Nevertheless, you can build
the mock project with the included Makefile. The following make directives are provided:

- `make clean`: removes an existing `./build/` directory and all of its contents
- `make all` / `make`: creates the build directory and compiles to `datanode` / `datanode.exe`

## Usage
### Inclusion
```c++
#include "datanode.h"
#include "parser.h"
```

### Creation
A datanode is a recursive node object which can either contain a `std::variant<std::string, int, double>` or another datanode

The following c++ code will create a datanode structure equivilent to that seen in `test.txt`:

```c++
datanode d;
d["config_node"]["some_field"] = "value";
d["config_node"]["some_field2"] = 2;
d["other_config_node"]["other_field"] = 3.14;
d["other_config_node"]["other_subconfig"]["sub_field"] = "2";
```

Note the use of the overridden operator[] which will either access a sub-datanode by name if it exists, or create one if it does not.

### Saving
```c++
// save to file
d.save("file/location/here");
// or save to other ostream object
d.save(std::cout);
```

### Loading
```c++
// load from file
datanode d = parser::load("file/location/here");
// or load from other istream object
d = parser::load(std::cin);
```
#### Parser notes
- Ignores horizontal whitespace unless enclosed in double quotes, e.g. a field containing a string value such as `sub_field = "2"`
- Does NOT ignore vertical whitespace. Newlines are syntactically important!
- If a parse error is encountered, a `parse_exception` will be thrown.
