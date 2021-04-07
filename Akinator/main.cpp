#include "akinator.h"

int main()
{
    tree bin_tree("akinator");

    //tree_element root(10);
    tree_element* root = bin_tree.add_to_left(nullptr, 10);

    bin_tree.add_to_left(root, 10);
    bin_tree.add_to_right(root, 20);




    return 0;
}
