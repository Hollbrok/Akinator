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
    else if(cur_size_ && tmp)
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
        //printf("set data [%s]\n", number);
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

const void tree::fill_tree(char* name_file)
{
	assert(this && "you passed nullptr to fill_tree");
	assert(name_file && "U need to pas FILE* database");

	char* buffer = make_buffer(name_file);
    char* copy_of_buffer = buffer;

	//printf("%s\n", buffer);

    while (*buffer != '[');
        buffer++;

    root_ = fill_root(buffer);
    printf("GOGOOGOGOGOG\n");

    free(copy_of_buffer);
	return;
}

tree_element* tree::fill_root(char* buffer)
{
    //printf("buffer in fill_root:\n%s\n", buffer);
    //printf("in fill_root\n");
    while(isspace(*buffer))
        buffer++;

    if (*buffer == '[')
        buffer++;

    while(isspace(*buffer))
        buffer++;

    tree_element* tmp_element = (tree_element*) calloc(1, sizeof(tree_element));
    assert(tmp_element && "Can't calloc mempry for tmp");

    if((*buffer == '`') || (*buffer == '?'))
    {
        buffer++;

        int lenght = 0;
        while((*buffer != '?') && (*buffer != '`'))
        {
            lenght++;
            buffer++;
        }

        buffer = buffer - lenght;
        tmp_element->data_ = (char*) calloc(lenght, sizeof(char));

        strncpy(tmp_element->data_, buffer, lenght);

        buffer = buffer + lenght;

        tmp_element->set_left(nullptr);//left_ = nullptr;
        tmp_element->set_right(nullptr);//right_ = nullptr;
        tmp_element->set_prev(nullptr);//prev_ = nullptr;

        while(isspace(*buffer))
            buffer++;

        //printf("buffer = *%s*\n", buffer);

        if(*buffer == '?')
        {
            //printf("find ?\n");
            buffer++;
            //printf("BUFFERBUFFER = %c", *buffer);
            tmp_element->set_right(fill_root(&buffer));//left_ = fill_root(char* buffer)
            //printf("BUFFERBUFFER = %c\n", *buffer);
            tmp_element->set_left(fill_root(&buffer));//right_ = fill_root(char* buffer)
        }
        //free(tmp_element);
    }
    buffer++;
    while(isspace(*buffer))
        buffer++;
    //printf("buffer after:\n%s\n", buffer);
    if (*buffer == ']')
    {
        buffer++;
        //printf("return\n");
        return tmp_element;
    }
    else
        printf("Something bad..\n");
}

tree_element* tree::fill_root(char** buffer)
{
    //assert(root && "root is nullptr");
    //rintf("buffer in fill_root:\n%s\n", buffer);
    //printf("in fill_root\n");
    while(isspace(**buffer))
        (*buffer)++;

    if (**buffer == '[')
       (*buffer)++;

    while(isspace(**buffer))
        (*buffer)++;

    //printf("buffer 10 strings after:\n%s\n", buffer);
    //printf("in fill_root\n");

    tree_element* tmp_element = (tree_element*) calloc(1, sizeof(tree_element));
    assert(tmp_element && "Can't calloc mempry for tmp");

    if((**buffer == '`') || (**buffer == '?'))
    {

        //printf("Find ' or ?\n");
        (*buffer)++;
        //printf("buffer after ? or ':\n*%s*\n", buffer);
        //printf("in fill_root\n");
        //char* tmp_data = (char*) calloc(MAX_QUESTION_SIZE, sizeof(char));
        //assert(tmp_data && "Can't calloc memory for tmp_data");

        int lenght = 0;
        while((**buffer != '?') && (**buffer != '`'))
        {
            //printf("lenght++\n");
            lenght++;
            (*buffer)++;
        }
        // BUFFER - lenght
        *buffer = (*buffer) - lenght;
        tmp_element->data_ = (char*) calloc(lenght, sizeof(char));

        strncpy(tmp_element->data_, *buffer, lenght); // in tmp_data 'INFORMATION'

        *buffer = (*buffer) + lenght;
        //printf("after strncpy\n");
        //printf("tmp_element->data_ = [%s]\n", tmp_element->data_);
        //tmp_element->set_data(tmp_data);// = tmp_data;


        tmp_element->set_left(nullptr);//left_ = nullptr;
        tmp_element->set_right(nullptr);//right_ = nullptr;
        tmp_element->set_prev(nullptr);//prev_ = nullptr;

        while(isspace(**buffer))
            (*buffer)++;

        //printf("buffer = *%s*\n", *buffer);

        if(**buffer == '?')
        {
            //printf("find ?\n");
            (*buffer)++;
            //printf("BUFFERBUFFER = %c", **buffer);
            tmp_element->set_left(fill_root(buffer));//left_ = fill_root(char* buffer)
            //printf("BUFFERBUFFER = %c\n", **buffer);
            tmp_element->set_right(fill_root(buffer));//right_ = fill_root(char* buffer)
        }
        //free(tmp_element);
    }
    (*buffer)++;
    while(isspace(**buffer))
        (*buffer)++;
    //printf("buffer after:\n%s\n", buffer);
    if (**buffer == ']')
    {
        (*buffer)++;
        //printf("return\n");
        return tmp_element;
    }
    else
        printf("Something bad..\n");
}

char* make_buffer(char* name_file)
{
    FILE* database = fopen(name_file, "rb");
	assert(database && "Can't open database.txt");

    long file_length = size_of_file(database);

	char* buffer = (char*) calloc(file_length, sizeof(char));
	assert(buffer && "Can't calloc memory for buffer");

	fread  (buffer, sizeof(char), file_length, database);
	return buffer;
}

