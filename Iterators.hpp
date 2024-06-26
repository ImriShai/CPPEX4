#pragma once
#include <vector>
#include <stack>
#include <queue>
#include "Node.hpp"
using namespace std;


 /**
 * @brief In Order Iterator class for the Tree class
*/
template <typename T>
class inOrderIterator
{
    private: 
    stack<Node<T> *> stack; //stack to store the nodes
    public:

    /**
     * @brief Construct a new in Order Iterator object
     * @param root The root of the tree
     * The constructor creates an in order iterator for the tree, by pushing the nodes in the stack in the correct order
     * The constructor pushes the nodes in the stack in the correct order, by pushing the entire left branch of the tree in the stack
     */
    inOrderIterator(Node<T> *root) 
    {
        stack.push(nullptr); //push a null pointer in the stack
        while (root != nullptr) //while the root is not null
        {
           stack.push(root); //push the root in the stack
           if(root->childrens.size() >=1 ) //if the root has childrens push the left child in the stack
           {
               root = root->childrens[0]; 
           }
           else
           {
               root = nullptr;
           }
        }
    }
/**
 * @brief Overloaded == operator
 * @param other The other iterator to compare with
 * @return true If the iterators are equal
 * @return false If the iterators are not equal
 * The operator checks if the iterators are equal by comparing the top elements of the stacks
 */
    bool operator==(const inOrderIterator &other)
    {
        if (stack.empty() && other.stack.empty()) //if both stacks are empty return true
        {
            return true;
        }
        if (stack.empty() != other.stack.empty()) //if only one of the stacks is empty return false
        {
            return false;
        }
        return stack.top() == other.stack.top(); //return the comparison of the top elements of the stacks
    }

/**
 * @brief Overloaded != operator
 * @param other The other iterator to compare with
 * @return true If the iterators are not equal
 * @return false If the iterators are equal
 * The operator checks if the iterators are not equal by calling the == operator and negating the result
 */
    bool operator!=(const inOrderIterator &other)
    {
        return !(*this == other); //return the negation of the == operator
    }

/**
 * @brief Overloaded * operator
 * @return T& The data of the top element of the stack
 * The operator returns the data of the top element of the stack
 */
    T &operator*() { return stack.top()->get_data(); }


 /**
  * @brief Overloaded -> operator
  * @return Node<T>* The top element of the stack
  * The operator returns the top element of the stack
  */
    Node<T> *operator->() { return stack.top(); }


/**
 * @brief Overloaded ++ operator
 * @return inOrderIterator& The iterator after the increment
 * The operator increments the iterator by popping the top element of the stack and pushing the right child of the node in the stack
 * If the right child has childrens, the operator pushes the left child of the right child in the stack, and so on
 * This way the operator traverses the tree in in order
 */
    inOrderIterator &operator++()
    {
        Node<T> *current = stack.top(); //get the top element of the stack
        stack.pop(); //pop the top element
        if (current->childrens.size() == 2) //if the current node has a right child it pushes it to the stack
        {
            stack.push(current->childrens[1]);
            Node<T> *temp = current->childrens[1];
            while (temp->childrens.size() >= 1) //then, it pushes the left branch of the right child in the stack
            {
                stack.push(temp->childrens[0]);
                temp = temp->childrens[0];
            }
        }
        return *this; //return the iterator
    }


};

//NOTICE: for every other class most of the code is the same, only the recursive function is different, therfore only the recursive function will be explained



template <typename T>
class preOrderIterator
{
    private:
    stack<Node<T> *> stack;
    public:

    preOrderIterator(Node<T> *root) 
    {
        if (root != nullptr)
        {
            stack.push(root); //push the root in the stack
        }
    }

    bool operator==(const preOrderIterator &other)
    {
        if (stack.empty() && other.stack.empty())
        {
            return true;
        }
        if (stack.empty() != other.stack.empty())
        {
            return false;
        }
        return stack.top() == other.stack.top();
    }

    bool operator!=(const preOrderIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return stack.top()->get_data(); }

    Node<T> *operator->() { return stack.top(); }

    preOrderIterator &operator++()
    {
        Node<T> *current = stack.top(); //get the top element of the stack
        stack.pop(); //pop the top element
        for (int i = current->childrens.size() - 1; i >= 0; i--) //for each child of the current node push the child in the stack, this creates a reverse order of the childrens, 
        //first the right if exists, then the left if exists. 
        {
            stack.push(current->childrens[(size_t)i]);
        }
        return *this; //return the iterator
    }
};


template <typename T>
class postOrderIterator
{
private:
    vector<Node<T> *> stk;

    /**
     * @brief Recursive function to traverse the tree in post order
     * @param root The root of the tree
     * @return vector<Node<T>*> The vector of nodes in post order
     * The function is a helper function for the constructor, it recursively traverses the tree in post order, and saves the nodes in a vector
     */
    vector<Node<T> *> recursive(Node<T> *root) //does the same but in different order, first the childrens then the root
    {
        vector<Node<T> *> result;
        if (root == nullptr)
        {
            return result;
        }
        for (Node<T> *child : root->childrens)
        {
            vector<Node<T> *> temp = recursive(child);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        result.push_back(root);
        return result;
    }



public:
    postOrderIterator(Node<T> *root) 
    {
        if(root != nullptr){
        stk = recursive(root);
        }
    }

    bool operator==(const postOrderIterator &other)
    {
        if(stk.empty() && other.stk.empty())
        {
            return true;
        }
        if(stk.empty() != other.stk.empty())
        {
            return false;
        }
        return stk.front() == other.stk.front();
    }

    bool operator!=(const postOrderIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return stk.front()->get_data(); }

    Node<T> *operator->() { return stk.front(); }

    postOrderIterator &operator++()
    {
        if (!stk.empty())
        {
            stk.erase(stk.begin());
        }
        return *this;
    }
};

template <typename T>
class BFSIterator
{
private:
    queue<Node<T>*> queue; //queue to store the nodes

public:
    BFSIterator(Node<T>* root) {
        if (root == nullptr) { //if the root is null return
            return;
        }
        queue.push(root); //push the root in the queue
    }

   T& operator*() {
        return queue.front()->get_data();
    }
   const T& operator*() const {
        return queue.front()->get_data();
    }

    Node<T>* operator->() {
        return queue.front();
    }

/**
 * @brief Overloaded ++ operator
 * @return BFSIterator& The iterator after the increment
 * The operator increments the iterator by popping the first element of the queue and pushing the childrens of the node in the queue
 */
    BFSIterator& operator++() {
        if (queue.empty()) { //if the queue is empty return
            return *this;
        }
        Node<T>* current = queue.front(); //get the first element of the queue
        queue.pop(); //pop the first element
        for(auto& child : current->get_childrens()) { //for each child of the current node push the child in the queue
            queue.push(child);
        }
        return *this; //return the iterator
    }

   bool operator==(const BFSIterator& other) {
    if (queue.empty() && other.queue.empty()) {
        return true;
    }
    if (queue.empty() != other.queue.empty()) {
        return false;
    }
    return queue.front() == other.queue.front();
}

bool operator!=(const BFSIterator& other) {
    return !(*this == other);
}

};

template <typename T>
class DFSIterator
{
private:
    stack<Node<T> *> stack; //stack to store the nodes

public:
    DFSIterator(Node<T> *root) 
    {
        if(root != nullptr) //if the root is not null push the root in the stack
        {
            stack.push(root);
        }
    }

    bool operator==(const DFSIterator &other)
    {
        if (stack.empty() && other.stack.empty())
        {
            return true;
        }
        if (stack.empty() != other.stack.empty())
        {
            return false;
        }
        return stack.top() == other.stack.top();
    }

    bool operator!=(const DFSIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return stack.top()->get_data(); }

    Node<T> *operator->() { return stack.top(); }


/**
 * @brief Overloaded ++ operator
 * @return DFSIterator& The iterator after the increment
 * The operator increments the iterator by popping the top element of the stack and pushing the childrens of the node in the stack
 */
    DFSIterator &operator++()
    {
            Node<T>* current = stack.top(); //get the top element of the stack
            stack.pop(); //pop the top element
            for (int i = current->childrens.size() - 1; i >= 0; i--) //for each child of the current node push the child in the stack, this creates a reverse order of the childrens
            //which is the same as DFS
            {
                stack.push(current->childrens[(size_t)i]);
            }
        
       
        return *this; //return the iterator
    }
};

template <typename T>
class heapIterator
{ 
private:
    vector<Node<T> *> heap; //vector to store the nodes
public:

/**
 * @brief Construct a new heap Iterator object
 * @param root The root of the tree
 * The constructor calls the BFSIterator to traverse the tree in BFS and save the nodes in the vector, then it calls the make_heap function of std
 */
    heapIterator(Node<T> *root) 
    {
        if (root != nullptr)
        {
            for(auto node = BFSIterator<T>(root); node != BFSIterator<T>(nullptr); ++node) //iterate through the tree in BFS, and push the nodes in the vector
            {
                heap.push_back(node.operator->());
            }
            //call make_heap of std with the heap vector and a lambda function to compare the values of the nodes, creating a min heap(for the current status of the tree)
           std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->get_data() > b->get_data(); });
    }
    }

    bool operator==(const heapIterator &other)
    {
        if (heap.empty() && other.heap.empty())
        {
            return true;
        }
        if (heap.empty() != other.heap.empty())
        {
            return false;
        }
        return heap.front() == other.heap.front();
    }

    bool operator!=(const heapIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return heap.front()->get_data(); }

    Node<T> *operator->() { return heap.front(); }

    heapIterator &operator++()
    {
       if(!heap.empty()){
        heap.erase(heap.begin());
       }
        return *this;
    }

    
};