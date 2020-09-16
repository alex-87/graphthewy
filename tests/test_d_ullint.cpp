/**
 * Copyright (C) 2020 Alexis LE GOADEC.
 * 
 * This file is part of the Graphthewy project which is licensed under
 * the European Union Public License v1.2.
 * 
 * If a copy of the EUPL v1.2 was not distributed with this software,
 * you can obtain one at : https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#include "../src/include/GraphthewyModel.hpp"
#include "../src/include/GraphthewyCycle.hpp"

#include <string>
#include <criterion/criterion.h>

/*************************************
 * Macro for graph instance
 * ***********************************/
#define GRAPH_TEMPTYPE                   unsigned long long int
#define GRAPH_CREATE(graph_name)         graphthewy::DirectedGraph<GRAPH_TEMPTYPE> graph_name;
#define GRAPH_CYCLE(gc_name, graph_name) graphthewy::GraphCycle<graphthewy::DirectedGraph, GRAPH_TEMPTYPE> gc_name(graph_name);
/*************************************/


Test(Test_Directed_ULLINT, create) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    cr_assert(g.getVertex(1) == 1);
}

Test(Test_Directed_ULLINT, create_heavy) {
    GRAPH_CREATE(g)
    const int limit_node_cr = 10000;
    for(int i=0; i<limit_node_cr; i++) {
        g.addVertex(i);
    };
    cr_assert(g.getVertex(limit_node_cr - 1) == limit_node_cr - 1);
}

Test(Test_Directed_ULLINT, link) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.link(1, 2);
    cr_assert(g.isLinked(1, 2) == true);
    cr_assert(g.isLinked(2, 1) == false);
}

Test(Test_Directed_ULLINT, link_heavy) {
    GRAPH_CREATE(g)
    const int limit_node_cr = 10000;
    for(int i=0; i<limit_node_cr; i++) {
        g.addVertex(i);
    }
    for(int i=1; i<limit_node_cr; i++) {
        g.link(i-1, i);
    }
    cr_assert(g.isLinked(1234, 1235) == true);
    cr_assert(g.isLinked(1235, 1234) == false);
    cr_assert(g.isLinked(1234, 1234) == false);
}

Test(Test_Directed_ULLINT, equals) {

    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.link(1, 2);
    g.link(2, 3);
    g.link(3, 1);

    GRAPH_CREATE(h)
    h.addVertex(1);
    h.addVertex(2);
    h.addVertex(3);
    h.link(1, 2);
    h.link(2, 3);
    h.link(3, 1);

    cr_assert(g.getVertex(1) == h.getVertex(1));
    cr_assert(g.getVertex(2) == h.getVertex(2));
    cr_assert(g.getVertex(3) == h.getVertex(3));

    cr_assert(g.isLinked(1, 2) == h.isLinked(1, 2));
    cr_assert(g.isLinked(2, 3) == h.isLinked(2, 3));
    cr_assert(g.isLinked(3, 1) == h.isLinked(3, 1));

}

Test(Test_Directed_ULLINT, cycle) {

    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.link(1, 2);
    g.link(2, 3);
    g.link(3, 1);

    GRAPH_CYCLE(gc, g)
    cr_assert(gc.hasCycle() == true);
}

Test(Test_Directed_ULLINT, no_cycle) {

    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.link(1, 2);
    g.link(2, 3);

    GRAPH_CYCLE(gc, g)
    cr_assert(gc.hasCycle() == false);
}


Test(Test_Directed_ULLINT, NoDuplicates) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    cr_assert(g.getVertex(1)==1);
}

Test(Test_Directed_ULLINT, graphCopy) {
    GRAPH_CREATE(g)
    for(int i=0; i<5; i++) {
        g.addVertex(i);
    }
    g.link(0, 1);

    decltype(g) h(g);

    cr_assert(g.getVertex(4)==h.getVertex(4));
}
