#pragma once

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int _data) : data(_data), left(nullptr), right(nullptr) {}
    
    bool childless() const {
        return left == nullptr && right == nullptr;
    }
};

class BinTree {
    Node* root;

public:
    BinTree() : root(nullptr) {}
    ~BinTree() {
       del(root);
    }
    void add(int x, char* path) {
        add(x, root, path);
    }

private:
    void add(int x, Node*& sub_root, char* path) {
        if (sub_root == nullptr) {
            sub_root = new Node(x);
            return;
        }
        if (path[0] == 'L') {
            add(x, sub_root->left, path + 1);
            return;
        }
        // Now path[0] is 'R'
        add(x, sub_root->right, path + 1);
        return;
    }
    void del(Node*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    }
   
public:
    bool is_BOT() const {
        return root == nullptr || is_nonempty_BOT(root);
    }

private:
    bool is_nonempty_BOT(Node* root) const {
        return is_BOT_with_elements_smaller_than(root->data, root->left)
            && is_BOT_with_elements_larger_than(root->data, root->right);
    }

    bool is_BOT_with_elements_smaller_than(int x, Node* root) const {
        return root == nullptr
            || (is_nonempty_BOT(root) && x > max_in_BOT(root));
    }
    bool is_BOT_with_elements_larger_than(int x, Node* root) const {
        return root == nullptr
            || (is_nonempty_BOT(root) && x < min_in_BOT(root));
    }

    int max_in_BOT(Node* node) const {
        return node->right == nullptr ? node->data : max_in_BOT(node->right);
    }
    int min_in_BOT(Node* node) const {
        return node->left == nullptr ? node->data : min_in_BOT(node->left);
    }
};