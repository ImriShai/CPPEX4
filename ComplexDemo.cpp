#include "Tree.hpp"
#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include "Complex.hpp"
using namespace std;
int main()
{

    Node<Complex> root(Complex(1.0, 1.0));
    Node<Complex> child1(Complex(2.0, 2.0));
    Node<Complex> child2(Complex(3.0, 3.0));
    Node<Complex> child3(Complex(4.0, 4.4));
    Node<Complex> child4(Complex(5.0, -5.5));
    Node<Complex> child5(Complex(6.0, 6.6));
    Tree<Complex> tree;
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
    cout << endl;


    // Now let's create a 4-ary tree.
    Node<Complex> root_node = Node<Complex>(Complex(1.1, 1.1));
    Node<Complex> n1 = Node<Complex>(Complex(2.2, 2.2));
    Node<Complex> n2 = Node<Complex>(Complex(3.3, 3.3));
    Node<Complex> n3 = Node<Complex>(Complex(4.4, 4.4));
    Node<Complex> n4 = Node<Complex>(Complex(5.5, 5.5));
    Node<Complex> n5 = Node<Complex>(Complex(6.6, -6.6));
    Node<Complex> n6 = Node<Complex>(Complex(-7.7, 7.7));
    Node<Complex> n7 = Node<Complex>(Complex(8.8, 8.8));
    Node<Complex> n8 = Node<Complex>(Complex(9.9, 9.9));
    Node<Complex> n9 = Node<Complex>(Complex(10.10, 10.10));
    Tree<Complex, 4> four_ary_tree; // 4-ary tree.
    four_ary_tree.add_root(root_node);
    four_ary_tree.add_sub_node(root_node, n1);
    four_ary_tree.add_sub_node(root_node, n2);
    four_ary_tree.add_sub_node(root_node, n3);
    four_ary_tree.add_sub_node(n1, n4);
    four_ary_tree.add_sub_node(n2, n5);
    four_ary_tree.add_sub_node(n2, n6);
    four_ary_tree.add_sub_node(n2, n7);
    four_ary_tree.add_sub_node(n2, n8);
    four_ary_tree.add_sub_node(n3, n9);
    four_ary_tree.draw(); // Starting position of the root
    return 0;
}