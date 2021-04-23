#include "akinator.h"
#include <SFML/Graphics.hpp>


#define PLAY(arg)                       \
    if(!strcmp(#arg, "console"))        \
        bin_tree.play();                \
    else if(!strcmp(#arg, "graphic"))   \
        bin_tree.graphic_play();        \
    else if(!strcmp(#arg, "REG1"))      \
        bin_tree.play();                \
    else if(!strcmp(#arg, "REG2"))      \
        bin_tree.graphic_play();        \
    else                                \
    {                                   \
        printf("No such regime\n");     \
        return 1;                       \
    }

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    tree bin_tree("akinator");
    
    PLAY(REG1);    


    
    return 0;
}

