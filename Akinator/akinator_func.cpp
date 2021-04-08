#include "akinator.h"


void print_all_elements(tree_element* tmp, FILE* dump)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if(tmp->get_right())
	{
		print_all_elements(tmp->get_right(), dump);
		fprintf(dump, "\"%s\" -> \"%s\" [label=\"Да\", fontcolor=darkblue]\n", tmp->non_const_get_data(), (tmp->get_right())->non_const_get_data());
	}
	if (tmp->get_left())
	{
		print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%s\" -> \"%s\" [label=\"Нет\", fontcolor=darkblue]\n", tmp->non_const_get_data(), (tmp->get_left())->non_const_get_data());
	}

    if((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
        fprintf(dump, "\"%s\" [label = \"%s\",style = filled, fillcolor = lightgreen] \n", tmp->non_const_get_data(), tmp->non_const_get_data());
    return;

}

void free_all(tree_element* root)
{
    assert(root && "Nullptr root in free_all");

    if(root->get_left())
        free_all(root->get_left());
	if(root->get_right())
        free_all(root->get_right());


    //printf("Free data\n");
    free(root->non_const_get_data());
    root->non_const_get_data() = nullptr;

	//printf("Free root\n");
	free(root);
	root = nullptr;

	return;
}

long size_of_file(FILE *user_code)
{
	assert(user_code);

	fseek(user_code, 0, SEEK_END);
	long file_length = ftell(user_code);
	fseek(user_code, 0, SEEK_SET);

	file_length++;

	return file_length;
}
