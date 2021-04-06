#include "akinator.h"

tree_element::tree_element(data_type data, tree_element* next, tree_element* prev) :
	data_(data),
	next_(next),
	prev_(prev)
{
	//printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to list_elem construct");
}

tree_element::~tree_element()
{
	assert(this && "You passed nullptr to ~tree_element");
	//printf("in %s\n", __PRETTY_FUNCTION__);
	free(next_);
	next_ = nullptr;
	free(prev_);
	prev_ = nullptr;
	data_ = POISON;
}

tree_element* list::set_element_from_end(data_type number)
{
	assert(!isnan(number) && "number is nan");
	assert(this && "You passed nullptr to set_element_from_end");

	tree_element* tmp = (tree_element*) calloc (1, sizeof(tree_element));

	if((start_ == nullptr) && (end_ == nullptr))  // cur_size_ == 0
	{
		tmp->set_data(number);
		tmp->set_next(nullptr);
		tmp->set_prev(nullptr);

		set_start(tmp);
		set_end(tmp);
	}
	else
	{
		tmp->set_data(number);
		tmp->set_prev(get_end());
		tmp->set_next(nullptr);

		(get_end())->set_next(tmp);

		set_end(tmp);
	}

	cur_size_++;

	return tmp;
}

tree_element* list::set_element_to_start(data_type number)
{
	assert(!isnan(number) && "number is nan");
	assert(this && "You passed nullptr to set_element_from_start");

	tree_element* tmp = (tree_element*) calloc (1, sizeof(tree_element));

	if((start_ == nullptr) && (end_ == nullptr))  // cur_size_ == 0
	{
		tmp->set_data(number);
		tmp->set_next(nullptr);
		tmp->set_prev(nullptr);

		set_start(tmp);
		set_end(tmp);
	}
	else
	{
		tmp->set_data(number);
		tmp->set_prev(nullptr);
		tmp->set_next(get_start());

		(get_start())->set_prev(tmp);

		set_start(tmp);
	}

	cur_size_++;

	return tmp;
}

tree_element* list::set_element_prev_to_x(tree_element* x, data_type number)
{
	assert(this && "You passed nullptr list to set_element_prev_to_x");
	assert(x && "You passed nullptr x element");

	tree_element* tmp = (tree_element*) calloc(1, sizeof(tree_element));

	if(is_start(x))
	{
		set_start(tmp);

		x->set_prev(tmp);
		tmp->set_next(x);

		tmp->set_data(number);
	}
	else
	{
		(x->get_prev())->set_next(tmp);

		tmp->set_next(x);
		tmp->set_prev(x->get_prev());
		tmp->set_data(number);
	}

	cur_size_++;

	return tmp;
}

