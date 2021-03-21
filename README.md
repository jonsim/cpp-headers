
[//]: # (\mainpage cpp-headers Documentation)

# cpp-headers

A collection of my general-purpose C++ classes. This is some way short of a
library, but all the classes contained within are intended to be standalone
and provide recognisable interfaces in keeping with the CSL.

Currently all of these are implemented as pure headers (hence the repository
name) which makes them lighter weight, easier to use and (frankly) easier to
distribute. I may add fully fledged classes at a later point if necessary, but
for now this repository is limited to very simple, robust building blocks
designed to be performant and easier to integrate than a giant library such as
boost.

All headers are written to be compatible with C++11 or newer.



## License

All files are licensed under
[the MIT license](https://github.com/jonsim/cpp-headers/blob/master/LICENSE).

The `src` folder contains all the headers. All the files within may be
distributed individually providing the copyright &amp; license header in each
remains intact.



# Documentation

Full doxygen reference documentation is hosted from the `docs` folder of this
repository at https://jonsim.github.io/cpp-headers/


## Using the headers

The headers can be simply included as normal, e.g.:
```c
#include "circular_buffer.h"
```


## Contributing
The project itself can be built from the repository root as:
```sh
make
```
which builds the documentation and runs the tests. This updates the html files
in the `docs` folder and also outputs `doxygen-output/cpp-headers-reference.pdf`
(which isn't included in the published repository to avoid adding unnecessary
bloat). This requires doxygen &ge; 1.8 and a suitable TeX distribution
installed.

