#pragma once
#include <gtest/gtest.h>
#include <string>
#include "../Graph.h"
#include "../WeightEdge.h"


struct GraphTests : public testing::Test {
    shared_ptr<Graph<std::string, shared_ptr<WeightEdge<std::string>> >> graph;
    void SetUp() {
        int  v = 5; // Number of vertices in
        //ConnectionPoint cp[] = {ConnectionPoint("A"), ConnectionPoint("B"), ConnectionPoint("C")};
        std::string a[] = {"A", "B", "C", "D", "E"};
        auto verts = shared_ptr<Sequence<std::string>>(new ArraySequence<std::string>(a, v));
        graph = shared_ptr<Graph<std::string, shared_ptr<WeightEdge<std::string>> >>(new Graph<std::string, shared_ptr<WeightEdge<std::string>> >(verts));
    }
    void TearDown() {
    }
};

TEST_F(GraphTests, GraphTests_Initialization) {
    ASSERT_TRUE(graph->ContainsVertex("D"));
    ASSERT_FALSE(graph->ContainsVertex("G"));
}
TEST_F(GraphTests, GraphTests_Initialization_2) {
    graph->AddEdge("H", make_shared<WeightEdge<std::string>>("C", 8));
    ASSERT_TRUE(graph->ContainsVertex("H"));
}
TEST_F(GraphTests, GraphTests_Initialization_3) {
    graph->AddEdge("H", make_shared<WeightEdge<std::string>>("G", 8));
    ASSERT_TRUE(graph->ContainsVertex("G"));
    ASSERT_TRUE(graph->ContainsVertex("H"));    
    ASSERT_EQ(graph->GetVertices()->GetLength(), 7);
}
TEST_F(GraphTests, GraphTests_Delete_Edge_1) {
    graph->AddEdge("H", make_shared<WeightEdge<std::string>>("G", 8));
    graph->DeleteEdge("H", make_shared<WeightEdge<std::string>>("G", 8));
    ASSERT_TRUE(graph->ContainsVertex("G"));
    ASSERT_TRUE(graph->ContainsVertex("H"));    
    ASSERT_EQ(graph->GetVertices()->GetLength(), 7);
}
