#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "LinkedList.h"

template <class T> class BinaryTree {
public:
    class Node;
    typedef std::shared_ptr<Node> NodePtr;
    class Node {
    public:
        T value;
        NodePtr left;
        NodePtr right;
        Node() {}
        Node(const T& value_) : value(value_) {}
    };
    BinaryTree() {}
    BinaryTree(LinkedList<T> list) {
        auto it = list.GetEnumerator();
        while(it->next()) {
            this->insert(*(*it));
        }
    }
    void insert(const T& value) {
        insertImpl(_root, value);
    }
    NodePtr find(const T& value) {
        return findImpl(_root, value);
    }
    bool findSubtree(BinaryTree<T> &subtree) {
        if (subtree._root == nullptr) {
            return true;
        }
        NodePtr t = find(subtree._root->value);
        return findSubtreeImpl(subtree._root, t);
    }
    void removeNode(const T& value) {
        _root = removeNodeImpl(_root, value);
    }
    void print() {
        printImpl(_root, "", false);
    }
    LinkedList<T> straightLeft() {
        return traverseTemplate(&straightLeftImpl);
    }
    LinkedList<T> straightRight() {
        return traverseTemplate(&straightRightImpl);
    }
    LinkedList<T> central() {
        return traverseTemplate(&centralImpl);
    }
    LinkedList<T> centralRight() {
        return traverseTemplate(&centralRightImpl);
    }
    LinkedList<T> reverseLeft() {
        return traverseTemplate(&reverseLeftImpl);
    }
    LinkedList<T> reverseRight() {
        return traverseTemplate(&reverseRightImpl);
    }
    template <typename T2>
    BinaryTree<T2> map(T2 (*func)(T)) {
        BinaryTree<T2> tree;
        LinkedList<T> list = straightLeft();
        for (size_t i = 0; i < list.GetLength(); i++) {
            tree.insert(func(list.Get(i)));
        }
        return tree;
    }
    BinaryTree<T> where(bool (*func)(T)) {
        BinaryTree<T> tree = copyTree();
        LinkedList<T> list = straightLeft();
        for (size_t i = 0; i < list.GetLength(); i++) {
            if (!func(list[i])) {
                tree.removeNode(list[i]);
            }
        }
        return tree;
    }
    BinaryTree<T> subtree(const T& value) {
        BinaryTree<T> tree;
        NodePtr node = find(value);
        if (node != nullptr) {
            tree._root = NodePtr(new Node(node->value));
            subtreeImpl(node, tree._root);
        }
        return tree;
    }
    bool equal(BinaryTree<T> &x2) {
        return equalImpl(_root, x2._root);
    }
    BinaryTree<T> copyTree() {
        BinaryTree<T> x2;
        copyImpl(x2._root, _root);
        return x2;
    }
private:
    void subtreeImpl(NodePtr& x1, NodePtr& x2) {
        if (x1->left.get()) {
            x2->left = NodePtr(new Node(x1->left->value));
            subtreeImpl(x1->left, x2->left);
        }
        if (x1->right.get()) {
            x2->right = NodePtr(new Node(x1->right->value));
            subtreeImpl(x1->right, x2->right);
        }

    }
    bool findSubtreeImpl(NodePtr& x1, NodePtr& x2) {
        if (x1.get() && x2 == nullptr) return false;
        if (x1 == nullptr) return true;
        if (x1->value != x2->value) return false;
        return findSubtreeImpl(x1->left, x2->left) && findSubtreeImpl(x1->right, x2->right);
    }
    void copyImpl(NodePtr& x1, NodePtr& x2) {
        x1 = NodePtr(new Node());
        if (x2 == nullptr) {x1 = nullptr; return;}
        else {
            x1->value = x2->value;
            if (x2->left.get()) copyImpl(x1->left, x2->left);
            if (x2->right.get()) copyImpl(x1->right, x2->right);
        }

    }
    bool equalImpl(NodePtr& x1, NodePtr& x2) {
        if (x1 == nullptr && x2 == nullptr) return true;
        if (x2 == nullptr || x1 == nullptr) return false;
        if (x1->value != x2->value) return false;
        return equalImpl(x1->left, x2->left) && equalImpl(x1->right, x2->right);
    }
    LinkedList<T> traverseTemplate(void (*func)(NodePtr&, LinkedList<T>&)) {
        LinkedList<T> res = LinkedList<T>();
        if (_root.get())
            func(_root, res);
        return res;
    }
    void printImpl(NodePtr& node, const std::string& indent, bool isRight) {
        if (node.get()) {
            std::cout << indent << (isRight ? "├──" : "└──") << node->value << '\n';
            printImpl(node->right, indent + (isRight ? "│   " : "    "), true);
            printImpl(node->left, indent + (isRight ? "│   " : "    "), false);
        }
    }
    void insertImpl(NodePtr& node, const T& value) {
        if (node.get()) {
            if (value < node->value)
                insertImpl(node->left, value);
            else if (value > node->value)
                insertImpl(node->right, value);
        } else
            node = NodePtr(new Node(value));
    }
    NodePtr findImpl(NodePtr& node, const T& value) {
        if (node.get()) {
            if (value < node->value)
                return findImpl(node->left, value);
            else if (value > node->value)
                return findImpl(node->right, value);
            else
                return node;
        } else
            return nullptr;
    }
    NodePtr removeNodeImpl(NodePtr& node, const T& value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->value)
            node->left = removeNodeImpl(node->left, value);

        else if (value > node->value)
            node->right = removeNodeImpl(node->right, value);

        else {
            if (node->left == nullptr)
                return node->right;
            if (node->right == nullptr)
                return node->left;

            NodePtr original;
            original = node;
            node = node->right;
            while (!(node->left == nullptr)) {
                node = node->left;
            }
            node->right = removeNodeImpl(original->right, node->value);
            node->left = original->left;
            return node;
        }
        return node;
    }
    static void centralImpl(NodePtr& node, LinkedList<T> & res) {
        if (node->left.get())
            centralImpl(node->left, res);
        res.Append(node->value);
        if (node->right.get())
            centralImpl(node->right, res);
    }
    static void centralRightImpl(NodePtr& node, LinkedList<T> & res) {
        if (node->right.get())
            centralRightImpl(node->right, res);
        res.Append(node->value);
        if (node->left.get())
            centralRightImpl(node->left, res);
    }
    static void straightLeftImpl(NodePtr& node, LinkedList<T> & res) {
        res.Append(node->value);
        if (node->left.get())
            straightLeftImpl(node->left, res);
        if (node->right.get())
            straightLeftImpl(node->right, res);
    }
    static void straightRightImpl(NodePtr& node, LinkedList<T> & res) {
        res.Append(node->value);
        if (node->right.get())
            straightRightImpl(node->right, res);
        if (node->left.get())
            straightRightImpl(node->left, res);
    }
    static void reverseLeftImpl(NodePtr& node, LinkedList<T> & res) {
        if (node->left.get())
            reverseLeftImpl(node->left, res);
        if (node->right.get())
            reverseLeftImpl(node->right, res);
        res.Append(node->value);
    }
    static void reverseRightImpl(NodePtr& node, LinkedList<T> & res) {
        if (node->right.get())
            reverseRightImpl(node->right, res);
        if (node->left.get())
            reverseRightImpl(node->left, res);
        res.Append(node->value);
    }
    NodePtr _root;
};