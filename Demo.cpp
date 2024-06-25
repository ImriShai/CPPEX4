
#include "Tree.hpp"
#include "Node.hpp"
#include <SFML/Graphics.hpp>

int main()
{

    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Tree<int> tree;
    tree.add_root(root);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);

    tree.draw(); // Starting position of the root
    // The tree should look like:
    /**
     *       root = 1
     *     /       \
     *     2       3
     *   /  \      /
     *  4    5    6
     */

    cout<< "PreOrder: ";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2 , 4, 5, 3, 6
    cout << endl << "PostOrder: ";


    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 4, 5, 2, 6, 3, 1
    cout << endl << "InOrder: ";

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_data() << ", ";

    } // prints: 4, 2, 5, 1, 6, 3
    cout << endl << "BFS: ";

    for (auto node = tree.begin_bfs(); node != tree.end_bfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 3, 4, 5, 6
    cout << endl << "DFS: ";

    for (auto node = tree.begin_dfs(); node != tree.end_dfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 4, 5, 3, 6
    cout << endl << "Range-based for loop(BFS): ";

    for (auto node : tree)
    {
        cout << node<< ", ";
    } // same as BFS: 1, 2, 3, 4, 5, 6
    cout << endl << "Heap Iterator: ";
    for (auto node = tree.make_heap_begin(); node != tree.make_heap_end(); ++node)
    {
        cout << node->get_data() << ", ";
    }
    cout << endl;


    // Now let's create a 3-ary tree.
    Node<double> root_node = Node<double>(1.1);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);
    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    three_ary_tree.draw(); // Starting position of the root

     cout<< "PreOrder(DFS): ";
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2 , 4, 5, 3, 6
    cout << endl << "PostOrder(DFS): ";


    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 4, 5, 2, 6, 3, 1
    cout << endl << "InOrder(DFS): ";

    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node->get_data() << ", ";

    } // prints: 4, 2, 5, 1, 6, 3
    cout << endl << "BFS: ";

    for (auto node = three_ary_tree.begin_bfs(); node != three_ary_tree.end_bfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 3, 4, 5, 6
    cout << endl << "DFS: ";

    for (auto node = three_ary_tree.begin_dfs(); node != three_ary_tree.end_dfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 4, 5, 3, 6
    cout << endl << "Range-based for loop(BFS): ";

    for (auto node : three_ary_tree)
    {
        cout << node<< ", ";
    } // same as BFS: 1, 2, 3, 4, 5, 6
    cout << endl << "Heap Iterator(DFS): ";
    for (auto node = three_ary_tree.make_heap_begin(); node != three_ary_tree.make_heap_end(); ++node)
    {
        cout << node->get_data() << ", ";
    }
    cout << endl;

    Node<string> root_str("root");
    Node<string> child1_str("child1");
    Node<string> child2_str("child2");
    Node<string> child3_str("child3");
    Node<string> child4_str("child4");
    Node<string> child5_str("child5");
    Tree<string,3> tree_str;
    tree_str.add_root(root_str);
    tree_str.add_sub_node(root_str, child1_str);
    tree_str.add_sub_node(root_str, child2_str);
    tree_str.add_sub_node(root_str, child3_str);
    tree_str.add_sub_node(child1_str, child4_str);
    tree_str.add_sub_node(child2_str, child5_str);
    tree_str.draw(); // Starting position of the root
     cout<< "PreOrder(DFS): ";
    for (auto node = tree_str.begin_pre_order(); node != tree_str.end_pre_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2 , 4, 5, 3, 6
    cout << endl << "PostOrder(DFS): ";


    for (auto node = tree_str.begin_post_order(); node != tree_str.end_post_order(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 4, 5, 2, 6, 3, 1
    cout << endl << "InOrder(DFS): ";

    for (auto node = tree_str.begin_in_order(); node != tree_str.end_in_order(); ++node)
    {
        cout << node->get_data() << ", ";

    } // prints: 4, 2, 5, 1, 6, 3
    cout << endl << "BFS: ";

    for (auto node = tree_str.begin_bfs(); node != tree_str.end_bfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 3, 4, 5, 6
    cout << endl << "DFS: ";

    for (auto node = tree_str.begin_dfs(); node != tree_str.end_dfs(); ++node)
    {
        cout << node->get_data() << ", ";
    } // prints: 1, 2, 4, 5, 3, 6
    cout << endl << "Range-based for loop(BFS): ";

    for (auto node : tree_str)
    {
        cout << node<< ", ";
    } // same as BFS: 1, 2, 3, 4, 5, 6
    cout << endl << "Heap Iterator(DFS): ";
    for (auto node = tree_str.make_heap_begin(); node != tree_str.make_heap_end(); ++node)
    {
        cout << node->get_data() << ", ";
    } 

    





   

    return 0;
}