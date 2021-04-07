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

void tree::fill_tree(FILE* database) // сделать имя файла, а не file
{
    assert(database && "You need to pass database");
    return;
}

