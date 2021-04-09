#include "akinator.h"


void print_all_elements(tree_element* tmp, FILE* dump)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if(tmp->get_right())
	{
		print_all_elements(tmp->get_right(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp, tmp->get_right());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
	}
	if (tmp->get_left())
	{
		print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp, tmp->get_left());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
	}


    if((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
		fprintf(dump, "\"%p\" [label = \"<f0> value = [%.*s]|{<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp->get_left(), tmp->get_prev(), tmp->get_right());
	else
		if(tmp->get_prev() == nullptr)
			fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());
		else 
			fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());


    return;

}

void print_all_elements_beauty(tree_element* tmp, FILE* dump)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if (tmp->get_right())
	{
		print_all_elements_beauty(tmp->get_right(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp, tmp->get_right());
	}
	if (tmp->get_left())
	{
		print_all_elements_beauty(tmp->get_left(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp, tmp->get_left());
	}

	if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
		fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data());
	else
		if(tmp->get_prev() == nullptr)
			fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data());
		else
			fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data());
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
