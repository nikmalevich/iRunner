#include <fstream>

struct Node {
    int key;
    int sum_keys;
    int sum_keys_max_pass;
    unsigned int height;
    unsigned int msl;
    Node* left;
    Node* right;
    Node* parent;

    Node() {
        key = INT_MAX;
        sum_keys = INT_MIN;
        sum_keys_max_pass = INT_MIN;
        height = 0;
        msl = 0;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

void direct_left_bypass(Node* node, std::ofstream& out) {
    if (node != nullptr) {
        out << node->key << "\n";
        direct_left_bypass(node->left, out);
        direct_left_bypass(node->right, out);
    }
}

Node* max_node(Node* x, Node* y) {
    if (x->msl > y->msl) {
        return x;
    }
    else if (x->msl < y->msl) {
        return y;
    }
    else {
        if (x->sum_keys >= y->sum_keys) {
            return x;
        }
        else {
            return y;
        }
    }
}

Node* back_left_bypass(Node* node) {
    if (node != nullptr) {
        auto left_node = back_left_bypass(node->left);
        auto right_node = back_left_bypass(node->right);

        if ((node->right != nullptr) && (node->left != nullptr)) {
            if (node->right->height >= node->left->height) {
                node->height = node->right->height + 1;
                node->sum_keys_max_pass = node->right->sum_keys_max_pass + node->key;
            }
            else {
                node->height = node->left->height + 1;
                node->sum_keys_max_pass = node->left->sum_keys_max_pass + node->key;
            }

            node->msl = node->right->height + node->left->height + 2;
            node->sum_keys = node->right->sum_keys_max_pass + node->left->sum_keys_max_pass + node->key;
        }
        else if (node->right != nullptr) {
            node->height = node->right->height + 1;
            node->msl = node->height;
            node->sum_keys = node->right->sum_keys_max_pass + node->key;
            node->sum_keys_max_pass = node->right->sum_keys_max_pass + node->key;
        }
        else if (node->left != nullptr) {
            node->height = node->left->height + 1;
            node->msl = node->height;
            node->sum_keys = node->left->sum_keys_max_pass + node->key;
            node->sum_keys_max_pass = node->left->sum_keys_max_pass + node->key;
        }
        else {
            node->height = 0;
            node->msl = 0;
            node->sum_keys = node->key;
            node->sum_keys_max_pass = node->key;
        }

        return max_node(max_node(right_node, left_node), node);
    }

    return new Node;
}

Node* create_tree(std::ifstream& in) {
    int num;
    Node* root = new Node;

    in >> num;

    root->key = num;

    while (in >> num) {
        Node* cur_node = root;

        while (true) {
            if (num == cur_node->key) {
                break;
            }
            else if (num > cur_node->key) {
                if (cur_node->right == nullptr) {
                    Node* new_node = new Node;

                    new_node->key = num;
                    new_node->parent = cur_node;
                    cur_node->right = new_node;

                    break;
                }
                else {
                    cur_node = cur_node->right;
                }
            }
            else {
                if (cur_node->left == nullptr) {
                    Node* new_node = new Node;

                    new_node->key = num;
                    new_node->parent = cur_node;
                    cur_node->left = new_node;

                    break;
                }
                else {
                    cur_node = cur_node->left;
                }
            }
        }
    }

    return root;
}

void right_delete_node(Node* &root, Node* delete_node) {
    if ((delete_node->right != nullptr) && (delete_node->left != nullptr)) {
        Node* cur_node = delete_node;
        cur_node = cur_node->right;

        while (cur_node->left != nullptr) {
            cur_node = cur_node->left;
        }

        if (cur_node->key > cur_node->parent->key) {
            delete_node->key = cur_node->key;
            cur_node->parent->right = cur_node->right;
        }
        else {
            delete_node->key = cur_node->key;
            cur_node->parent->left = cur_node->right;
        }
    }
    else if (delete_node->right != nullptr) {
        if (delete_node->parent != nullptr) {
            if (delete_node->key > delete_node->parent->key) {
                delete_node->parent->right = delete_node->right;
            }
            else {
                delete_node->parent->left = delete_node->right;
            }
        } else {
            root = delete_node->right;
        }
    }
    else if (delete_node->left != nullptr) {
        if (delete_node->parent != nullptr) {
            if (delete_node->key > delete_node->parent->key) {
                delete_node->parent->right = delete_node->left;
            }
            else {
                delete_node->parent->left = delete_node->left;
            }
        }
        else {
            root = delete_node->left;
        }
    }
    else {
        if (delete_node->key > delete_node->parent->key) {
            delete_node->parent->right = nullptr;
        }
        else {
            delete_node->parent->left = nullptr;
        }
    }
}

void find_center_node(Node* &center_node, unsigned int height_center_node) {
    while (true) {
        if (center_node->height == height_center_node) {
            return;
        }

        if ((center_node->right != nullptr) && (center_node->left != nullptr)) {
            if (center_node->right->height > center_node->left->height) {
                center_node = center_node->right;
            } else if (center_node->right->height < center_node->left->height) {
                center_node = center_node->left;
            } else {
                if (center_node->right->sum_keys_max_pass > center_node->left->sum_keys_max_pass) {
                    center_node = center_node->right;
                } else {
                    center_node = center_node->left;
                }
            }
        } else if (center_node->right != nullptr) {
            center_node = center_node->right;
        } else {
            center_node = center_node->left;
        }
    }
}

int main() {
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    Node* root = create_tree(in);

    auto pass_root = back_left_bypass(root);

    unsigned int pass_length = pass_root->msl;

    if (pass_length % 2 == 0) {
        unsigned int height_center_node = pass_length / 2;
        Node* center_node = pass_root;

        find_center_node(center_node, height_center_node);

        if (center_node != pass_root) {
            right_delete_node(root, center_node);
        }
    }

    right_delete_node(root, pass_root);

    direct_left_bypass(root, out);

    in.close();
    out.close();

    return 0;
}