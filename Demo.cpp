
#include "Tree.hpp"
#include "Node.hpp"
#include <SFML/Graphics.hpp>

int main() {
sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Visualization");

    
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);

    Tree<int,3> tree;
    tree.add_root(root);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child1, child5);
    

   

    tree.draw(window); // Starting position of the root
    cout<<typeid(tree.end_bfs()).name()<<endl;
    int i = 0;  
    for(auto child = tree.begin_bfs(); child != tree.end_bfs();++child){
                cout <<i++<<endl;

        cout<< "Child: "<< child->get_data()<<endl;
    }
    cout<< "End of BFS"<<endl;

    return 0;






}