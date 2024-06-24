#pragma once
#include <vector>
using namespace std;
template <typename T>
class Node {
public:
    T data;
    Node* parent;
    vector<Node<T>*> childrens;

    Node(const T& data) : data(data), parent(nullptr) {}

    void add_child(Node<T>& child) {
        childrens.push_back(&child);
        child.parent = this;
    }

    void clean() {
        childrens.clear();
    }

    const vector<Node<T>*>& get_childrens() const {
        return childrens;
    }

    void set_data(const T& data) {
        this->data = data;
    }

    const T& get_data() const {
        return data;
    }
    

};