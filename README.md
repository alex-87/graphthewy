![Graphthewy - Open source header-only graph modelling](https://zupimages.net/up/21/09/ygbc.png "Graphthewy - Open source header-only graph modelling")


About
=====

[![Build Status](https://travis-ci.org/alex-87/graphthewy.svg?branch=master)](https://travis-ci.org/alex-87/graphthewy)

Graphthewy is a header-only C++17 Library to use for :
  - Graph (directed or not) modelling
  - Graph cycle detection

Documentation
-------------

You may find user documentation [in the `docs` directory](https://github.com/alex-87/graphthewy/tree/master/docs)

Requirement
-----------

This software requires :
  - g++ or clang++ supporting C++17
  - [CMake](https://github.com/Kitware/CMake)
  - [CppUTest](https://cpputest.github.io/) *for building tests*


Installation from source
------------------------

From the project basedir, in a terminal :

```
cmake CMakeLists.txt -DGRAPHTHEWY_BUILD_TESTS=OFF
make
sudo make install
```

*Feel free to build tests with `-DGRAPHTHEWY_BUILD_TESTS=ON` after installing [CppUTest](https://cpputest.github.io/)*


Using with Conan
----------------

In your project's `conanfile.txt`, append your `[requires]` section with :

```
graphthewy/1.1@
```


Quick start
-----------


Create an **undirected** graph with a `int`-type label :

```cpp
#include <graphthewy/GraphthewyModel.hpp>

...

graphthewy::UndirectedGraph<int> g{1, 2, 3};
g.addVertex(4); // Add vertex in another way
g << 5; // Add vertex using '<<' operator
g << 6 << 7; // The graph contains vertex {1, 2, 3, 4, 5, 6, 7}
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
