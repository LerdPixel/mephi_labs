#pragma once
#include <gtest/gtest.h>
#include <string>
#include "../Graph.h"
#include "../WeightEdge.h"


struct GraphTests : public testing::Test {
    shared_ptr<Graph<std::string, int >> graph;
    void SetUp() {
        int  v = 5; // Number of vertices in
        //ConnectionPoint cp[] = {ConnectionPoint("A"), ConnectionPoint("B"), ConnectionPoint("C")};
        std::string a[] = {"A", "B", "C", "D", "E"};
        auto verts = shared_ptr<Sequence<std::string>>(new ArraySequence<std::string>(a, v));
        graph = shared_ptr<Graph<std::string, int>>(new Graph<std::string, int >(verts));
    }
    void TearDown() {
    }
};

TEST_F(GraphTests, GraphTests_Initialization) {
    ASSERT_TRUE(graph->ContainsVertex("D"));
    ASSERT_FALSE(graph->ContainsVertex("G"));
}
TEST_F(GraphTests, GraphTests_Initialization_2) {
    graph->AddEdge("H", "C", 8);
    ASSERT_TRUE(graph->ContainsVertex("H"));
}
TEST_F(GraphTests, GraphTests_Initialization_3) {
    graph->AddEdge("H", "G", 8);
    ASSERT_TRUE(graph->ContainsVertex("G"));
    ASSERT_TRUE(graph->ContainsVertex("H"));    
    ASSERT_EQ(graph->GetVertices()->GetLength(), 7);
}
TEST_F(GraphTests, GraphTests_Delete_Edge_1) {
    graph->AddEdge("H", "G", 8);
    graph->DeleteEdge("H", "G", 8);
    ASSERT_TRUE(graph->ContainsVertex("G"));
    ASSERT_TRUE(graph->ContainsVertex("H"));    
    ASSERT_EQ(graph->GetVertices()->GetLength(), 7);
}
class dickClass {
    int a;
public:
    dickClass() : a(666) {}
    dickClass(int _a) : a(_a) {}
};
 TEST_F(GraphTests, GraphTests_RandWeight) {
    Graph<std::string, dickClass > graph = Graph<std::string, dickClass >();

    graph.AddEdge("H", "G", dickClass(3));
    ASSERT_TRUE(graph.ContainsVertex("G"));
    ASSERT_TRUE(graph.ContainsVertex("H"));
}/*
TEST_F(GraphTests, GraphTests_CopyConstructor_2) {
    shared_ptr<Graph<std::string, shared_ptr<WeightEdge<std::string>> >> graph2(new Graph<std::string, shared_ptr<WeightEdge<std::string>>>(*graph));
    graph2->AddEdge("H", make_shared<WeightEdge<std::string>>("G", 8));
    ASSERT_FALSE(graph->ContainsVertex("G"));
    ASSERT_FALSE(graph->ContainsVertex("H"));
    graph->AddVertex("X");
    graph->AddEdge("X", make_shared<WeightEdge<std::string>>("A", 8));
    ASSERT_FALSE(graph2->ContainsVertex("X"));
} */