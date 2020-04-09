#include <fstream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node() {
        key = INT_MAX;
        left = nullptr;
        right = nullptr;
    }
};

void direct_left_bypass(Node* node, std::ofstream& out) {
    if (node != nullptr) {
        out << node->key << '\n';
        direct_left_bypass(node->left, out);
        direct_left_bypass(node->right, out);
    }
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

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    Node* root = create_tree(in);

    direct_left_bypass(root, out);

    return 0;
}
