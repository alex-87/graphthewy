/**
 * Copyright (C) 2020, 2021 Alexis LE GOADEC.
 * 
 * This file is part of the Graphthewy project which is licensed under
 * the European Union Public License v1.2.
 * 
 * If a copy of the EUPL v1.2 was not distributed with this software,
 * you can obtain one at : https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
 */


#ifndef _GRAPH_MODEL_HPP_
#define _GRAPH_MODEL_HPP_

#include <initializer_list>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>


namespace graphthewy {

template<typename Tp>
concept equality_comparable = requires(const Tp& t, const Tp& u) {
    { t == u };
    { t != u };
    { u == t };
    { u != t };
};

/**
 * Vertex
 * 
 * Template argument:
 * - T the type of label
 */
template<equality_comparable T>
struct Vertex {

    /**
     * Constructor
     * 
     * @param label The vertex's label
     */
    Vertex(const T& label) : label_(label) { };

    /**
     * Operator
     * 
     * @param o The label to compare
     * @return true if the labels are equals
     */
    bool operator==(const T& o) const { return o==label_; }

    /**
     * Operator
     * 
     * @param o The vertex to compare
     * @return true if the vertexes' labels are equals
     */
    bool operator==(const Vertex<T>& o) const { return o.label_==label_; }

    /**
     * Operator
     * 
     * @param o The pointed vertex to compare
     * @return true if the pointed vertexes' labels are equals
     */
    bool operator==(const std::shared_ptr<Vertex<T>>& o) const { return o->label_==label_; }

    /**
     * Operator
     * 
     * @param o The pointed vertex to compare
     * @return true if the pointed vertexes' labels are equals
     */
    bool operator==(const std::weak_ptr<Vertex<T>>& o) const { return o->label_==label_; }

    /**
     * To check whether the label represents an existing vertex in the
     * linking list of the current vertex.
     * 
     * @param label The label
     * @return true or false
     */
    bool contains(const T& label) const {
        for(const auto& e : linkVectorPtr_) {
            if(e.lock()->label_ == label) {
                return true;
            }
        }
        return false;
    }

    /**
     * To check whether the vertex's label represents an existing vertex in the
     * linking list of the current vertex.
     * 
     * @param label The vertex
     * @return true or false
     */
    bool contains(const Vertex<T>& vertex) const
    { return contains(vertex.label_); }

    /**
     * To check whether the pointed vertex's label represents an existing vertex in the
     * linking list of the current vertex.
     * 
     * @param label The pointed vertex
     * @return true or false
     */
    bool contains(const std::shared_ptr<Vertex<T>>& vertex) const
    { return contains(vertex->label_); }

    /**
     * To create a link between this vertex and the vertex in argument.
     * 
     * In a directed graph, the current vertex recognizes a link between
     * itself and the vertex in argument, but the vertex in argument does
     * NOT recognize a link with the current vertex.
     * 
     * @param vertex The vertex to create a link with.
     */
    void link(const Vertex<T>& vertex)
    { linkVectorPtr_.push_back(std::shared_ptr<Vertex<T>>(vertex)); }

    /**
     * To create a link between this vertex and the pointed vertex in argument.
     * 
     * In a directed graph, the current vertex recognizes a link between
     * itself and the pointed vertex in argument, but the pointed vertex in argument does
     * NOT recognize a link with the current vertex.
     * 
     * @param vertex The pointed vertex to create a link with.
     */
    void link(const std::shared_ptr<Vertex<T>>& vertexPtr) { linkVectorPtr_.push_back(vertexPtr); }

    /**
     * Vertex's label of type T
     */
    const T label_;

    /**
     * List of linked vertexes. The degree of the current vertex is
     * the size of the vector.
     */
    std::vector<std::weak_ptr<Vertex<T>>> linkVectorPtr_;

};


/**
 * Undirected graph.
 * 
 * Template argument:
 * - T = the type of the vertex's label
 */
template<equality_comparable T>
class UndirectedGraph {

public:

    /**
     * Constructor
     */
    UndirectedGraph() { }

    /**
     * Copy constructor
     * 
     * This copy constructor operates a perfect copy, preserving
     * the labels and structures.
     * 
     * @param g The graph to operate a copy from.
     */
    UndirectedGraph(const UndirectedGraph<T>& g) {
        for(const auto& e : g.vertexPtrMap_) {
            vertexPtrMap_.insert(std::pair(e.first, std::shared_ptr<Vertex<T>>(new Vertex<T>(e.first))));
        }
        for(const auto& q : g.vertexPtrMap_) {
            for(const auto& p : q.second->linkVectorPtr_) {
                if(g.isLinked(p.lock()->label_, q.first)) {
                    link(p.lock()->label_, q.first);
                }
            }
        }
    }

    /**
     * Constructor
     * 
     * @param vertexLabelList List of the vertex
     */
    UndirectedGraph(const std::initializer_list<Vertex<T>>& vertexList) : vertexPtrMap_(vertexList) { }

    /**
     * Constructor
     * 
     * @param vertexLabelList List of the vertex labels
     */
    UndirectedGraph(const std::initializer_list<T>& vertexLabelList) {
        for(auto& e : vertexLabelList) {
            vertexPtrMap_.insert(std::pair(e, std::shared_ptr<Vertex<T>>(new Vertex<T>(e))) );
        }
    }

    /**
     * To add a newly created vertex in the current graph, with the
     * specified label.
     * 
     * @param label The new vertex's label to create the new vertex with
     */
    void addVertex(const T& label)
    { vertexPtrMap_.insert(std::pair(label, std::shared_ptr<Vertex<T>>(new Vertex<T>(label)))); }

    /**
     * To add a vertex in the current graph.
     * 
     * @param vertex The vertex to add
     */
    void addVertex(const Vertex<T>& vertex)
    { vertexPtrMap_.emplace( std::pair(vertex.label_, std::shared_ptr<Vertex<T>>(vertex))); }

    /**
     * To check whether the vertex's represents a vertex in the vertex registry
     * of the current graph.
     * 
     * @param label The vertex's label
     * @return true or false
     */
    bool contains(const T& label) const { return vertexPtrMap_.find(label)!=vertexPtrMap_.end(); }

    /**
     * To check whether the vertex is contained in the vertex registry
     * of the current graph.
     * 
     * @param vertex The vertex
     * @return true or false
     */
    bool contains(const Vertex<T>& vertex) const { return contains(vertex.label_); }

    /**
     * To check whether the pointed vertex is contained in the vertex registry
     * of the current graph.
     * 
     * @param vertex A pointer to the vertex
     * @return true or false
     */
    bool contains(const std::shared_ptr<Vertex<T>>& vertex) const { return contains(vertex->label_); }

    /**
     * Get the corresponding vertex by label.
     * 
     * @param label the vertex's label
     * @return the vertex
     */
    const Vertex<T>& getVertex(const T& label) { return *(vertexPtrMap_.at(label)); }

    /**
     * Create a link between vertex e1 and e2.
     * 
     * @param e1 the vertex's label
     * @param e2 the vertex's label
     */
    void link(const T& e1, const T& e2) {
        if( contains(e1) && contains(e2) ) {
            vertexPtrMap_.at(e1)->link(vertexPtrMap_.at(e2));
            vertexPtrMap_.at(e2)->link(vertexPtrMap_.at(e1));
        }
    }

    /**
     * Check whether there is a link between vertex e1 and e2,
     * by label.
     * 
     * @param e1 the vertex's label
     * @param e2 the vertex's label
     * @return true or false
     */
    bool isLinked(const T& e1, const T& e2) const {
        if( !contains(e1) || !contains(e2) ) {
            return false;
        }
        if( vertexPtrMap_.at(e1)->contains(e2) && vertexPtrMap_.at(e2)->contains(e1) ) {
            return true;
        }
        return false;
    }

    /**
     * Check whether there is a link between vertex e1 and e2
     * 
     * @param e1 the vertex
     * @param e2 the vertex
     * @return true or false
     */
    bool isLinked(const Vertex<T>& e1, const Vertex<T>& e2) const {
        return isLinked(e1->label_, e2->label_);
    }

    /**
     * Get edge list (list of label pairs). In case of undirected graph,
     * there will be two edge per linked vertex ((a, b), (b, a))
     * 
     * @return vector of pairs of label corresponding to edge
     */
    std::vector<std::pair<T, T>> getEdgePairList() const {
        std::vector<std::pair<T, T>> edgePairList;
        for(const auto& e : vertexPtrMap_) {
            for(const auto& h : e.second->linkVectorPtr_) {
                edgePairList.push_back( std::make_pair(e.second->label_, h.lock()->label_) );
            }
        }
        return edgePairList;
    }


public:

    /**
     * Operator <<
     * 
     * To add a vertex if not exists. if exists, noop.
     * 
     * @param e vertex label
     * @return graph instance
     */
    UndirectedGraph<T>& operator <<(const T& e) {
        if( !contains(e) ) {
            addVertex(e);
        }
        return *this;
    }

    /**
     * Operator <<
     * 
     * To add a vertex if not exists. if exists, noop.
     * 
     * @param e vertex
     * @return graph instance
     */
    UndirectedGraph<T>& operator <<(const Vertex<T>& e) {
        if( !contains(e) ) {
            addVertex(e);
        }
        return *this;
    }


public:

    /**
     * Order of the graph (number of vertices)
     * 
     * @return the order of the graph
     */
    std::size_t order() const
    { return vertexPtrMap_.size(); }

    /**
     * Size of the graph (number of edges)
     * 
     * @return the number of edges
     */
    std::size_t size() const {
        return getEdgePairList().size() / 2;
    }


public:

    /**
     * Map label to vertex.
     */
    std::map<T, std::shared_ptr<Vertex<T>>>
    vertexPtrMap_;

};


/**
 * Directed graph.
 * 
 * Template argument:
 * - T = the type of the vertex's label
 */
template<equality_comparable T>
class DirectedGraph : public UndirectedGraph<T> {

public:

    using UndirectedGraph<T>::vertexPtrMap_;
    using UndirectedGraph<T>::contains;
    using UndirectedGraph<T>::getEdgePairList;


public:

    /**
     * Constructor
     */
    DirectedGraph() : UndirectedGraph<T>() {}

    /**
     * Copy constructor
     * 
     * This copy constructor operates a perfect copy, preserving
     * the labels and structures.
     * 
     * @param g The graph to operate a copy from.
     */
    DirectedGraph(const DirectedGraph<T>& g) : UndirectedGraph<T>() {
        for(const auto& e : g.vertexPtrMap_) {
            vertexPtrMap_.insert(std::pair(e.first, std::shared_ptr<Vertex<T>>(new Vertex<T>(e.first))));
        }
        for(const auto& q : g.vertexPtrMap_) {
            for(const auto& p : q.second->linkVectorPtr_) {
                if(g.isLinked(q.first, p.lock()->label_)) {
                    link(q.first, p.lock()->label_);
                }
            }
        }
    }

    /**
     * Constructor
     * 
     * @param vertexLabelList List of the vertex
     */
    DirectedGraph(const std::initializer_list<Vertex<T>>& vertexList) : UndirectedGraph<T>(vertexList) { }

    /**
     * Constructor
     * 
     * @param vertexLabelList List of the vertex labels
     */
    DirectedGraph(const std::initializer_list<T>& vertexLabelList) : UndirectedGraph<T>(vertexLabelList) { }

    /**
     * Create a link between vertex e1 and e2, in the e1 -> e2 way.
     * 
     * @param e1 the main vertex's label
     * @param e2 the second vertex's label
     */
    void link(const T& e1, const T& e2) {
        if( contains(e1) && contains(e2) ) {
            vertexPtrMap_.at(e1)->link(vertexPtrMap_.at(e2));
        }
    }

    /**
     * Check whether there is a link between vertex e1 and e2
     * in the e1 -> e2 way.
     * 
     * @param e1 the main vertex
     * @param e2 the second vertex
     * @return true or false
     */
    bool isLinked(const T& e1, const T& e2) const {
        if( !contains(e1) || !contains(e2) ) {
            return false;
        }
        if( vertexPtrMap_.at(e1)->contains(e2) ) {
            return true;
        }
        return false;
    }

    /**
     * Size of the graph (number of edges)
     * 
     * @return the number of edges
     */
    std::size_t size() const {
        return getEdgePairList().size();
    }

};

}


#endif // _GRAPH_MODEL_HPP_
