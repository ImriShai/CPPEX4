#pragma once
#include <vector>
#include <stack>
#include <queue>
#include "Node.hpp"
using namespace std;


template <typename T>
class inOrderIterator
{
private:
    
    vector<Node<T> *> it;
    vector<Node<T> *> recursive(Node<T> *root)
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
    inOrderIterator(Node<T> *root) 
    {
        if (root != nullptr)
        {
            it = recursive(root);
        }
    }

    bool operator==(const inOrderIterator &other)
    {
        if (it.empty() && other.it.empty())
        {
            return true;
        }
        if (it.empty() != other.it.empty())
        {
            return false;
        }
        return it.front() == other.it.front();
    }

    bool operator!=(const inOrderIterator &other)
    {
        return !(*this == other);
    }

    T &operator*() { return it.front()->get_value(); }

    Node<T> *operator->() { return it.front(); }

    inOrderIterator &operator++()
    {
        if (!it.empty())
        {
            it.erase(it.begin());
        }
        return *this;
    }
};

template <typename T>
class preOrderIterator
{
private:
   
    vector<Node<T> *> stack;
    vector<Node<T> *> recursive(Node<T> *root)
    {
        vector<Node<T> *> result;
        if (root == nullptr)
        {
            return result;
        }
        result.push_back(root);
        for (Node<T> *child : root->childrens)
        {
            vector<Node<T> *> temp = recursive(child);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
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

    T &operator*() { return stack.front()->get_value(); }

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
    vector<Node<T> *> recursive(Node<T> *root)
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

    T &operator*() { return stk.front()->get_value(); }

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
    queue<Node<T>*> queue;

public:
    BFSIterator(Node<T>* root) {
        if (root == nullptr) {
            return;
        }
        queue.push(root);
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

    BFSIterator& operator++() {
        if (queue.empty()) {
            return *this;
        }
        Node<T>* current = queue.front();
        queue.pop();
        for(auto& child : current->get_childrens()) {
            queue.push(child);
        }
        return *this;
    }

   bool operator==(const BFSIterator& other) {
    // Both iterators are at the end
    if (queue.empty() && other.queue.empty()) {
        return true;
    }
    // One iterator is at the end, and the other is not
    if (queue.empty() != other.queue.empty()) {
        return false;
    }
    // Neither iterator is at the end, compare the front of the queues
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
    stack<Node<T> *> stack;

public:
    DFSIterator(Node<T> *root) 
    {
        if(root != nullptr)
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

    T &operator*() { return stack.top()->get_value(); }

    Node<T> *operator->() { return stack.top(); }

    DFSIterator &operator++()
    {
       
            Node<T>* current = stack.top();
            stack.pop();
            for (int i = current->childrens.size() - 1; i >= 0; i--)
            {
                stack.push(current->childrens[(size_t)i]);
            }
        
       
        return *this;
    }
};

template <typename T>
class heapIterator
{ // this should convert the tree to a heap and return iterators
private:
    Node<T> *current;
    vector<Node<T> *> heap;

public:
    heapIterator(Node<T> *root) : current(root)
    {
        heap.push_back(current);
        for (int i = 0; i < heap.size(); i++)
        {
            for (Node<T> *child : heap[i]->childrens)
            {
                heap.push_back(child);
            }
        }
    }

    bool operator==(const heapIterator &other)
    {
        return heap.front() == other.heap.front();
    }

    bool operator!=(const heapIterator &other)
    {
        return heap.front() != other.heap.front();
    }

    T &operator*() { return heap.front()->get_value(); }

    Node<T> *operator->() { return heap.front(); }

    heapIterator &operator++()
    {
        if (!heap.empty())
        {
            current = heap.front();
            heap.erase(heap.begin());
        }
        else
        {
            current = nullptr;
        }
        return *this;
    }
};