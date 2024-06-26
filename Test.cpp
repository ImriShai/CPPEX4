#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include "Complex.hpp"
using namespace std;
class Complex;
/**
 * @brief Test cases for the Tree and Iterators classes
*/

using namespace std;

TEST_CASE("Tree Insertion and Traversal for binary tree of integers") {
    Node<int> root(10);
    Node<int> child1(5);
    Node<int> child2(15);
    Node<int> child3(3);
    Node<int> child4(7);
    Node<int> child5(12);
    Node<int> child6(17);
    Tree<int> tree;
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);
    tree.add_sub_node(child2, child6);

    

    SUBCASE("In-order Traversal") {
        vector<int> expected = {3, 5, 7, 10, 12, 15, 17};
        vector<int> actual;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Pre-order Traversal") {
        vector<int> expected = {10, 5, 3, 7, 15, 12, 17};
        vector<int> actual;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Post-order Traversal") {
        vector<int> expected = {3, 7, 5, 12, 17, 15, 10};
        vector<int> actual;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<int> expected = {10, 5, 15, 3, 7, 12, 17};
        vector<int> actual;
        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<int> expected = {10, 5, 3, 7, 15, 12, 17};
        vector<int> actual;
        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("MIN Heap iterator"){
        vector<int> expected = {3, 5, 12, 10, 7, 15, 17};
        vector<int> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Tree Drawing") {
        tree.draw();
    }

}

TEST_CASE("Tree Insertion and Traversal for binary tree of Complex "){
    Node<Complex> root(Complex(10, 10));
    Node<Complex> child1(Complex(5, 5));
    Node<Complex> child2(Complex(15, 15));
    Node<Complex> child3(Complex(3, 3));
    Node<Complex> child4(Complex(7, 7));
    Node<Complex> child5(Complex(12, 12));
    Tree<Complex> tree;
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);

    SUBCASE("In-order Traversal") {
        vector<Complex> expected = {Complex(3, 3), Complex(5, 5), Complex(7, 7), Complex(10, 10), Complex(12, 12), Complex(15, 15)};
        vector<Complex> actual;
        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Pre-order Traversal") {
        vector<Complex> expected = {Complex(10, 10), Complex(5, 5), Complex(3, 3), Complex(7, 7), Complex(15, 15), Complex(12, 12)};
        vector<Complex> actual;
        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Post-order Traversal") {
        vector<Complex> expected = {Complex(3, 3), Complex(7, 7), Complex(5, 5), Complex(12, 12), Complex(15, 15), Complex(10, 10)};
        vector<Complex> actual;
        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("BFS Traversal") {
        vector<Complex> expected = {Complex(10, 10), Complex(5, 5), Complex(15, 15), Complex(3, 3), Complex(7, 7), Complex(12, 12)};
        vector<Complex> actual;
        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("DFS Traversal") {
        vector<Complex> expected = {Complex(10, 10), Complex(5, 5), Complex(3, 3), Complex(7, 7), Complex(15, 15), Complex(12, 12)};
        vector<Complex> actual;
        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("MIN Heap iterator"){
        vector<Complex> expected = {Complex(3, 3), Complex(5, 5), Complex(12, 12), Complex(10, 10), Complex(7, 7), Complex(15, 15)};
        vector<Complex> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Tree Drawing") {
        tree.draw();
    }
}

TEST_CASE("Tree Insertion and Traversal for 4-ary tree of integers") {
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Node<int> child6(7);
    Node<int> child7(8);
    Node<int> child8(9);
    Node<int> child9(10);
    Tree<int, 4> four_ary_tree;
    four_ary_tree.add_root(root);
    four_ary_tree.add_sub_node(root, child1);
    four_ary_tree.add_sub_node(root, child2);
    four_ary_tree.add_sub_node(root, child3);
    four_ary_tree.add_sub_node(child1, child4);
    four_ary_tree.add_sub_node(child2, child5);
    four_ary_tree.add_sub_node(child2, child6);
    four_ary_tree.add_sub_node(child2, child7);
    four_ary_tree.add_sub_node(child2, child8);
    four_ary_tree.add_sub_node(child3, child9);

    SUBCASE("DFS Traversal") {
        vector<int> expected = {1, 2, 5, 3, 6, 7, 8,9,4,10};
        vector<int> actual;
        for (auto it = four_ary_tree.begin_dfs(); it != four_ary_tree.end_dfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("BFS Traversal") {
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        vector<int> actual;
        for (auto it = four_ary_tree.begin_bfs(); it != four_ary_tree.end_bfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("MIN Heap iterator(should be as DFS)"){
        vector<int> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<int> actual;
        for (auto it = four_ary_tree.make_heap_begin(); it != four_ary_tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("In Order Traversal(should be as DFS)"){
         vector<int> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<int> actual;
        for (auto it = four_ary_tree.begin_in_order(); it != four_ary_tree.end_in_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
        
    }
    SUBCASE("Pre Order Traversal(should be as DFS)"){
        vector<int> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<int> actual;
        for (auto it = four_ary_tree.begin_pre_order(); it != four_ary_tree.end_pre_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Post Order Traversal(should be as DFS)"){
        vector<int> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<int> actual;
        for (auto it = four_ary_tree.begin_post_order(); it != four_ary_tree.end_post_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Tree Drawing") {
        four_ary_tree.draw();
    }
}

TEST_CASE("Tree Insertion and Traversal for 4-ary tree of Complex"){
    Node<Complex> root(Complex(1.1, 1.1));
    Node<Complex> n1(Complex(2.2, 2.2));
    Node<Complex> n2(Complex(3.3, 3.3));
    Node<Complex> n3(Complex(4.4, 4.4));
    Node<Complex> n4(Complex(5.5, 5.5));
    Node<Complex> n5(Complex(6.6, -6.6));
    Node<Complex> n6(Complex(-7.7, 7.7));
    Node<Complex> n7(Complex(8.8, 8.8));
    Node<Complex> n8(Complex(9.9, 9.9));
    Node<Complex> n9(Complex(10.10, 10.10));
    Tree<Complex, 4> four_ary_tree; // 4-ary tree.
    four_ary_tree.add_root(root);
    four_ary_tree.add_sub_node(root, n1);
    four_ary_tree.add_sub_node(root, n2);
    four_ary_tree.add_sub_node(root, n3);
    four_ary_tree.add_sub_node(n1, n4);
    four_ary_tree.add_sub_node(n2, n5);
    four_ary_tree.add_sub_node(n2, n6);
    four_ary_tree.add_sub_node(n2, n7);
    four_ary_tree.add_sub_node(n2, n8);
    four_ary_tree.add_sub_node(n3, n9);

    SUBCASE("DFS Traversal") {
        vector<Complex> expected = {Complex(1.1, 1.1), Complex(2.2, 2.2), Complex(5.5, 5.5), Complex(3.3, 3.3), Complex(6.6, -6.6), Complex(-7.7, 7.7), Complex(8.8, 8.8), Complex(9.9, 9.9), Complex(4.4, 4.4), Complex(10.10, 10.10)};
        vector<Complex> actual;
        for (auto it = four_ary_tree.begin_dfs(); it != four_ary_tree.end_dfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
}
    SUBCASE("BFS Traversal") {
        vector<Complex> expected = {Complex(1.1, 1.1), Complex(2.2, 2.2), Complex(3.3, 3.3), Complex(4.4, 4.4), Complex(5.5, 5.5), Complex(6.6, -6.6), Complex(-7.7, 7.7), Complex(8.8, 8.8), Complex(9.9, 9.9), Complex(10.10, 10.10)};
        vector<Complex> actual;
        for (auto it = four_ary_tree.begin_bfs(); it != four_ary_tree.end_bfs(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("MIN Heap iterator(should be as DFS)"){
        vector<Complex> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<Complex> actual;
        for (auto it = four_ary_tree.make_heap_begin(); it != four_ary_tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("In Order Traversal(should be as DFS)"){
         vector<Complex> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<Complex> actual;
        for (auto it = four_ary_tree.begin_in_order(); it != four_ary_tree.end_in_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
        
    }
    SUBCASE("Pre Order Traversal(should be as DFS)"){
        vector<Complex> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<Complex> actual;
        for (auto it = four_ary_tree.begin_pre_order(); it != four_ary_tree.end_pre_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Post Order Traversal(should be as DFS)"){
        vector<Complex> expected;
        for(auto DFS = four_ary_tree.begin_dfs(); DFS != four_ary_tree.end_dfs(); ++DFS){
            expected.push_back(*DFS);
        }
        vector<Complex> actual;
        for (auto it = four_ary_tree.begin_post_order(); it != four_ary_tree.end_post_order(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
    SUBCASE("Tree Drawing") {
        four_ary_tree.draw();
    }
}

TEST_CASE("Test minHEap for binary trees"){
    SUBCASE("Integers"){
    SUBCASE("Tree 1"){
        Node<int> root(-5);
        Node<int> child1(5);
        Node<int> child2(10);
        Node<int> child3(3);
        Node<int> child4(12);
        Node<int> child5(98);
        Node<int> child6(17);
        Tree<int> tree;
        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);
        tree.add_sub_node(child1, child3);
        tree.add_sub_node(child1, child4);
        tree.add_sub_node(child2, child5);
        tree.add_sub_node(child2, child6);
        vector<int> expected = {-5, 3, 10, 5, 12, 98, 17};
        vector<int> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }

    SUBCASE("Tree 2"){
        Node<int> root(10);
        Node<int> child1(5);
        Node<int> child2(15);
        Node<int> child3(3);
        Node<int> child4(7);
        Node<int> child5(12);
        Node<int> child6(17);
        Node<int> child7(-20);
        Tree<int> tree;
        tree.add_root(root);
        tree.add_sub_node(root, child4);
        tree.add_sub_node(root, child5);
        tree.add_sub_node(child4, child1);
        tree.add_sub_node(child4, child2);
        tree.add_sub_node(child5, child3);
        tree.add_sub_node(child5, child6);
        tree.add_sub_node(child6, child7);
        vector<int> expected = {-20, 5, 3, 7, 15, 12, 17, 10};
        vector<int> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
        Node<int> heap_root = expected[0];
        Node<int> left_child = expected[1];
        Node<int> right_child = expected[2];
        Node<int> left_child_left_child = expected[3];
        Node<int> left_child_right_child = expected[4];
        Node<int> right_child_left_child = expected[5];
        Node<int> right_child_right_child = expected[6];
        Node<int> left_child_left_child_left_child = expected[7];
        Tree<int> heap_tree;
        heap_tree.add_root(heap_root);
        heap_tree.add_sub_node(heap_root, left_child);
        heap_tree.add_sub_node(heap_root, right_child);
        heap_tree.add_sub_node(left_child, left_child_left_child);
        heap_tree.add_sub_node(left_child, left_child_right_child);
        heap_tree.add_sub_node(right_child, right_child_left_child);
        heap_tree.add_sub_node(right_child, right_child_right_child);
        heap_tree.add_sub_node(left_child_left_child, left_child_left_child_left_child);
        heap_tree.draw();

    }
}

SUBCASE("Complex"){
    SUBCASE("Tree 1"){
        Node<Complex> root(Complex(0,0));
        Node<Complex> child1(Complex(5,5));
        Node<Complex> child2(Complex(10,10));
        Node<Complex> child3(Complex(3,3));
        Node<Complex> child4(Complex(12,12));
        Node<Complex> child5(Complex(98,98));
        Node<Complex> child6(Complex(17,17));
        Tree<Complex> tree;
        tree.add_root(root);
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);
        tree.add_sub_node(child1, child3);
        tree.add_sub_node(child1, child4);
        tree.add_sub_node(child2, child5);
        tree.add_sub_node(child2, child6);
        vector<Complex> expected = {Complex(0, 0), Complex(3, 3), Complex(10, 10), Complex(5, 5), Complex(12, 12), Complex(98, 98), Complex(17, 17)};
        vector<Complex> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
        Node<Complex> heap_root = expected[0];
        Node<Complex> left_child = expected[1];
        Node<Complex> right_child = expected[2];
        Node<Complex> left_child_left_child = expected[3];
        Node<Complex> left_child_right_child = expected[4];
        Node<Complex> right_child_left_child = expected[5];
        Node<Complex> right_child_right_child = expected[6];
        Tree<Complex> heap_tree;
        heap_tree.add_root(heap_root);
        heap_tree.add_sub_node(heap_root, left_child);
        heap_tree.add_sub_node(heap_root, right_child);
        heap_tree.add_sub_node(left_child, left_child_left_child);
        heap_tree.add_sub_node(left_child, left_child_right_child);
        heap_tree.add_sub_node(right_child, right_child_left_child);
        heap_tree.add_sub_node(right_child, right_child_right_child);
        heap_tree.draw();
    }

    SUBCASE("Tree 2"){
        Node<Complex> root(Complex(10, 10));
        Node<Complex> child1(Complex(5, 5));
        Node<Complex> child2(Complex(15, 15));
        Node<Complex> child3(Complex(3, 3));
        Node<Complex> child4(Complex(7, 7));
        Node<Complex> child5(Complex(12, 12));
        Node<Complex> child6(Complex(17, 17));
        Node<Complex> child7(Complex(0, 0));
        Tree<Complex> tree;
        tree.add_root(root);
        tree.add_sub_node(root, child4);
        tree.add_sub_node(root, child5);
        tree.add_sub_node(child4, child1);
        tree.add_sub_node(child4, child2);
        tree.add_sub_node(child5, child3);
        tree.add_sub_node(child5, child6);
        tree.add_sub_node(child6, child7);
        vector<Complex> expected = {Complex(0, 0), Complex(5, 5), Complex(3, 3), Complex(7, 7), Complex(15, 15), Complex(12, 12), Complex(17, 17), Complex(10, 10)};
        vector<Complex> actual;
        for (auto it = tree.make_heap_begin(); it != tree.make_heap_end(); ++it) {
            actual.push_back(*it);
        }
        CHECK(actual == expected);
    }
}
}

   
