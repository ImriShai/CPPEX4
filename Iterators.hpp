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
    
    vector<Node<T> *> it;
    /**
     * @brief Recursive function to traverse the tree in in order
     * @param root The root of the tree
     * @return vector<Node<T>*> The vector of nodes in in order
     * The function is a helper function for the constructor, it recursively traverses the tree in in order, and saves the nodes in a vector 
     * for the iterator to use
     */
    vector<Node<T> *> recursive(Node<T> *root)
    {
        vector<Node<T> *> result; //create a vector to store the nodes
        if (root == nullptr) //if the root is null return an empty vector
        {
            return result;
        }
        if(root->childrens.size() == 0){ //if the root has no childrens
            result.push_back(root); //push the root in the vector
        }
       if(root->childrens.size() == 1){ //if the root has childrens
              vector<Node<T> *> temp = recursive(root->childrens[0]); //call the recursive function for the left child
              result.insert(result.end(), temp.begin(), temp.end()); //insert the result of the recursive call in the result vector
              result.push_back(root); //push the root in the result vector
       }

       if(root->childrens.size() == 2){ //if the root has 2 childrens
           vector<Node<T> *> temp = recursive(root->childrens[0]); //call the recursive function for the left child
           result.insert(result.end(), temp.begin(), temp.end()); //insert the result of the recursive call in the result vector
           result.push_back(root); //push the root in the result vector
           vector<Node<T> *> temp2 = recursive(root->childrens[1]); //call the recursive function for the right child
           result.insert(result.end(), temp2.begin(), temp2.end()); //insert the result of the recursive call in the result vector
       } 
        return result; //return the result vector
    }


public:
    /**
     * @brief Construct a new in Order Iterator object
     * @param root The root of the tree
     * The constructor calls the recursive function to traverse the tree in in order and save the nodes in the vector
     */
    inOrderIterator(Node<T> *root) 
    {
        if (root != nullptr)//if the root is not null
        {
            it = recursive(root); //call the recursive function
        }
    }

/**
 * @brief Overloaded == operator
 * @param other The other iterator to compare with
 * @return true If the iterators are equal
 * @return false If the iterators are not equal
 * The operator checks if the iterators are equal by checking if the vectors are empty and if the first elements of the vectors are equal
 */
    bool operator==(const inOrderIterator &other)
    {
        if (it.empty() && other.it.empty()) //if both vectors are empty return true
        {
            return true;
        }
        
        if (it.empty() != other.it.empty())//if one of the vectors is empty and the other is not return false
        {
            return false;
        }
        return it.front() == other.it.front();//return the comparison of the first elements of the vectors(the Node*)
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
 * @return T& The data of the node at the front of the vector(the current iterator position)
 */
    T &operator*() { return it.front()->get_data(); } 

/**
 * @brief Overloaded -> operator
 * @return Node<T>* The pointer to the node at the front of the vector(the current iterator position)
 */
    Node<T> *operator->() { return it.front(); }

/**
 * @brief Overloaded ++ operator
 * @return inOrderIterator& The iterator after the increment
 * The operator increments the iterator by erasing the first element of the vector
 */
    inOrderIterator &operator++()
    {
        if (!it.empty())
        {
            it.erase(it.begin());
        }
        return *this;
    }
};

//NOTICE: for every other class most of the code is the same, only the recursive function is different, therfore only the recursive function will be explained




template <typename T>
class preOrderIterator
{
private:
   
    vector<Node<T> *> stack;

    /**
     * @brief Recursive function to traverse the tree in pre order
     * @param root The root of the tree
     * @return vector<Node<T>*> The vector of nodes in pre order
     * The function is a helper function for the constructor, it recursively traverses the tree in pre order, and saves the nodes in a vector
     */
    vector<Node<T> *> recursive(Node<T> *root)
    {
        vector<Node<T> *> result; //create a vector to store the nodes
        if (root == nullptr) //if the root is null return an empty vector
        {
            return result;
        }
        result.push_back(root); //push the root in the vector
        for (Node<T> *child : root->childrens) //for each child of the root call the recursive function(only 2 cildrens at max)
        {
            vector<Node<T> *> temp = recursive(child); //store the result of the recursive call in a temporary vector
            result.insert(result.end(), temp.begin(), temp.end()); //insert the temporary vector in the result vector, at the end
        }
        return result; //return the result vector
    }

public:
    preOrderIterator(Node<T> *root) 
    {
        if (root != nullptr)
        {
            stack = recursive(root);
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
        return stack.front() == other.stack.front();
    }

    bool operator!=(const preOrderIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return stack.front()->get_data(); }

    Node<T> *operator->() { return stack.front(); }

    preOrderIterator &operator++()
    {
        if (!stack.empty())
        {
            stack.erase(stack.begin());
        }
        return *this;
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