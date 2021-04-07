#include "akinator.h"

// Класс вынести в отдельнй .cpp/.h

// fill_tree(FILE* base);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    tree bin_tree("akinator");

    tree_element* root = bin_tree.add_to_left(nullptr, "КОТ?");

    bin_tree.add_to_left(root, "Poltorashka");
    bin_tree.add_to_right(root, "Stasik");


    bin_tree.print_tree(true);

    return 0;
}
