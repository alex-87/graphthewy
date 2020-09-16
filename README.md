About
=====

Graphthewy is a header-only C++17 Library to use for :
  - Graph (directed or not) modelling
  - Graph cycle detection

Requirement
-----------

This software requires :
  - C++17
  - [CMake](https://github.com/Kitware/CMake)
  - [Criterion](https://github.com/Snaipe/Criterion) *for building tests*


Installation
------------

From the project basedir, in a terminal :

```
cmake CMakeLists.txt -DGRAPHTHEWY_BUILD_TESTS=OFF
make
sudo make install
```

*Feel free to build tests with `-DGRAPHTHEWY_BUILD_TESTS=ON` after installing [Criterion](https://github.com/Snaipe/Criterion)*


Quick start
-----------


Create an **undirected** graph with a `int`-type label :

```cpp
#include <graphthewy/GraphthewyModel.hpp>

...

graphthewy::UndirectedGraph<int> g{1, 2, 3};
g.link(1, 2);
g.link(2, 3);
g.link(3, 1);
```


Create an **directed** graph with a `std::string`-type label :

```cpp
#include <graphthewy/GraphthewyModel.hpp>

...

graphthewy::DirectedGraph<std::string> g{"a", "b", "c"};
g.link("a", "b");
g.link("b", "c");
g.link("c", "a");
```


Check whether a graph contains a cycle :

```cpp
#include <graphthewy/GraphthewyModel.hpp>
#include <graphthewy/GraphthewyCycle.hpp>

...


graphthewy::DirectedGraph<std::string> g{"a", "b", "c"};
g.link("a", "b");
g.link("b", "c");
g.link("c", "a");

graphthewy::GraphCycle<graphthewy::UndirectedGraph, std::string> gc(g);
std::cout << ( gc.hasCycle() ? "Cycle detected !" : "No cycle detected" ) << std::endl;
```


License
-------

This software is licensed under the [European Union Public License v1.2](https://joinup.ec.europa.eu/sites/default/files/custom-page/attachment/2020-03/EUPL-1.2%20EN.txt)
