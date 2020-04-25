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

bool back_left_bypass(Node* node, int min, int max) {
    if (node != nullptr) {
        if ((node->key < min) || (node->key >= max)) {
            return false;
        }

        return back_left_bypass(node->left, min, node->key) && back_left_bypass(node->right, node->key, max);
    }

    return true;
}

int main() {
    std::ifstream in("bst.in");
    std::ofstream out("bst.out");

    int num_nodes;
    int root_key;

    in >> num_nodes >> root_key;

    Node** nodes = new Node*[num_nodes];
    Node* root = new Node;

    root->key = root_key;
    nodes[0] = root;

    for (int i = 1; i < num_nodes; i++) {
        int node_key;
        int num_parent;
        char direction;

        in >> node_key >> num_parent >> direction;

        num_parent--;

        Node* node = new Node;

        node->key = node_key;

        if (direction == 'L') {
            nodes[num_parent]->left = node;
        }
        else {
            nodes[num_parent]->right = node;
        }

        nodes[i] = node;
    }

    if (back_left_bypass(root, -INT_MAX, INT_MAX)) {
        out << "YES";
    }
    else {
        out << "NO";
    }

    in.close();
    out.close();

    return 0;
}
