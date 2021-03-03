/**
 * Copyright (C) 2020, 2021 Alexis LE GOADEC.
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
#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(Test_Directed_Int) { };

/*************************************
 * Macro for graph instance
 * ***********************************/
#define GRAPH_TEMPTYPE                   int
#define GRAPH_CREATE(graph_name)         graphthewy::DirectedGraph<GRAPH_TEMPTYPE> graph_name;
#define GRAPH_CYCLE(gc_name, graph_name) graphthewy::GraphCycle<graphthewy::DirectedGraph, GRAPH_TEMPTYPE> gc_name(graph_name);
/*************************************/


TEST(Test_Directed_Int, create) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    CHECK_TRUE(g.getVertex(1) == 1);
}

TEST(Test_Directed_Int, create_heavy) {
    GRAPH_CREATE(g)
    const int limit_node_cr = 10000;
    for(int i=0; i<limit_node_cr; i++) {
        g.addVertex(i);
    };
    CHECK_TRUE(g.getVertex(limit_node_cr - 1) == limit_node_cr - 1);
}

TEST(Test_Directed_Int, link) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.link(1, 2);
    CHECK_TRUE(g.isLinked(1, 2) == true);
    CHECK_TRUE(g.isLinked(2, 1) == false);
}

TEST(Test_Directed_Int, link_heavy) {
    GRAPH_CREATE(g)
    const int limit_node_cr = 10000;
    for(int i=0; i<limit_node_cr; i++) {
        g.addVertex(i);
    }
    for(int i=1; i<limit_node_cr; i++) {
        g.link(i-1, i);
    }
    CHECK_TRUE(g.isLinked(1234, 1235) == true);
    CHECK_TRUE(g.isLinked(1235, 1234) == false);
    CHECK_TRUE(g.isLinked(1234, 1234) == false);
}

TEST(Test_Directed_Int, equals) {

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

    CHECK_TRUE(g.getVertex(1) == h.getVertex(1));
    CHECK_TRUE(g.getVertex(2) == h.getVertex(2));
    CHECK_TRUE(g.getVertex(3) == h.getVertex(3));

    CHECK_TRUE(g.isLinked(1, 2) == h.isLinked(1, 2));
    CHECK_TRUE(g.isLinked(2, 3) == h.isLinked(2, 3));
    CHECK_TRUE(g.isLinked(3, 1) == h.isLinked(3, 1));

}

TEST(Test_Directed_Int, cycle) {

    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.link(1, 2);
    g.link(2, 3);
    g.link(3, 1);

    GRAPH_CYCLE(gc, g)
    CHECK_TRUE(gc.hasCycle() == true);
}

TEST(Test_Directed_Int, no_cycle) {

    GRAPH_CREATE(g)
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.link(1, 2);
    g.link(2, 3);

    GRAPH_CYCLE(gc, g)
    CHECK_TRUE(gc.hasCycle() == false);
}


TEST(Test_Directed_Int, NoDuplicates) {
    GRAPH_CREATE(g)
    g.addVertex(1);
    CHECK_TRUE(g.getVertex(1)==1);
}

TEST(Test_Directed_Int, graphCopy) {
    GRAPH_CREATE(g)
    for(int i=0; i<5; i++) {
        g.addVertex(i);
    }
    g.link(0, 1);

    decltype(g) h(g);

    CHECK_TRUE(g.getVertex(4)==h.getVertex(4));
}

int main(int argc, char** arvg)
{
   return CommandLineTestRunner::RunAllTests(argc, arvg);
}
