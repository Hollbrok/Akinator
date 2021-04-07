#include "tree.h"

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

void tree::fill_tree(FILE* database)
{
    assert(database && "You need to pass database");
    return;
}

const void tree::print_tree(bool need_graphviz_dump) const
{
	if(need_graphviz_dump)
	{
        graphviz_dump("dump.dot");

        system("iconv.exe -t UTF-8 -f  CP1251 < dump.dot > dump_temp.dot");
        system("dot dump_temp.dot -Tpdf -o dump.pdf");
        system("del dump.dot");
        system("ren dump_temp.dot dump.dot");

        system("dump.pdf");

    // or   system("dot dump.dot -Tpng -o dump_list.png"); // if u want [.png] format
	}

	size_t counter = 0;

    //const tree_element* tmp = get_start();

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

    //size_t counter = 1;
    tree_element* tmp = root_;

	print_all_elements(tmp, dump);
    fprintf(dump, "}\n");

    fclose(dump);
    return;
}
