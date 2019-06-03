#pragma once
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
class AVLTree
{
    struct Node
    {
        T key;
        int height;
        Node *left, *right, *parent;
        Node(T key): key(key), height(1), left(nullptr), right(nullptr), parent(nullptr){}
        Node(T key, int height, Node* left, Node* right, Node* parent): key(key),
            height(height), left(left), right(left), parent(left){}
    };

    Node *root = nullptr;

    int height(Node* v)
    {
        return v ? v->height : 0;
    }

    int balance_factor(Node* v)
    {
        if(!v)
            return 0;

        return height(v->right) - height(v->left);
    }

    void update(Node *v)
    {
        if(!v)
            return;
        if(v->left != nullptr)
            v->left->parent = v;
        if(v->right != nullptr)
            v->right->parent = v;

        v->height = std::max(height(v->left), height(v->right)) + 1;
    }

    Node* rotate_right(Node* v)
    {
        Node* u = v->left;
        v->left = u->right;
        u->right = v;
        v->parent = nullptr;
        u->parent = nullptr;
        update(v);
        update(u);
        return u;
    }

    Node* rotate_left(Node* v)
    {
        Node* u = v->right;
        v->right = u->left;
        u->left = v;
        v->parent = nullptr;
        u->parent = nullptr;

        update(v);
        update(u);
        return u;
    }

    Node* balance(Node *v)
    {
        if(balance_factor(v) == 2)
        {
            if(balance_factor(v->right) < 0)
            {
                v->right = rotate_right(v->right);
            }
            update(v->right);
            v = rotate_left(v);
            update(v);
            return v;
        }

        if(balance_factor(v) == -2)
        {
            if(balance_factor(v->left) > 0)
            {
                v->left = rotate_left(v->left);
            }
            update(v->left);

            v = rotate_right(v);
            update(v);
            return v;
        }

        return v;
    }

    Node* insert(Node *v, T key)
    {
        if(!v)
        {
            return new Node(key);
        }

        if(v->key >= key)
            v->left = insert(v->left, key);
        else
            v->right = insert(v->right, key);
        update(v);
        v = balance(v);
        return v;
    }

    Node* find_min(Node* v)
    {
        return v->left ? find_min(v->left) : v;
    }

    Node* find_max(Node* v)
    {
        return v->right ? find_max(v->right) : v;
    }

    Node* remove_min(Node* v)
    {
        if(v->left == nullptr)
            return v->right;

        v->left = remove_min(v->left);
        update(v);
        return balance(v);
    }

    Node* remove(Node* v, int k)
    {
        if(!v)
            return nullptr;

        if(v->key > k)
            v->left = remove(v->left, k);
        else
            v->right = remove(v->right, k);

        if(v->key == k)
        {
            Node* l = v->left;
            Node* r = v->right;
            delete v;
            if(r == nullptr)
                return l;
            Node* u = find_min(r);
            u->right = remove_min(r);
            u->left = l;
            update(u);
            return balance(u);
        }
        update(v);
        return balance(v);
    }
public:
    class Iterator
    {
        Node* current;

    public:
        Iterator(Node* current): current(current){};
        Iterator operator++()
        {
            if(current->right != nullptr)
            {
                current = current->right;
                while(current->left != nullptr)
                    current = current->left;
            }
            else
            {
                bool ok = false;
                while(current->parent != nullptr)
                {
                    if(current->parent->left == current)
                    {
                        current = current->parent;
                        ok = true;
                        break;
                    }

                    current = current->parent;
                }

                if(!ok)
                    current = nullptr;

            }
        }
        bool operator!=(Iterator right){return current != right.current;}
        T operator*(){ return current->key; }
    };

    void insert(T key)
    {
        root = insert(root, key);
        update(root);
    }

    void remove(T key)
    {
        root = remove(root, key);
        update(root);
    }

    Iterator get_root()
    {
        return Iterator(root);
    }

    Iterator begin()
    {
        return Iterator(find_min(root));
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }
};
