#ifndef fonction_h
#define fonction_h
#include <vector>
#include <string>
struct radix_tree_t ;   
radix_tree_t* createNode(std::string sqc, std::vector<int> positions, bool terminal) ;
radix_tree_t* searchNodeByPosition(int position, radix_tree_t* root) ;
void insert(std::string sqc, std::vector<int> positions, radix_tree_t*& root) ;
void display_tree2D(std::ostream& out, radix_tree_t* root, int space = 0) ;
void display_tree1D(std::ostream& out, radix_tree_t* root, int space = 0) ;

#endif


