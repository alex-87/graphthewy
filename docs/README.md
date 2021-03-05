![Graphthewy - Open source header-only graph modelling](https://zupimages.net/up/21/09/ygbc.png "Graphthewy - Open source header-only graph modelling")

# What's inside Graphthewy

The goal of this header-only C++ library is to provide a lightweight feature for graph modelling, in a simple and efficient way of use. There is also an algorithmic feature for cycles detection in directed or undirected graph.

[Graphthewy](https://github.com/alex-87/graphthewy) is Open Source, lisenced under the [European Union Public License v1.2](https://joinup.ec.europa.eu/sites/default/files/custom-page/attachment/2020-03/EUPL-1.2%20EN.txt)

# How to use it

[Download the package here](https://github.com/alex-87/graphthewy/releases/latest), untar-gz, and `cmake CMakeLists.txt -DGRAPHTHEWY_BUILD_TESTS=OFF && make && sudo make install`

Once installation is done, add the following headers in your source :

```cpp
#include <graphthewy/GraphthewyModel.hpp>
#include <graphthewy/GraphthewyCycle.hpp>
```

## How to create a graph

To create a graph with `int`-typed labels, do like following :

```cpp
graphthewy::DirectedGraph<int> g; // For a directed graph
// OR
graphthewy::UndirectedGraph<int> g; // For an undirected graph
```

Any type endowed with the '==' comparator operator can be used to label.

## Add vertex

Starting from our `int`-labeled graph `g`, now let's add vertices in 3 different ways, all equivalent :

##### Way 1

```cpp
graphthewy::Vertex<int> v(1), w(2);
g.addVertex(v);
g.addVertex(w);
```

##### Way 2

```cpp
g.addVertex(1);
g.addVertex(2);
```

##### Way 3

```cpp
g << 1 << 2;
```


## Get a vertex

To get a specific vertex, here the number `2` for example, call :

```cpp
g.getVertex(2);
```

This method will return an object of type :

```cpp
const graphthewy::Vertex<int>&
```

## Edges

To link vertex `1` toward `2`, simply do :

```cpp
g.link(1, 2);
```

In case of undirected graph, the link occurs in `1` toward `2`, and `2` toward `1`.

##### Order and size

To compute the order and the size of the graph :

```cpp
std::cout << g.order() << ", " << g.size() << std::endl; // [Out]: 2, 1
```

##### Edge list

Once linking has been done, to get the edge list, call :

```cpp
std::vector<std::pair<int, int>> edgeList = g.getEdgePairList();
```

## Cycles detection

*A cycle or simple circuit is a circuit in which the only repeated vertex is the first/last vertex.*
*--- Wikipedia*

##### Usage

To detect a cycle in a directed or undirected graph, this library provides the following tool :

```cpp
graphthewy::GraphCycle<graphthewy::DirectedGraph, int> gc(g);
```

The first template parameter is the type of graph (`graphthewy::DirectedGraph` or `graphthewy::UndirectedGraph`), and
the type of label.

The initialization is made by passing as parameter the previous graph `g`.

To detected a cycle, call the following method :

```cpp
gc.hasCycle();
```

This method returns a boolean.
