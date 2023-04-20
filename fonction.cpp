#include "fonction.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Création de la strcuture noeud

struct radix_tree_t {
    string sqc;
    radix_tree_t* branch[4];
    vector<int> positions;
    radix_tree_t* parent;
    bool terminal;

    radix_tree_t() {
        for (int i = 0; i < 4; i++) {
            branch[i] = nullptr;
        }
        parent = nullptr;
        terminal = false;
    }
};
// Fonction permettant de créer des nouveaux noeuds

radix_tree_t* createNode(string sqc, vector<int> positions, bool terminal) {
    radix_tree_t* node = new radix_tree_t;
    node->sqc = sqc;
    node->positions = positions;
    node->terminal = terminal;
    for (int i = 0; i < 4; i++) {
        node->branch[i] = nullptr;
    }
    return node;
}

radix_tree_t* searchNodeByPosition(int position, radix_tree_t* root) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->terminal) {
        for (int i = 0; i < root->positions.size(); i++) {
            if (root->positions[i] == position) {
                return root;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        radix_tree_t* node = searchNodeByPosition(position, root->branch[i]);
        if (node != nullptr) {
            return node;
        }
    }
    return nullptr;
}


void insert(string sqc, vector<int> positions, radix_tree_t*& root) {
    if (root == nullptr) {
        root = createNode(sqc, positions, true);
        return;
    }
    radix_tree_t* current = root;
    int i = 0;
    while (i < sqc.size()) {
        int index = -1;
        switch (sqc[i]) {
            case 'A':
                index = 0;
                break;
            case 'C':
                index = 1;
                break;
            case 'G':
                index = 2;
                break;
            case 'T':
                index = 3;
                break;
            default:
                "Mauvais nucléotide"
                return;
        }
        if (current->branch[index] == nullptr) {
            current->branch[index] = createNode(sqc.substr(i), positions, true);
            current->branch[index]->parent = current;
            return;
        }
        string& s = current->branch[index]->sqc;
        int j = 0;
        while (j < s.size() && i + j < sqc.size() && s[j] == sqc[i + j]) {
            j++;
        }
        if (j == s.size()) {
            // Si le match est total, on continue la recherche
            current = current->branch[index];
            i += j;
        } else {
            // Si le match est partiel, alors on sépare le noeud
            radix_tree_t* newNode = createNode(s.substr(i + j), {}, false);
            newNode->parent = current->branch[index];
            current->branch[index]->sqc = s.substr(0, j);
            current->branch[index]->branch[newNode->sqc[0] - 'A'] = newNode;
            if (current->branch[index]->terminal) {
                // the split node was terminal, so the new node is terminal too
                newNode->terminal = true;
                newNode->positions = current->branch[index]->positions;
                current->branch[index]->terminal = false;
                current->branch[index]->positions.clear();
            }
            current->branch[index]->branch[sqc[i + j] - 'A'] = createNode(sqc.substr(i + j + 1), positions, true);
            current->branch[index]->branch[sqc[i + j] - 'A']->parent = current->branch[index];
            return;
        }
    }
    if (i == sqc.size()) {
        // Dans le cas où sqc est un préfix d'un noeud pré-existant
        current->terminal = true;
        current->positions = positions;
    } else {
        // insert new node
        current->branch[sqc[i] - 'A'] = createNode(sqc.substr(i), positions, true);
        current->branch[sqc[i] - 'A']->parent = current;
    }
}
void display_tree2D(ostream& os, radix_tree_t *root, int indent) {
    if (root == nullptr) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        os << "  ";
    }
    os << root->sqc;
    if (root->terminal) {
        os << "*";
    }
    os << endl;
    for (int i = 0; i < 4; i++) {
        display_tree2D(os, root->branch[i], indent + 1);
    }
}

void display_tree1D(ostream& os, radix_tree_t *root, int indent) {
    if (root == nullptr) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        os << "  ";
    }
    os << root->sqc;
    if (root->terminal) {
        os << "*";
    }
    os << " ";
    for (int i = 0; i < 4; i++) {
        display_tree1D(os, root->branch[i], indent + 1);
    }
}

