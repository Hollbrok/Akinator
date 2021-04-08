#include "tree.h"

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
	data_(data),
	prev_(prev),
	left_(left),
	right_(right)
{
	//printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to list_elem construct");
}

tree_element::~tree_element()
{
	assert(this && "You passed nullptr to ~tree_element");
    //printf("in %s\n", __PRETTY_FUNCTION__);
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
    //printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to constructor");
	assert(name && "You need to pass name");
}

tree::~tree()
{
    //printf("in %s\n", __PRETTY_FUNCTION__);
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


    //printf("Calloc\n");
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

    tree_element* root = root_;
    build_prev_connections(root);



    //printf("root = %d\n", root_);

    free(copy_of_buffer);
	return;
}

void tree_element::build_prev_connections(tree_element* root)
{
    assert(root);

    /*if((root->get_right() == nullptr) || (root->get_left() == nullptr))
        return root;
    if(root->get_right() == nullptr)
        root->set_right(build_prev_connection(root->get_right));
    if(root->get_left() == nullptr)
        root->set_left*/
    if(root->get_right())
    {
        if( ((root->get_right())->get_left() == nullptr) && ((root->get_right())->get_right() == nullptr) )
            (root->get_right())->set_prev(root);
        else
        {
            (root->get_right())->set_prev(root);
            build_prev_connections(root->get_right());
        }
    }
    if(root->get_left())
    {
        if( ((root->get_left())->get_left() == nullptr) && ((root->get_left())->get_right() == nullptr) )
            (root->get_left())->set_prev(root);
        else
        {
            (root->get_left())->set_prev(root);
            build_prev_connections(root->get_left());
        }
    }
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

        if(*buffer == '?')    // if first if was called by '?'
        {
            //printf("find ?\n");
            buffer++;
            //printf("BUFFERBUFFER = %c", *buffer);
            tmp_element->set_left(fill_root(&buffer));//left_ = fill_root(char* buffer)
            //printf("BUFFERBUFFER = %c\n", *buffer);
            tmp_element->set_right(fill_root(&buffer));//right_ = fill_root(char* buffer)
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

const void tree::play()
{
    assert(this && "You passed nullptr yo play()");

    print_hello();
    fill_tree();

    switch(get_number_of_game())
    {
        case 1:
            //printf("Вы выбрали режим 1\n");
            play_1();
            break;
        case 2:
            break;
        case 3:
            break;

        default:
            printf("Not indentified number of regime\n");
            break;
    }

    print_tree(true);
    update_database();

    return;
}

int get_number_of_game()
{
    int number_of_game = 0;
    int number_of_scanf_digits = 0;

    char user_data[256] = {};

    //printf("Введите цифру режима игры: ");

    while(true)
    {
        printf("Введите цифру режима игры: ");
        gets(user_data);
        user_data[strlen(user_data)] = '\0';

        if(!isdigit(user_data[0]))
        {
            //printf("Пожалуйста, введите именно цифру: ");
            continue;
        }

        if(strlen(user_data) != 1)
        {
            fflush(stdin);
            //printf("Введите цифру (длина 1): ");
            continue;
        }

        number_of_game = atoi(user_data);

        if(!(0 < number_of_game) || !(number_of_game < 2))
        {
            //printf("Режим номер %d не существует, выберите другой: ", number_of_game);
            //gets(user_data);
            continue;
        }
        break;
    }
    printf("\n\n");
    return number_of_game;
}

void print_hello()
{
    printf("\t\tПриветствую тебя.\nЧтобы сыграть можешь выбрать один в следующих режимов игры:\n");

    printf("\t1. Угадать загаданный предмет/героя\n");


    printf("\n");
    return;
}

const void tree::play_1()
{
    assert(this && "You passed nullptr tree to play_1");

    //tree_element* root = root_;
    //printf("root = %d\n", root_);

    if(root_)
    {
        printf("Правила игры:\n");
        printf("\t 1) Загадайте предмет\n");
        printf("\t 2) Я буду угадывать его\n");
        printf("\t 3) Если ваш да, то введите \"y\" \n");
        printf("\t 4) Если нет, то \"n\" \n\n\n");
        check_answer(root_);
    }
    else
        printf("Дерево не создано\n");

    return;
}

const void check_answer(tree_element* question)
{
    assert(question && "nullptr question in check_answer");

    if((question->get_left() == nullptr) && (question->get_right() == nullptr))
    {
        printf("\t\tКажется я нашел ваш предмет!\n");

        if(question->get_user_answer())
            printf("\t\tЯ так рад, что смог угадать твой предмет!!\n");

        else
        {
            printf("\t\tЖаль, что не удалось, но я\n\t\tпопробую угадать в следующий раз!\n");

            printf("\t\tМожешь ввести имя загаданного предмета?\n:");

            tree_element* user_element = (tree_element*) calloc(1, sizeof(tree_element));
            assert(user_element);
            user_element->set_data(get_data_from_user());
            printf("Ваш предмет [%s]\n", user_element->non_const_get_data());

     // USER WORD   -- TRUE   -- RIGHT RIGHT

            printf("\t\tА теперь какое-нибудь его свойство, которого нет в моем слове\n:");

            tree_element* user_attribute = (tree_element*) calloc(1, sizeof(tree_element));
            assert(user_attribute);
            user_attribute->set_data(get_data_from_user());
            printf("Ваш вопрос [%s]\n", user_attribute->non_const_get_data());


            user_element->set_prev(user_attribute);
     //ATTRIBUTE OF USER WORD

            user_attribute->set_right(user_element);
            user_attribute->set_left(question);

            if((question->get_prev())->get_right() == question)
                (question->get_prev())->set_right(user_attribute);
            else if((question->get_prev())->get_left() == question)
                (question->get_prev())->set_left(user_attribute);
            else
                printf("Something bad..");

            user_attribute->set_prev(question->get_prev());
            question->set_prev(user_attribute);




            //get_data_from_user()
        }

        // bool
        //verify_user_answer();
    }
    else if(question->get_user_answer())
    {
        //printf("Ваш ответ да\n");
        check_answer(question->get_right());
    }
    else
    {   // user answered no
        //printf("Ваш ответ нет\n");
        check_answer(question->get_left());
    }
    return;
}

bool tree_element::get_user_answer()
{
//printf("Мне нужно знать\n");
    printf("\t\t%s?\n", non_const_get_data());
    char user_data[256] = {};

    while(true)
    {
        //printf("Обладает ли этот предмет этим свойством?: ");
        gets(user_data);
        if(strlen(user_data) != 1)
        {
            printf("Нет такого варианта ответа\n");
            fflush(stdin);
            continue;
        }
        if((user_data[0] == 'y') || (user_data[0] == 'Y') || (user_data[0] == 'n') || (user_data[0] == 'N'))
            break;

        printf("Нет такого варианта ответа\n");
        fflush(stdin);
        continue;
    }
    return ((user_data[0] == 'Y') || (user_data[0] == 'y'));
}

char* get_data_from_user()
{
    //calloc
    char* user_data = (char*) calloc(256, sizeof(char));

    gets(user_data);

    return user_data;
}

const void tree::update_database(char* name_file)
{
    assert(name_file && "no file name");
    assert(this && "nullptr tree in update_database");

    FILE* database = fopen(name_file, "wb");
    assert(database && "Can't open file to update database");

    print_elem(root_, database);

    return;
}

void tree_element::print_elem(tree_element* root, FILE* database)
{
    //printf("in print_elem\n");
    assert(root);
    assert(database);
    assert(this);

    fprintf(database, "[\n");

    if(root->get_left())
    {
        //printf("If no\n ?%s? \n", root->non_const_get_data());
        fprintf(database, "?%s?\n", root->non_const_get_data());
        print_elem(root->get_left(), database);
    }

    if(root->get_right())
    {
        //printf("If yes ?%s? \n", root->non_const_get_data());
        //fprintf(database, "?%s?\n", root->non_const_get_data());
        print_elem(root->get_right(), database);
    }

    if( (root->get_right() == nullptr) && (root->get_left() == nullptr) )
    {
        //printf("`%s`\n", root->non_const_get_data());
        fprintf(database, "`%s`\n", root->non_const_get_data());
    }

    /*if( (root->git_left() nullptr) && (root->git_right() == nullptr))
        fprintf(database, "`%s`\n", root->non_const_get_data());

    print_elem(root->get_left());
    print_elem(root->get_right());
      */

    fprintf(database, "]\n");
    //printf("return\n");
    return;
}
