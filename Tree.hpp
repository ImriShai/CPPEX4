
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Node.hpp"
#include "Iterators.hpp"

using namespace std;


template <typename T, size_t k = 2>
class Tree
{
private:
    Node<T> *root;
public:
    Tree() : root(nullptr) {}

    void add_root(Node<T> &root)
    {
        if (this->root == nullptr)
        {
            this->root = &root;
        }
        else
        {
            throw std::runtime_error("Root already exists");
        }
    }

    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.childrens.size() < k)
        {
            parent.add_child(child);
        }
        else
        {
            throw std::runtime_error("Parent has already k childrens");
        }
    }

    DFSIterator<T> begin_in_order()
    {
        return DFSIterator<T>(root);
    }
    DFSIterator<T> end_in_order()
    {
        return DFSIterator<T>(nullptr);
    }
    DFSIterator<T> begin_pre_order()
    {
        return DFSIterator<T>(nullptr);
    }
    DFSIterator<T> end_pre_order()
    {
        return DFSIterator<T>(nullptr);
    }
    DFSIterator<T> begin_post_order()
    {
        return DFSIterator<T>(root);
    }
    DFSIterator<T> end_post_order()
    {
        return DFSIterator<T>(nullptr);
    }
    BFSIterator<T> begin_bfs()
    {
        return BFSIterator<T>(root);
    }
    BFSIterator<T> end_bfs()
    {
        return BFSIterator<T>(nullptr);
    }
    DFSIterator<T> begin_dfs()
    {
        return DFSIterator<T>(root);
    }
    DFSIterator<T> end_dfs()
    {
        return DFSIterator<T>(nullptr);
    }
    DFSIterator<T> begin_heap()
    {
        return DFSIterator<T>(root);
    }
    DFSIterator<T> end_heap()
    {
        return DFSIterator<T>(nullptr);
    }
    BFSIterator<T> begin()
    {
        return BFSIterator<T>(root);
    }
    BFSIterator<T> end()
    {
        return BFSIterator<T>(nullptr);
    }

    ~Tree()
    {
        vector<Node<T>*> nodes; // vector to store all nodes
        for (auto it = begin_bfs(); it != end_bfs(); ++it)
        {
            nodes.push_back(it.operator->());
        }
        for( auto it =  nodes.begin(); it != nodes.end(); ++it)
        { // clear all childes from parent
            (*it)->clean();
        }
        root = nullptr; // clear root
    }
    /**
     * @brief Draws the tree on a SFML window.
     *
     * @param window The SFML window to draw the tree on.
     */
     void draw()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            drawTree(window, root, 400, 50, 200, 100, 0);

            window.display();
        }

    }

    private:
    /**
     * @brief Helper function to recursively draw the tree nodes.
     *
     * @param window The SFML window to draw the tree on.
     * @param node The current node to draw.
     * @param x The x-coordinate of the current node.
     * @param y The y-coordinate of the current node.
     * @param xOffset The x-offset for the child nodes.
     * @param yOffset The y-offset for the child nodes.
     * @param level The level of the current node in the tree.
     */

    void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float xOffset, float yOffset, int level)
{
    if (!node)
        return;

    // Draw the node
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y);

    sf::Font font;
    if (!font.loadFromFile("guiResources/RobotoFlex-Regular.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->data));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 10, y + 5);

    // Calculate the positions for the children
    int numChildren = node->childrens.size();
    if (numChildren > 0)
    {
        // Calculate the start position for the first child node
        float startX = x - (xOffset * (numChildren - 1)) / 2.0f;

        for (size_t i = 0; i < numChildren; ++i)
        {
            float childX = startX + i * xOffset;
            float childY = y + yOffset;

            // Draw the connecting line
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + 20, childY + 20), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);

            // Recursively draw the child node
            drawTree(window, node->childrens[i], childX, childY, xOffset / 1.5f, yOffset, level + 1);
        }
    }

    window.draw(circle);
    window.draw(text);
}

    
};

/**
 * @brief A template class representing a Tree data structure.
 *
 * @tparam T The type of data stored in the tree.
 */
template <typename T>
class Tree<T, 2>
{
private:
    Node<T> *root;

public:
    /**
     * @brief Constructs an empty Tree object.
     */
    Tree() : root(nullptr) {}

    /**
     * @brief Adds a root node to the tree.
     *
     * @param root The root node to be added.
     * @throw std::runtime_error if the root already exists.
     */
    void add_root(Node<T> &root)
    {
        if (this->root == nullptr)
        {
            this->root = &root;
        }
        else
        {
            throw std::runtime_error("Root already exists");
        }
    }

    /**
     * @brief Adds a child node to a parent node in the tree.
     *
     * @param parent The parent node.
     * @param child The child node to be added.
     * @throw std::runtime_error if the parent already has 2 children.
     */
    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.childrens.size() < 2)
        {
            parent.add_child(child);
        }
        else
        {
            throw std::runtime_error("Parent has already 2 children");
        }
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in in-order traversal.
     *
     * @return inOrderIterator<T> An iterator pointing to the beginning of the tree.
     */
    inOrderIterator<T> begin_in_order()
    {
        return inOrderIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in in-order traversal.
     *
     * @return inOrderIterator<T> An iterator pointing to the end of the tree.
     */
    inOrderIterator<T> end_in_order()
    {
        return inOrderIterator<T>(nullptr);
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in pre-order traversal.
     *
     * @return preOrderIterator<T> An iterator pointing to the beginning of the tree.
     */
    preOrderIterator<T> begin_pre_order()
    {
        return preOrderIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in pre-order traversal.
     *
     * @return preOrderIterator<T> An iterator pointing to the end of the tree.
     */
    preOrderIterator<T> end_pre_order()
    {
        return preOrderIterator<T>(nullptr);
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in post-order traversal.
     *
     * @return postOrderIterator<T> An iterator pointing to the beginning of the tree.
     */
    postOrderIterator<T> begin_post_order()
    {
        return postOrderIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in post-order traversal.
     *
     * @return postOrderIterator<T> An iterator pointing to the end of the tree.
     */
    postOrderIterator<T> end_post_order()
    {
        return postOrderIterator<T>(nullptr);
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in breadth-first search traversal.
     *
     * @return BFSIterator<T> An iterator pointing to the beginning of the tree.
     */
    BFSIterator<T> begin_bfs()
    {
        return BFSIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in breadth-first search traversal.
     *
     * @return BFSIterator<T> An iterator pointing to the end of the tree.
     */
    BFSIterator<T> end_bfs()
    {
        return BFSIterator<T>(nullptr);
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in depth-first search traversal.
     *
     * @return DFSIterator<T> An iterator pointing to the beginning of the tree.
     */
    DFSIterator<T> begin_dfs()
    {
        return DFSIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in depth-first search traversal.
     *
     * @return DFSIterator<T> An iterator pointing to the end of the tree.
     */
    DFSIterator<T> end_dfs()
    {
        return DFSIterator<T>(nullptr);
    }

    /**
     * @brief Returns an iterator pointing to the beginning of the tree in heap traversal.
     *
     * @return heapIterator<T> An iterator pointing to the beginning of the tree.
     */
    heapIterator<T> begin_heap()
    {
        return heapIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in heap traversal.
     *
     * @return heapIterator<T> An iterator pointing to the end of the tree.
     */
    heapIterator<T> end_heap()
    {
        return heapIterator<T>(nullptr);
    }


    BFSIterator<T> begin()
    {
        return BFSIterator<T>(root);
    }  

    BFSIterator<T> end()
    {
        return BFSIterator<T>(nullptr);
    }




    /**
     * @brief Destroys the Tree object.
     *
     * This function clears all child nodes from the parent nodes and sets the root to nullptr.
     */
    ~Tree()
    {
           vector<Node<T>*> nodes; // vector to store all nodes
        for (auto it = begin_bfs(); it != end_bfs(); ++it)
        {
            nodes.push_back(it.operator->());
        }
        for (auto it : nodes)
        { // clear all childes from parent
            it->clean();
        }
        root = nullptr; // clear root
    }

    /**
     * @brief Draws the tree on a SFML window.
     *
     * @param window The SFML window to draw the tree on.
     */
     void draw()
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            drawTree(window, root, 400, 50, 200, 100, 0);

            window.display();
        }

    }

    private:
    /**
     * @brief Helper function to recursively draw the tree nodes.
     *
     * @param window The SFML window to draw the tree on.
     * @param node The current node to draw.
     * @param x The x-coordinate of the current node.
     * @param y The y-coordinate of the current node.
     * @param xOffset The x-offset for the child nodes.
     * @param yOffset The y-offset for the child nodes.
     * @param level The level of the current node in the tree.
     */

    void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float xOffset, float yOffset, int level)
{
    if (!node)
        return;

    // Draw the node
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y);

    sf::Font font;
    if (!font.loadFromFile("guiResources/RobotoFlex-Regular.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->data));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 10, y + 5);

    // Calculate the positions for the children
    int numChildren = node->childrens.size();
    if (numChildren > 0)
    {
        // Calculate the start position for the first child node
        float startX = x - (xOffset * (numChildren - 1)) / 2.0f;

        for (size_t i = 0; i < numChildren; ++i)
        {
            float childX = startX + i * xOffset;
            float childY = y + yOffset;

            // Draw the connecting line
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + 20, childY + 20), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);

            // Recursively draw the child node
            drawTree(window, node->childrens[i], childX, childY, xOffset / 1.5f, yOffset, level + 1);
        }
    }

    window.draw(circle);
    window.draw(text);
}



    


};