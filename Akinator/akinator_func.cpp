#include "akinator.h"

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
	data_(data),
	prev_(prev),
	left_(left),
	right_(right)
{
	printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to list_elem construct");
}

tree_element::~tree_element()
{
	assert(this && "You passed nullptr to ~tree_element");
    printf("in %s\n", __PRETTY_FUNCTION__);
	data_ = POISON;

	prev_ = nullptr;
	left_ = nullptr;
	right_ = nullptr;

}

tree::tree(const char* name) :
	cur_size_(0),
	error_state_(0),
	name_(name),
	root_(nullptr)
{
    printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to constructor");
	assert(name && "You need to pass name");
}

tree::~tree()
{
    printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "nullptr in desctructor");


	if(root_)
        free_all(root_);
    else
        printf("No free\n");

	cur_size_ = -1;
	error_state_ = -1;
	name_ = nullptr;
	root_ = nullptr;
}

void free_all(tree_element* root)
{
    assert(root && "Nullptr root in free_all");

	if(root->get_right())
        free_right(root->get_right());
	if(root->get_left())
        free_left(root->get_left());

	printf("Free root\n");

	free(root);
	root = nullptr;

	return;
}

void free_right(tree_element* tmp)
{
    assert(tmp && "Nullptr tmp in free_right()");
	if((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
	{
		printf("Free leaf\n");
		free(tmp);
		tmp = nullptr;
		return;
	}
	else
		return free_all(tmp);
}

void free_left(tree_element* tmp)
{
	if((tmp->get_left() == nullptr) && (tmp->get_right() == nullptr))
	{
		printf("Free leaf\n");
		free(tmp);
		tmp = nullptr;
		return;
	}
	else
		return free_all(tmp);
}

tree_element* tree::add_to_left(tree_element* x, data_type number)
{
	//assert(!isnan(number) && "You passed NAN number");
	//assert(x && "You passed nullptr x yo add_to_left");
	assert(this && "You passed nullptr tree");


    printf("Calloc\n");
	tree_element* tmp = (tree_element*) calloc(1, sizeof(tree_element));
	assert(tmp && "Can't calloc memory for tree_element");

    if((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;
    	tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);
        cur_size_++;
    }
    else if(cur_size_)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);
        cur_size_++;

        x->set_left(tmp);
	}
	else
        printf("You must pass x\n");

	return tmp;
}

tree_element* tree::add_to_right(tree_element* x, data_type number)
{
	//assert(!isnan(number) && "You passed NAN number");
	//assert(x && "You passed nullptr x yo add_to_left");
	assert(this && "You passed nullptr tree");


    printf("Calloc\n");
	tree_element* tmp = (tree_element*) calloc(1, sizeof(tree_element));
	assert(tmp && "Can't calloc memory for tree_element");

    if((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;
    	tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);
        cur_size_++;
    }
    else if(cur_size_)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);
        cur_size_++;

        x->set_right(tmp);
	}
	else
        printf("You must pass x\n");

	return tmp;
}

void tree::fill_tree(FILE* database) // Ò‰ÂÎ‡Ú¸ ËÏˇ Ù‡ÈÎ‡, ‡ ÌÂ file
{
    assert(database && "You need to pass database");
    return;
}

const void tree::print_tree(bool need_graphviz_dump) const
{
	if(need_graphviz_dump)
	{
        //char* dumpfile_name = "dump.dot";
        graphviz_dump("dump.dot");

        system("iconv.exe -t UTF-8 -f  CP1251 < dump.dot > dump_temp.dot");
        system("dot dump_temp.dot -Tpdf -o dump.pdf");
        system("del dump.dot");
        system("ren dump_temp.dot dump.dot");

        system("dump.pdf");


// or   system("dot dump.dot -Tpng -o dump_list.png"); // if u want [.png] format
	}

	//FILE* txt_dump = fopen("dump.txt", "wb");
	//assert(txt_dump && "Can't open dump.txt");

	size_t counter = 0;

    //const tree_element* tmp = get_start();

    /*if(tmp == nullptr)
    {
        fprintf(txt_dump, "List if empty");
        return;
    } */

    /*fprintf(txt_dump, "START_ELEMENT: [%d]: [%lg] -> ", ++counter, tmp->get_data());
    tmp = tmp->get_next();

	for(tmp; !is_end(tmp); tmp = tmp->get_next())
		fprintf(txt_dump, "[%d]: [%lg] -> ", ++counter, tmp->get_data());

    fprintf(txt_dump, "END_ELEMENT: [%d]: [%lg].\n", ++counter, tmp->get_data());
    fprintf(txt_dump, "SIZE: [%d]\nNAME: [%s]\nERROR_STATE: [%d]", cur_size_, name_, error_state_);
	*/
	return;
}

const void tree::graphviz_dump(char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=ellipse, fillcolor = purple]\n");
    fprintf(dump, "edge [color=Blue, style=dashed]\n");
    //fprintf(dump, "rankdir=LR\n");

    size_t counter = 1;
    tree_element* tmp = root_;
    //fprintf(dump, "%d [label =\"<f0> value = [%s]\"];\n", counter, tmp->get_data(), tmp->get_next());

	// Œ¡Œ…“» ¬—≈ ƒ≈–≈¬Œ

	print_all_elements(tmp, dump, &counter);

    //tmp = root_;
    //counter = 1;

    //printf("EDGEEEEEEEEEEEES\n");
    //print_all_edges(tmp, dump, &counter);
    fprintf(dump, "}");

    fclose(dump);
    return;
}

void print_all_edges(tree_element* tmp, FILE* dump, size_t* counter)
{
    assert(tmp && "You passed nullptr tmp to print_all_edges");
    assert(dump && "You don't pass dump file name");

    if(tmp->get_right())
    {
        printf("Go to right\n");
        print_right_edge(tmp->get_right(), dump, counter);
    }
    if(tmp->get_left())
    {
        printf("GO to left\n");
        print_left_edge(tmp->get_left(), dump, counter);
    }

    if(tmp->get_right())
    {
        fprintf(dump, "%d:f2 -> %d:f0 [color=blue,penwidth=2.0];\n", (*counter), (*counter) + 1);
        (*counter)++;
    }
    if(tmp->get_left())
    {
        fprintf(dump, "%d:f2 -> %d:f0 [color=blue,penwidth=2.0];\n", (*counter), (*counter) + 1);
        /*(*counter)++;*/
    }


}

void print_right_edge(tree_element* tmp, FILE* dump, size_t* counter)
{
    if((tmp->get_left() == nullptr) && (tmp->get_right() == nullptr))
    {
        printf("Find right leaf, connecting to papa\n");
        fprintf(dump, "%d:f0 -> %d:f3 [color=blue,penwidth=2.0];\n", (*counter), (*counter) + 1);
        (*counter)++;
    }
    else
    {
        printf("Not a leaf, go next\n");
        print_all_edges(tmp->get_right(), dump, counter);
    }
}

void print_left_edge(tree_element* tmp, FILE* dump, size_t* counter)
{
    if((tmp->get_left() == nullptr) && (tmp->get_right() == nullptr))
    {
        printf("Find left leaf, connecting to papa\n");
        fprintf(dump, "%d:f0 -> %d:f3 [color=blue,penwidth=2.0];\n", (*counter), (*counter) + 1);
        (*counter)++;
    }
    else
    {
        printf("Not a leaf, go next\n");
        print_all_edges(tmp->get_left(), dump, counter);
    }
}

void print_all_elements(tree_element* tmp, FILE* dump, size_t* counter)
{
	assert(tmp && "tmp is nullptr in print_all_elements");

	if(tmp->get_right())
	{
		//printf("Print right root\n");
		print_right_root(tmp->get_right(), dump, counter);
		fprintf(dump, "\"%s\" -> \"%s\" [label=\"No\", fontcolor=darkblue]\n", tmp->non_const_get_data(), (tmp->get_right())->non_const_get_data());
		(*counter)++;
	}
	if (tmp->get_left())
	{
		print_left_root(tmp->get_left(), dump, counter);
        fprintf(dump, "\"%s\" -> \"%s\" [label=\"Yes\", fontcolor=darkblue]\n", tmp->non_const_get_data(), (tmp->get_left())->non_const_get_data());
        (*counter)++;
	}
    fprintf(dump, "\"%s\" [label = \"%s\",style = filled, fillcolor = purple] \n", tmp->non_const_get_data(), tmp->non_const_get_data());
	return;

}

void print_right_root(tree_element* tmp, FILE* dump,size_t* counter)
{
	assert(tmp && "tmp is nullptr in print_right_root");
	assert(dump && "dump is not identified");

	if((tmp->get_left() == nullptr) && (tmp->get_right() == nullptr))
    {
        printf("print right leaf\n");
        fprintf(dump, "%s [label = \"%s\", style = filled, fillcolor = green]\n", tmp->non_const_get_data(), tmp->non_const_get_data());
        //fprintf(dump, "%s [label = \"%s\"]\n", tmp->get_data(), tmp->get_data());
	}
	else
        print_all_elements(tmp->get_right(), dump, counter);

}

void print_left_root(tree_element* tmp, FILE* dump,size_t* counter)
{
	assert(tmp && "tmp is nullptr in print_right_root");
	assert(dump && "dump is not identified");


	if((tmp->get_left() == nullptr) && (tmp->get_right() == nullptr))
	{
        printf("print left leaf\n");
        fprintf(dump, "%s [label = \"%s\", fillcolor = green]\n", tmp->non_const_get_data(), tmp->non_const_get_data());
    }
	else
        print_all_elements(tmp->get_left(), dump, counter);

}
