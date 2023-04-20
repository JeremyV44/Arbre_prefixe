#include <iostream>
#include <string>
#include <vector>
#include "fonction.hpp"

// Vous pouvez utiliser ici les fonctions insert, searchNodesByPosition, display_tree1D et display_tree2D

//// Utilisation d'insert : insert("<séquence nucléotide>", {<position>}, root)
//// Vous pouvez alors insérer des séquences de nucléotides dans un arbre
//// searchNodeByPosition({<position>}, root) ; permet de trouver un noeud selon sa position
//// display_tree2D(cout, root) ; Permet de retourner l'arbre avec des retours à la ligne, affichant astérisques pour les noeuds terminaux
//// display_tree1D(cout,root) ; idem que display_tree2D mais ici l'affichage est sur une ligne
using namespace std;

int main(){
    radix_tree_t *root = nullptr;
    insert("", {0}, root);
    insert("CCCTCCGCGTA", {1}, root);
    insert("AAGCCCTCC", {4}, root);
    insert("TAACACC", {9}, root);
    insert("CGCGTAACA",{18},root);
    insert("GAGGACCAC",{27},root);
    insert("CACCAGAG",{10},root);
    insert("TAAGCC",{30},root);
    insert("TAACACCTCA",{15},root);
    display_tree2D(cout, root);    
    display_tree1D(cout, root);
return 0;

}


