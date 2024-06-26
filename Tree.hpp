
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Node.hpp"
#include "Iterators.hpp"

using namespace std;

/**
 * @brief A template class representing a Tree data structure.
 *
 * @tparam T The type of data stored in the tree.
 * @tparam k The maximum number of children each node can have. Default is 2.
 */
template <typename T, size_t k = 2>
class Tree
{
private:
    Node<T> *root;

public:
    Tree() : root(nullptr) {} // Constructor, initializes the root to nullptr

/**
 * @brief Adds a root node to the tree.
 * @param root The root node to be added.
 * @throw std::runtime_error if the root already exists.
 */
    void add_root(Node<T> &root)
    {
        if (this->root == nullptr) // If the root is empty, set the root to the given root
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
 * @param parent The parent node.
 * @param child The child node to be added.
 * @throw std::runtime_error if the parent already has k children.
 */
    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        if (parent.childrens.size() < k) // If the parent has less than k children, add the child to the parent
        {
            parent.add_child(child);
        }
        else
        {
            throw std::runtime_error("Parent has already k childrens"); // If the parent has k children, throw an error
        }
    }
// Iterator functions, as required by the assignment, if the tree has k!=2 children all binary tree iterators will be DFS iterators
// For each iterator, the begin function returns an iterator pointing to the beginning of the tree, and the end function returns an iterator pointing to the end of the tree.
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
        return DFSIterator<T>(root);
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
    DFSIterator<T> make_heap_begin()
    {
        return DFSIterator<T>(root);
    }
    DFSIterator<T> make_heap_end()
    {
        return DFSIterator<T>(nullptr);
    }

/**
 * @brief Destroys the Tree object.
 * This function clears all child nodes from the parent nodes and sets the root to nullptr.
 * This function is called when the Tree object goes out of scope.
 */
    ~Tree()
    {
        vector<Node<T> *> nodes; // vector to store all nodes
        for (auto it = begin_bfs(); it != end_bfs(); ++it)
        {
            nodes.push_back(it.operator->());
        }
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
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
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization"); // Create a window
        while (window.isOpen()) // While the window is open
        {
            sf::Event event; // Create an event
            while (window.pollEvent(event)) // While there are events to process
            {
                if (event.type == sf::Event::Closed) // If the event is a close event, close the window
                    window.close();
            }

            window.clear(sf::Color::White); // Clear the window, set the background color to white

            drawTree(window, root, 400, 50, 150, 100, 0); //calls the drawTree function to draw the tree

            window.display(); // Display the window
        }
    }

private:
   
    // Helper function to format numbers with a specific precision
    std::string formatData(const T &data, int precision = 5)
    {
        std::stringstream ss; // Create a stringstream
        ss << std::fixed << std::setprecision(precision) << data; // Set the precision of the stringstream
        return ss.str(); // Return the string
    }

    // Helper function to truncate text and add ellipsis if necessary
    std::string truncateText(const sf::Text &text, float maxWidth)
    {
        std::string str = text.getString(); // Get the string from the text
        std::string truncatedStr = str; // Set the truncated string to the original string
        sf::Text tempText = text; // Create a temporary text object

        // Check if the text width exceeds the maximum allowed width
        if (text.getLocalBounds().width > maxWidth)
        {
            // Find the maximum length that fits within the width
            for (size_t i = 0; i < str.size(); ++i)
            {
                truncatedStr = str.substr(0, i) + "..."; // Add ellipsis to the string
                tempText.setString(truncatedStr); // Set the string of the temporary text object

                if (tempText.getLocalBounds().width > maxWidth) //if the text is too long, truncate it
                {
                    truncatedStr = str.substr(0, i - 1) + "...";
                    break;
                }
            }
        }
        return truncatedStr;
    }

    /**
     * @brief Helper function to calculate the max width of a subtree. this function is used to prevent overlapping of nodes in the tree visualization.
     * @param node The root node of the subtree.
     * @param xOffset The x-offset for the child nodes.
     * @return the maximum width of the subtree as a float.
     */
float calculateSubtreeWidth(Node<T> *node, float xOffset)
{
    if (!node || node->childrens.empty())
        return 0.0f;

    // Sum the widths of all children subtrees
    float totalWidth = 0.0f;
    for (auto &child : node->childrens)
    {
        totalWidth += calculateSubtreeWidth(child, xOffset) + xOffset;
    }

    // The total width should be adjusted by removing the extra xOffset added to the last child
    totalWidth -= (2 * xOffset)  ;

    // Ensure at least a minimum width for a single child
    return std::max(totalWidth, xOffset);
}

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
    sf::CircleShape circle(30);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("guiResources/RobotoFlex-Regular.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }

    // Format the node data for display with a precision of 5
    std::string nodeDataStr = formatData(node->data);

    // Create the text for the node data
    sf::Text text;
    text.setFont(font);
    text.setString(nodeDataStr);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);

    // Initial centering of text based on its original content
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // Calculate the circle's center
    float circleCenterX = x + circle.getRadius();
    float circleCenterY = y + circle.getRadius();

    // Set the initial position of the text to the circle's center
    text.setPosition(circleCenterX, circleCenterY);

    // Truncate the text if it doesn't fit within the circle
    float maxTextWidth = circle.getRadius() * 2.0f - 10.0f; // Circle diameter minus padding
    std::string truncatedTextStr = truncateText(text, maxTextWidth);
    text.setString(truncatedTextStr);

    // Re-calculate the origin after setting the truncated text to ensure it's centered
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // Adjust the position again to ensure the truncated text is centered within the circle
    text.setPosition(circleCenterX, circleCenterY);

    // Draw the circle and text
    window.draw(circle);
    window.draw(text);

    // Calculate the positions for the children
    int numChildren = node->childrens.size();
    if (numChildren > 0)
    {
        // Calculate the width needed for the current node's subtree
        float subtreeWidth = calculateSubtreeWidth(node, xOffset);

        // Calculate the start position for the first child node
        float startX = x + circle.getRadius() - subtreeWidth / 2.0f;

        for (size_t i = 0; i < numChildren; ++i)
        {
            float childX = startX + i * (subtreeWidth / numChildren);
            float childY = y + yOffset;

            // Draw the connecting line
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(circleCenterX, circleCenterY), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY + circle.getRadius()), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);

            // Recursively draw the child node
            drawTree(window, node->childrens[i], childX, childY, xOffset / 1.2f, yOffset, level + 1);
        }
    }

    // Check if the mouse is hovering over the circle
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (circle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        // Create and position the tooltip box
        sf::RectangleShape tooltip(sf::Vector2f(200, 50));
        tooltip.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(1);
        tooltip.setPosition(static_cast<float>(mousePos.x) + 10, static_cast<float>(mousePos.y) - 60);

        // Create and position the tooltip text
        sf::Text tooltipText;
        tooltipText.setFont(font);
        tooltipText.setString(nodeDataStr); // Full untruncated text
        tooltipText.setCharacterSize(15);
        tooltipText.setFillColor(sf::Color::Black);
        tooltipText.setPosition(tooltip.getPosition().x + 10, tooltip.getPosition().y + 10);

        // Draw the tooltip box and text
        window.draw(tooltip);
        window.draw(tooltipText);
    }
}
};









/**
 * @brief A template class representing a Tree data structure. This specialization is for a binary tree.
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
    heapIterator<T> make_heap_begin()
    {
        return heapIterator<T>(root);
    }

    /**
     * @brief Returns an iterator pointing to the end of the tree in heap traversal.
     *
     * @return heapIterator<T> An iterator pointing to the end of the tree.
     */
    heapIterator<T> make_heap_end()
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
        vector<Node<T> *> nodes; // vector to store all nodes
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
   // Helper function to format numbers with a specific precision
    std::string formatData(const T &data, int precision = 5)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision) << data;
        return ss.str();
    }

    // Helper function to truncate text and add ellipsis if necessary
    std::string truncateText(const sf::Text &text, float maxWidth)
    {
        std::string str = text.getString();
        std::string truncatedStr = str;
        sf::Text tempText = text;

        // Check if the text width exceeds the maximum allowed width
        if (text.getLocalBounds().width > maxWidth)
        {
            // Find the maximum length that fits within the width
            for (size_t i = 0; i < str.size(); ++i)
            {
                truncatedStr = str.substr(0, i) + "...";
                tempText.setString(truncatedStr);

                if (tempText.getLocalBounds().width > maxWidth)
                {
                    truncatedStr = str.substr(0, i - 1) + "...";
                    break;
                }
            }
        }
        return truncatedStr;
    }

//Notice that the function calculateSubtreeWidth is not defined in this specialization, as it is only used in the general case of the Tree class.
//In binary tree no overlapping of nodes is possible, so we don't need to calculate the width of the subtree.


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
        sf::CircleShape circle(30);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x, y);

        // Load the font
        sf::Font font;
        if (!font.loadFromFile("guiResources/RobotoFlex-Regular.ttf"))
        {
            std::cerr << "Failed to load font\n";
            return;
        }

        // Format the node data for display
        std::string nodeDataStr = formatData(node->data);

        // // Create the text for the node data

        sf::Text text;
        text.setFont(font);
        text.setString(nodeDataStr);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);

        // Initial centering of text based on its original content
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        // Calculate the circle's center
        float circleCenterX = x + circle.getRadius();
        float circleCenterY = y + circle.getRadius();

        // Set the initial position of the text to the circle's center
        text.setPosition(circleCenterX, circleCenterY);

        // Truncate the text if it doesn't fit within the circle
        float maxTextWidth = circle.getRadius() * 2.0f - 10.0f; // Circle diameter minus padding
        std::string truncatedTextStr = truncateText(text, maxTextWidth);
        text.setString(truncatedTextStr);

        // Re-calculate the origin after setting the truncated text to ensure it's centered
        textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        // Adjust the position again to ensure the truncated text is centered within the circle
        text.setPosition(circleCenterX, circleCenterY);

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
                    sf::Vertex(sf::Vector2f(x + 30, y + 30), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(childX + 30, childY + 30), sf::Color::Black)};
                window.draw(line, 2, sf::Lines);

                // Recursively draw the child node
                drawTree(window, node->childrens[i], childX, childY, xOffset / 1.5f, yOffset, level + 1);
            }
        }

        // Draw the circle and text
        window.draw(circle);
        window.draw(text);

        // Check if the mouse is hovering over the circle
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (circle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            // Create and position the tooltip box
            sf::RectangleShape tooltip(sf::Vector2f(200, 50));
            tooltip.setFillColor(sf::Color(255, 255, 255, 200)); // Semi-transparent white
            tooltip.setOutlineColor(sf::Color::Black);
            tooltip.setOutlineThickness(1);
            tooltip.setPosition(static_cast<float>(mousePos.x) + 10, static_cast<float>(mousePos.y) - 60);

            // Create and position the tooltip text
            sf::Text tooltipText;
            tooltipText.setFont(font);
            tooltipText.setString(nodeDataStr); // Full untruncated text
            tooltipText.setCharacterSize(15);
            tooltipText.setFillColor(sf::Color::Black);
            tooltipText.setPosition(tooltip.getPosition().x + 10, tooltip.getPosition().y + 10);

            // Draw the tooltip box and text
            window.draw(tooltip);
            window.draw(tooltipText);
        }
    }
};