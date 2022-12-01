# datanode API
A personal implementation of a configuration file format and parser

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
