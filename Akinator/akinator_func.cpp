#include "akinator.h"

const int LT_BUT_POSITION = 265;
const int LB_BUT_POSITION = 550;

const int X_BUT_SIZE = 250;
const int Y_BUT_SIZE = 100;

#pragma warning(disable : 4996)

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

using namespace sf;
void tree::graphic_play()
{
	assert(this);

	const char* name_of_file = "database.txt";
	fill_tree(name_of_file);

	//printf("Updating data base..\n");

	// Устанавливаем 8-й уровень сглаживания
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	bool DRAW_BUTTON = true;
	bool NEED_MENU = false;
	bool REGIME_1 = false;
	bool FIND_WORD = false;
	bool NEED_UPDATE = false;
	bool WAIT_WORD = false;
	bool WORD_DONE = false;
	bool NEED_QUESTION = false;
	bool QUESTION_DONE = false;
	bool NEED_UPDATE_BASE = false;

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 939), "Akinator", Style::Default, settings);


	// Создаем переменную текстуры
	Texture texture;

	texture.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/backgraund.jpg");

	// Создаем спрайт и устанавливаем ему нашу текстуру
	Sprite sprite(texture);

	// Устанавливаем ему цвет - зеленый
	sprite.setColor(Color::Green);

	// Создаем прямоугольник размером 
	RectangleShape rectangle(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// Перемещаем его в нужное место
	rectangle.move(LT_BUT_POSITION, LB_BUT_POSITION);

	// Устанавливаем ему цвет
	rectangle.setFillColor(Color(175, 180, 240));

	// Создаем прямоугольник размером 
	//RectangleShape rectangle2(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));


	Font font;
	font.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/CyrilicOld.TTF");

	Text text("", font, 50);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	text.setString("Играть");
	text.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10);

	Text exit_but("", font, 50);
	exit_but.setColor(Color::Magenta);
	exit_but.setStyle(Text::Bold);

	exit_but.setString("Выйти");
	exit_but.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10 + Y_BUT_SIZE + 10);


	Text regime1("", font, 50);
	regime1.setColor(Color::Blue);
	regime1.setStyle(Text::Bold);

	regime1.setString("Угадайка");
	regime1.setPosition(120, 350);


	Text yes_text("Да", font, 50);
	yes_text.setColor(Color::Green);
	yes_text.setStyle(Text::Bold);

	//	yes_text.setString("Да");
	yes_text.setPosition(180, 450);

	Text no_text("Нет", font, 50);
	no_text.setColor(Color::Red);
	no_text.setStyle(Text::Bold);

	//	yes_text.setString("Да");
	no_text.setPosition(170 + X_BUT_SIZE + 100, 450);


	RectangleShape yes_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// Перемещаем его в нужное место
	yes_rect.move(100, 440);

	// Устанавливаем ему цвет
	yes_rect.setFillColor(Color(175, 180, 240));


	RectangleShape no_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// Перемещаем его в нужное место
	no_rect.move(100 + X_BUT_SIZE + 100, 440);

	// Устанавливаем ему цвет
	no_rect.setFillColor(Color(175, 180, 240));


	RectangleShape reg1_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// Перемещаем его в нужное место
	reg1_rect.move(100, 340);

	// Устанавливаем ему цвет
	reg1_rect.setFillColor(Color(175, 180, 240));

	RectangleShape exit_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// Перемещаем его в нужное место
	exit_rect.move(LT_BUT_POSITION, LB_BUT_POSITION + Y_BUT_SIZE + 10);

	// Устанавливаем ему цвет
	exit_rect.setFillColor(Color(175, 180, 240));

	Vector2i pos;
	int x;
	int y;

	tree_element* tmp_root = new tree_element;

	tmp_root = root_;

	//printf("root_ = %p\nleft = %p\n,right = %p\n", root_, root_->get_left(), root_->get_right());

	//tree_element* copy_of_root = new tree_element;
	//printf("root_ = %p\n", root_);

	//copy_of_root = root_;
	//printf("copy_of_root = %p\n", copy_of_root);

	//printf("before dump\n");
	//graphviz_dump();
	//printf("after dump\n");

	char question[100];
	// Главный цикл приложения. Выполняется, пока открыто окно
	char user_word[100];
	int cur_size = 0;

	char user_question[100];
	int cur_size_q = 0;

	while (window.isOpen())
	{

		// Получаем координаты курсора мышки относительно окна нашего приложения
		pos = Mouse::getPosition(window);
		x = pos.x;
		y = pos.y;

		// Обрабатываем очередь событий в цикле
		Event event;

		while (window.pollEvent(event))
		{

			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
		

			// Определяем, была ли нажата кнопка мыши?
			if (event.type == Event::MouseButtonPressed)
			{
				// Если была нажата левая кнопка мыши, то открываем клетку
				if (event.key.code == Mouse::Left)
				{
					//printf("x = %d,y = %d\n LT_BUT_POSITION = %d, LB_BUT_POSITION = %d\n", x, y, LT_BUT_POSITION, LB_BUT_POSITION);
					if (DRAW_BUTTON)
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
						{
							if ((LB_BUT_POSITION <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE))
							{
								//printf("ok\n");
								text.setColor(Color::Green);
								window.draw(text);

								DRAW_BUTTON = false;
								NEED_MENU = true;

								text.setColor(Color::Black);
								text.setString("Выберите режим игры:");

								text.move(-170, -330);

								// Перемещаем его в нужное место
								rectangle.move(-170, -330);

								// Устанавливаем ему цвет
								rectangle.setSize(sf::Vector2f(600, 100));
								rectangle.setFillColor(Color(175, 180, 240));
							}
							else if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
								window.close();
						}
					}
					else if (REGIME_1)
					{
						//printf("REGIME!!!!!!!\n");
						if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
						{
							if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
								window.close();
						}
						else
						{
							//printf("x = %d\ny = %d\n", x, y);
							if ((440 <= y) && (y <= 440 + Y_BUT_SIZE))
							{

								if ((100 + X_BUT_SIZE + 100 <= x) && (x <= 100 + X_BUT_SIZE + 100 + X_BUT_SIZE))
								{
									if (tmp_root->get_left())
									{
										tmp_root = tmp_root->get_left();
										strncpy(question, tmp_root->data_, tmp_root->length_);

										question[tmp_root->length_] = '?';
										question[tmp_root->length_ + 1] = '\0';


										text.setString(question);
									}
									else
									{
										FIND_WORD = true;
										tmp_root->set_left(nullptr);
										tmp_root->set_right(nullptr);
										//tmp_root = tmp_root->get_left();
										//strncpy(question, tmp_root->data_, tmp_root->length_);
										//question[tmp_root->length_] = '\0';
										text.move(100, 0);
										text.setString("Какой был предмет?");
										WAIT_WORD = true;
										REGIME_1 = false;

										NEED_UPDATE = true;
									}

									//printf("NO BUTTON\n");
								}
								else if ((100 <= x) && (x <= 350))
								{
									if (tmp_root->get_right())
									{
										//printf("tmp_root = %p\nright = %p\nleft = %p\n", tmp_root, tmp_root->get_right(), tmp_root->get_left());

										tmp_root = tmp_root->get_right();

										//printf("tmp_root = %p\nright = %p\nleft = %p\n", tmp_root->get_prev(), (tmp_root->get_prev())->get_right(), (tmp_root->get_prev())->get_left());

										strncpy(question, tmp_root->data_, tmp_root->length_);
										
										question[tmp_root->length_] = '?';
										question[tmp_root->length_ + 1] = '\0';

										text.setString(question);

									//	(tmp_root->get_prev())->set_right(tmp_root) = tmp_root;
									//	(tmp_root->get_prev())->set_left((tmp_root->get_prev())->get_left());
									//	tmp_root->set_prev(tmp_root);
									}
									else
									{
										FIND_WORD = true;
										tmp_root->set_left(nullptr);
										tmp_root->set_right(nullptr);
										//tmp_root = tmp_root->get_left();
										//strncpy(question, tmp_root->data_, tmp_root->length_);
										//question[tmp_root->length_] = '\0';
										text.move(125, 0);
										text.setString("УРА");
										REGIME_1 = false;
									}

									//printf("YES BUTTON\n");
								}
							}
						}
						//graphviz_dump();
					}
					else
					{
						if ((100 <= x) && (x <= 100 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_1 = true;

								//char* question = new char[tmp_root->length_];
								strncpy(question, root_->data_, root_->length_);
								question[root_->length_] = '?';
								question[root_->length_ + 1] = '\0';


								text.setCharacterSize(30);
								text.setString(question);
							}
						}
						else if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
							window.close();
					}

				}
			}

			if (WAIT_WORD)
				if (event.type == sf::Event::KeyPressed)
				{
					//printf("%d\n", static_cast<char>(event.text.unicode));
					if (static_cast<char>(event.text.unicode) == 58)
					{
						//printf("Enter \n");
						WAIT_WORD = false;
						WORD_DONE = true;
						user_word[cur_size] = '\0';
					}
					else
					{
						if (event.key.code == Keyboard::Q) user_word[cur_size++] = 'й';
						else if (event.key.code == Keyboard::W) user_word[cur_size++] = 'ц';
						else if (event.key.code == Keyboard::E) user_word[cur_size++] = 'у';
						else if (event.key.code == Keyboard::R) user_word[cur_size++] = 'к';
						else if (event.key.code == Keyboard::T) user_word[cur_size++] = 'е';
						else if (event.key.code == Keyboard::Y) user_word[cur_size++] = 'н';
						else if (event.key.code == Keyboard::U) user_word[cur_size++] = 'г';
						else if (event.key.code == Keyboard::I) user_word[cur_size++] = 'ш';
						else if (event.key.code == Keyboard::O) user_word[cur_size++] = 'щ';
						else if (event.key.code == Keyboard::P) user_word[cur_size++] = 'з';
						else if (event.key.code == Keyboard::LBracket) user_word[cur_size++] = 'х';
						else if (event.key.code == Keyboard::RBracket) user_word[cur_size++] = 'ъ';
						else if (event.key.code == Keyboard::A) user_word[cur_size++] = 'ф';
						else if (event.key.code == Keyboard::S) user_word[cur_size++] = 'ы';
						else if (event.key.code == Keyboard::D) user_word[cur_size++] = 'в';
						else if (event.key.code == Keyboard::F) user_word[cur_size++] = 'а';
						else if (event.key.code == Keyboard::G) user_word[cur_size++] = 'п';
						else if (event.key.code == Keyboard::H) user_word[cur_size++] = 'р';
						else if (event.key.code == Keyboard::J) user_word[cur_size++] = 'о';
						else if (event.key.code == Keyboard::K) user_word[cur_size++] = 'л';
						else if (event.key.code == Keyboard::L) user_word[cur_size++] = 'д';
						else if (event.key.code == Keyboard::Semicolon) user_word[cur_size++] = 'ж';
						else if (event.key.code == Keyboard::Hyphen) user_word[cur_size++] = '-';
						else if (event.key.code == Keyboard::Comma) user_word[cur_size++] = 'б';
						else if (event.key.code == Keyboard::Period) user_word[cur_size++] = 'ю';
						else if (event.key.code == Keyboard::Quote) user_word[cur_size++] = 'э';
						else if (event.key.code == Keyboard::Z) user_word[cur_size++] = 'я';
						else if (event.key.code == Keyboard::X) user_word[cur_size++] = 'ч';
						else if (event.key.code == Keyboard::C) user_word[cur_size++] = 'с';
						else if (event.key.code == Keyboard::V) user_word[cur_size++] = 'м';
						else if (event.key.code == Keyboard::B) user_word[cur_size++] = 'и';
						else if (event.key.code == Keyboard::N) user_word[cur_size++] = 'т';
						else if (event.key.code == Keyboard::M) user_word[cur_size++] = 'ь';
						else if (event.key.code == Keyboard::Q) user_word[cur_size++] = 'й';
						else if (event.key.code == Keyboard::Space) user_word[cur_size++] = ' ';
					}

				}
			if (NEED_QUESTION)
				if (event.type == sf::Event::KeyPressed)
				{
					//printf("%d\n", static_cast<char>(event.text.unicode));
					if (static_cast<char>(event.text.unicode) == 58)
					{
						//printf("Enter \n");
						NEED_QUESTION = false;
						QUESTION_DONE = true;
						user_question[cur_size_q] = '\0';
					}
					else
					{
						if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = 'й';
						else if (event.key.code == Keyboard::W) user_question[cur_size_q++] = 'ц';
						else if (event.key.code == Keyboard::Space) user_question[cur_size_q++] = ' ';
						else if (event.key.code == Keyboard::E) user_question[cur_size_q++] = 'у';
						else if (event.key.code == Keyboard::R) user_question[cur_size_q++] = 'к';
						else if (event.key.code == Keyboard::T) user_question[cur_size_q++] = 'е';
						else if (event.key.code == Keyboard::Y) user_question[cur_size_q++] = 'н';
						else if (event.key.code == Keyboard::U) user_question[cur_size_q++] = 'г';
						else if (event.key.code == Keyboard::I) user_question[cur_size_q++] = 'ш';
						else if (event.key.code == Keyboard::O) user_question[cur_size_q++] = 'щ';
						else if (event.key.code == Keyboard::P) user_question[cur_size_q++] = 'з';
						else if (event.key.code == Keyboard::LBracket) user_question[cur_size_q++] = 'х';
						else if (event.key.code == Keyboard::RBracket) user_question[cur_size_q++] = 'ъ';
						else if (event.key.code == Keyboard::A) user_question[cur_size_q++] = 'ф';
						else if (event.key.code == Keyboard::S) user_question[cur_size_q++] = 'ы';
						else if (event.key.code == Keyboard::D) user_question[cur_size_q++] = 'в';
						else if (event.key.code == Keyboard::F) user_question[cur_size_q++] = 'а';
						else if (event.key.code == Keyboard::G) user_question[cur_size_q++] = 'п';
						else if (event.key.code == Keyboard::H) user_question[cur_size_q++] = 'р';
						else if (event.key.code == Keyboard::J) user_question[cur_size_q++] = 'о';
						else if (event.key.code == Keyboard::K) user_question[cur_size_q++] = 'л';
						else if (event.key.code == Keyboard::L) user_question[cur_size_q++] = 'д';
						else if (event.key.code == Keyboard::Semicolon) user_question[cur_size_q++] = 'ж';
						else if (event.key.code == Keyboard::Hyphen) user_question[cur_size_q++] = '-';
						else if (event.key.code == Keyboard::Comma) user_question[cur_size_q++] = 'б';
						else if (event.key.code == Keyboard::Period) user_question[cur_size_q++] = 'ю';
						else if (event.key.code == Keyboard::Quote) user_question[cur_size_q++] = 'э';
						else if (event.key.code == Keyboard::Z) user_question[cur_size_q++] = 'я';
						else if (event.key.code == Keyboard::X) user_question[cur_size_q++] = 'ч';
						else if (event.key.code == Keyboard::C) user_question[cur_size_q++] = 'с';
						else if (event.key.code == Keyboard::V) user_question[cur_size_q++] = 'м';
						else if (event.key.code == Keyboard::B) user_question[cur_size_q++] = 'и';
						else if (event.key.code == Keyboard::N) user_question[cur_size_q++] = 'т';
						else if (event.key.code == Keyboard::M) user_question[cur_size_q++] = 'ь';
						else if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = 'й';
					}

				}

		}
		// Установка цвета фона - белый
		window.clear(Color::White);


		// Отрисовка фона
		window.draw(sprite);

		// Отрисовка кнопки play
		window.draw(rectangle);

		/*printf("DRAW_BUTTON = %d\n"
				"NEED_MENU = %d\n"
				" FIND_WORD = %d\n"
				" REGIME_1 = %d\n"
				" WORD_DONE = %d\n", DRAW_BUTTON, NEED_MENU, FIND_WORD, REGIME_1, WORD_DONE);
				*/
		if (DRAW_BUTTON)
			window.draw(text);
		else if (NEED_MENU)
		{
			//printf("NEEW_MENU\n");
			window.draw(text);

			window.draw(reg1_rect);
			window.draw(regime1);

		}
		else if (FIND_WORD)
		{
			window.draw(text);
		}
		else if (REGIME_1)
		{
			//printf("REGIME_1 yes_no\n");
			window.draw(text);
			//delete[] question;

			window.draw(yes_rect);
			window.draw(no_rect);

			window.draw(yes_text);
			window.draw(no_text);

		}

		if (WORD_DONE)
		{
			//printf(" word done\n");
			printf("[%s]\n", user_word);
			WORD_DONE = false;
			NEED_QUESTION = true;
			text.move(-100, 0);
			text.setString("Чем ваш предмет отличается от моего?");
		}
		if (QUESTION_DONE)
		{

			printf("[%s]\n", user_question);
			QUESTION_DONE = false;
			NEED_UPDATE_BASE = true;
			text.move(75, 0);
			text.setString("Спасибо большое за игру!");
		}

		if (NEED_QUESTION)
		{
			window.draw(text);
		}
		// EXIT BUTTON
		window.draw(exit_rect);
		window.draw(exit_but);


		// Отрисовка окна
		window.display();
	}
	
	//printf("tmp_root = %p\n"	
	//		"prev = %p\n", tmp_root, tmp_root->get_prev());
	//delete tmp_root;

	//printf("root_ = %p\n"
	//		"left = %p\n,right = %p\n", root_, root_->get_left(), root_->get_right());

	if (NEED_UPDATE_BASE)
	{
		//printf("aaa");
		tree_element* user_element = new tree_element;
		assert(user_element);
		//printf("length = %d\n", strlen(user_word));
		char* new_data = new char[strlen(user_word)];
		strncpy(new_data, user_word, strlen(user_word));
		//new_data[strlen(user_word)] = '\0';
		//printf("strlen new data = %d\n", strlen(new_data));
		//printf("strlen user_word = %d\n", strlen(user_word));
		//printf("cur size = %d\n", cur_size);

		user_element->data_ = new_data;
		user_element->user_length_ = strlen(user_word);
		user_element->length_ = user_element->user_length_;
		//printf("user_elemen length = %d\n", user_element->length_);

		//printf("Ваш предмет [%s]\n", new_data);

		// USER WORD   -- TRUE   -- RIGHT RIGHT

		//printf("\t\tА теперь какое-нибудь его свойство, которого нет в моем слове\n:");

		tree_element* user_attribute = new tree_element;
		assert(user_attribute);


		//printf("length = %d\n", strlen(user_question));

		char* new_question = new char[strlen(user_question)];
		strncpy(new_question, user_question, strlen(user_question));
		//new_question[strlen(user_question)] = '\0';


		user_attribute->data_ = new_question;
		user_attribute->user_length_ = strlen(user_question);
		user_attribute->length_ = user_attribute->user_length_;
		//printf("user_att length = %d\n", user_attribute->length_);
		//printf("Ваш вопрос [%s]\n", new_question);


		user_element->set_prev(user_attribute);

		//ATTRIBUTE OF USER WORD

		user_attribute->set_right(user_element);
		user_attribute->set_left(tmp_root);

		if ((tmp_root->get_prev())->get_right() == tmp_root)
			(tmp_root->get_prev())->set_right(user_attribute);
		else if ((tmp_root->get_prev())->get_left() == tmp_root)
			(tmp_root->get_prev())->set_left(user_attribute);
		else
			printf("Something bad..");

		user_attribute->set_prev(tmp_root->get_prev());
		tmp_root->set_prev(user_attribute);
	}

	const char* name_of_new_base = "database.txt";
	update_database(name_of_new_base);
	printf("Done!\n");

	return;
}