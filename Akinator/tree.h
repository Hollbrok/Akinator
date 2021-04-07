#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <TXLib.h>

using data_type = char*;
#define POISON nullptr

class tree_element
{
private:

	data_type 	  data_ = 0;

	tree_element* prev_ = nullptr;

	tree_element* left_  = nullptr;
	tree_element* right_ = nullptr;

public:

    tree_element(data_type data = 0, tree_element* prev = nullptr,
                tree_element* left = nullptr, tree_element* right = nullptr);
	//tree_element(data_type data = 0, tree_element* next = nullptr, tree_element* prev = nullptr);
	~tree_element();

//! SETTERS

	void set_data(data_type new_data) {data_ = new_data;};

	void set_left(tree_element* new_left) {left_ = new_left;};
	void set_right(tree_element* new_right) {right_ = new_right;};

	void set_prev(tree_element* new_prev) {prev_ = new_prev;};


//! GETTERS

	const data_type& get_data()     const {assert(this && "You passed nullptr to get_data()"); return data_;};

	const tree_element* get_left()  const {assert(this && "nullptr tree_element in get_next()"); return left_;};
	const tree_element* get_right() const {assert(this && "nullptr tree_element in get_next()"); return right_;};
	const tree_element* get_prev()  const {assert(this && "nullptr tree_element in get_prev()"); return prev_;};

//! NON_CONST GETTERS

 	data_type& non_const_get_data() {assert(this && "You passed nullptr to get_data()"); return data_;};

    data_type& get_data() {assert(this && "You passed nullptr to get_data()"); return data_;};

    tree_element* get_left()  {assert(this && "nullptr tree_element in get_next()"); return left_;};
	tree_element* get_right() {assert(this && "nullptr tree_element in get_next()"); return right_;};
	tree_element* get_prev()  {assert(this && "nullptr tree_element in get_prev()"); return prev_;};


};

class tree:tree_element
{
private:

	size_t cur_size_ 	= 0;
	size_t error_state_ = 0;
	const char* name_ 	= nullptr;

	tree_element* root_  = nullptr;


//! PRIVATE SETTERS

    // set_root(tree_element* new_root) {assert(new_root && "You passed nullptr new_root"); root_ = new_root;};
	// i do'nt need this function cause i can just use root_ = something ..


public:
	tree(const char* name);
	~tree();

//! SETTERS

	//set_root(tree_element* new_root) {assert(new_root && "You passed nullptr new_root"); root_ = new_root;};
	// Neew to change left and right elements;

// * MAIN SETTERS

	tree_element* add_to_right(tree_element* x, data_type number);
	tree_element* add_to_left(tree_element* x, data_type number);



    void fill_tree(FILE* database);

//! GETTERS

	tree_element* get_root() {return root_;};

// * MAIN GETTERS

	const void print_tree(bool need_graphviz_dump = false)
									const;
	const void graphviz_dump(char* dumpfile_name = "dump.dot")
						 			const;

	//const tree_element* get_root() const {return root_;};

};

void free_all(tree_element* root);
void print_all_elements(tree_element* tmp, FILE* dump);


#endif // TREE_H_INCLUDED
