/**
 * Copyright (C) 2020 Alexis LE GOADEC.
 * 
 * This file is part of the Graphthewy project which is licensed under
 * the European Union Public License v1.2.
 * 
 * If a copy of the EUPL v1.2 was not distributed with this software,
 * you can obtain one at : https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */

#ifndef _GRAPH_MODEL_CYCLE_HPP_
#define _GRAPH_MODEL_CYCLE_HPP_

#include "GraphthewyModel.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include <map>



namespace graphthewy {

/**
 * Helper class for template method selection.
 * 
 * Templates arguments:
 * - G = UndirectedGraph or DirectedGraph
 * - T = the type that G has been templated with
 */
template<template<class> class G, class T>
struct CycleHelper { };

/**
 * Algorithm structure for cycle detection in
 * directed or undirected graph.
 * 
 * Templates arguments:
 * - G = UndirectedGraph or DirectedGraph
 * - T = the type that G has been templated with
 */
template<template<class> class G, class T>
struct GraphCycle {

    /**
     * Contructor
     * 
     * @param graph The graph, directed or undirected
     */
    GraphCycle(const G<T>& graph)
    : graph_(graph) { }

protected:

    /**
     * Depth-first search part of the alrorithm
     * for undirected graph.
     * 
     * @param vertex The current vertex
     * @param visited The visited vertex vector
     * @param previous The previous visited vertex
     * @return true or false
     */
    bool deepfirstseach(
        const std::shared_ptr<Vertex<T>>& vertex,
        std::vector<T>& visited,
        const std::shared_ptr<Vertex<T>>& previous) const {
        visited.push_back(vertex->label_);
        for(const auto& v : vertex->linkVectorPtr_) {
            if(v.lock()!=previous) {
                if(std::find_if(visited.begin(), visited.end(), [&](const auto& x) {return v.lock()->label_==x;})!=visited.end() ) {
                    return true;
                }
                if(deepfirstseach(v.lock(), visited, vertex)) {
                    return true;
                }
            }
        }
        return false;
    };


    /**
     * Cycle detection in an undirected graph.
     * 
     * @return true if cycle is detected, false otherwise.
     */
    bool hasCycleUndirected() const {
        std::vector<T> visited;
        for(const auto& v : graph_.vertexPtrMap_) {
            if(std::find_if(visited.begin(), visited.end(), [&](const auto& x) {return v.first==x;})==visited.end()) {
                if( deepfirstseach(v.second, visited, nullptr) ) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Cycle detection in a directed graph.
     * 
     * @return true if cycle is detected, false otherwise.
     */
    bool hasCycleDirected() const {
        std::map<T, std::vector<std::weak_ptr<Vertex<T>>>> currentMap, newMap;
        for(const auto& e : graph_.vertexPtrMap_) {
            currentMap.insert( std::pair(e.first, e.second->linkVectorPtr_));
        }
        unsigned int sum_r = 0;
        unsigned long long int rollCounter = 0;
        do {
            sum_r = 0;
            newMap.clear();
            for(const auto& e : currentMap) {
                std::vector<std::weak_ptr<Vertex<T>>> u;
                for(const auto& s : e.second) {
                    for(const auto& h : currentMap[s.lock()->label_]) {
                        u.push_back( h );
                    }
                }
                newMap.insert( std::pair(e.first, u) );
            }
            currentMap = newMap;
            for(const auto& e : newMap) {
                sum_r += e.second.size();

                if( contains(e.second, e.first) ) {
                    return true;
                }
            }
            rollCounter++;
            if( rollCounter > newMap.size() ) {
                return true;
            }
        } while( sum_r > 0);
        return false;
    }


public:

    /**
     * Cycle detection in a directed or undirected graph.
     * 
     * @return true if cycle is detected, false otherwise.
     */
    constexpr bool hasCycle() const {
        return CycleHelper<G, T>::hasCycle(this);
    }


protected:

    /**
     * To check whether the specified element's label is contained in the vector.
     * 
     * @param l the vector of elements
     * @param e the element's label
     * @return true or false
     */
    bool contains(const std::vector<std::shared_ptr<Vertex<T>>>& l, const T& e) const {
        for(const auto& v : l) {
            if(v->label_==e) {
                return true;
            }
        }
        return false;
    }

    /**
     * To check whether the specified element's label is contained in the vector.
     * 
     * @param l the vector of elements
     * @param e the element's label
     * @return true or false
     */
    bool contains(const std::vector<std::weak_ptr<Vertex<T>>>& l, const T& e) const {
        for(const auto& v : l) {
            if(v.lock()->label_==e) {
                return true;
            }
        }
        return false;
    }

    /**
     * To check whether the specified element label is contained in the vector.
     * 
     * @param l the vector of elements
     * @param e the element
     * @return true or false
     */
    bool contains(const std::vector<std::shared_ptr<Vertex<T>>>& l, const std::shared_ptr<Vertex<T>>& e) const {
        return contains(l, e->label_);
    }

    /**
     * To check whether the specified element label is contained in the vector.
     * 
     * @param l the vector of elements
     * @param e the element
     * @return true or false
     */
    bool contains(const std::vector<std::weak_ptr<Vertex<T>>>& l, const std::shared_ptr<Vertex<T>>& e) const {
        return contains(l, e->label_);
    }


public:

    /**
     * Friend class with the helper.
     */
    friend class CycleHelper<G, T>;


protected:

    /**
     * The graph.
     */
    const G<T>&
    graph_;

};

template<class T>
struct CycleHelper<UndirectedGraph, T> {
    static inline constexpr bool hasCycle(const GraphCycle<UndirectedGraph, T>* gc) { return gc->hasCycleUndirected(); }
};

template<class T>
struct CycleHelper<DirectedGraph, T> {
    static inline constexpr bool hasCycle(const GraphCycle<DirectedGraph, T>* gc) { return gc->hasCycleDirected(); }
};

}


#endif // _GRAPH_MODEL_CYCLE_HPP_
