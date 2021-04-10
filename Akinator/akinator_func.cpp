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
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp, tmp->get_right());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
	}
	if (tmp->get_left())
	{
		print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp, tmp->get_left());
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
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
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"��\", fontcolor=darkblue]\n", tmp, tmp->get_right());
	}
	if (tmp->get_left())
	{
		print_all_elements_beauty(tmp->get_left(), dump);
		fprintf(dump, "\"%p\" -> \"%p\" [label=\"���\", fontcolor=darkblue]\n", tmp, tmp->get_left());
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

	// ������������� 8-� ������� �����������
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
	bool REGIME_2 = false;
	bool WAIT_FOR_REGIME = true;
	bool PLAY_AGAIN = false;

	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(800, 939), "Akinator", Style::Default, settings);


	// ������� ���������� ��������
	Texture texture;

	texture.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/backgraund.jpg");

	// ������� ������ � ������������� ��� ���� ��������
	Sprite sprite(texture);

	// ������������� ��� ���� - �������
	sprite.setColor(Color::Green);

	// ������� ������������� �������� 
	RectangleShape rectangle(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	rectangle.move(LT_BUT_POSITION, LB_BUT_POSITION);

	// ������������� ��� ����
	rectangle.setFillColor(Color(175, 180, 240));

	// ������� ������������� �������� 
	//RectangleShape rectangle2(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));


	Font font;
	font.loadFromFile("C:/Users/Danik/Documents/Visual Studio 2019/Projects/Akinator/CyrilicOld.TTF");

	Text text("", font, 50);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold);

	text.setString("������");
	text.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10);

	Text exit_but("", font, 50);
	exit_but.setColor(Color::Magenta);
	exit_but.setStyle(Text::Bold);

	exit_but.setString("�����");
	exit_but.setPosition(LT_BUT_POSITION + 40, LB_BUT_POSITION + 10 + Y_BUT_SIZE + 10);


	Text regime1("", font, 50);
	regime1.setColor(Color::Blue);
	regime1.setStyle(Text::Bold);

	regime1.setString("��������");
	regime1.setPosition(120, 350);

	Text regime2("", font, 50);
	regime2.setColor(Color::Blue);
	regime2.setStyle(Text::Bold);

	regime2.setString("������");
	regime2.setPosition(120 + X_BUT_SIZE + 50, 350);

	RectangleShape reg2_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	reg2_rect.move(100 + X_BUT_SIZE + 50, 340);

	// ������������� ��� ����
	reg2_rect.setFillColor(Color(175, 180, 240));


	Text yes_text("��", font, 50);
	yes_text.setColor(Color::Green);
	yes_text.setStyle(Text::Bold);

	//	yes_text.setString("��");
	yes_text.setPosition(180, 450);

	Text no_text("���", font, 50);
	no_text.setColor(Color::Red);
	no_text.setStyle(Text::Bold);

	//	yes_text.setString("��");
	no_text.setPosition(170 + X_BUT_SIZE + 100, 450);


	RectangleShape yes_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	yes_rect.move(100, 440);

	// ������������� ��� ����
	yes_rect.setFillColor(Color(175, 180, 240));


	RectangleShape no_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	no_rect.move(100 + X_BUT_SIZE + 100, 440);

	// ������������� ��� ����
	no_rect.setFillColor(Color(175, 180, 240));


	RectangleShape reg1_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	reg1_rect.move(100, 340);

	// ������������� ��� ����
	reg1_rect.setFillColor(Color(175, 180, 240));


	RectangleShape exit_rect(Vector2f(X_BUT_SIZE, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	exit_rect.move(LT_BUT_POSITION, LB_BUT_POSITION + Y_BUT_SIZE + 10);

	// ������������� ��� ����
	exit_rect.setFillColor(Color(175, 180, 240));

	Vector2i pos;
	int x;
	int y;

	tree_element* tmp_root = new tree_element;

	tmp_root = root_;

	Text user_text("", font, 50);
	user_text.setColor(Color::Red);
	user_text.setStyle(Text::Bold);

	//text.setString("������");
	user_text.setPosition(150, 440);

	RectangleShape user_word_rect(Vector2f( 500, Y_BUT_SIZE));

	// ���������� ��� � ������ �����
	user_word_rect.move(150, 440);

	// ������������� ��� ����
	user_word_rect.setFillColor(Color(175, 180, 240));

	char question[100];
	// ������� ���� ����������. �����������, ���� ������� ����
	char user_word[100];
	int cur_size = 0;

	char user_question[100];
	int cur_size_q = 0;

	while (window.isOpen())
	{

		// �������� ���������� ������� ����� ������������ ���� ������ ����������
		pos = Mouse::getPosition(window);
		x = pos.x;
		y = pos.y;

		// ������������ ������� ������� � �����
		Event event;

		while (window.pollEvent(event))
		{

			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
		

			// ����������, ���� �� ������ ������ ����?
			if (event.type == Event::MouseButtonPressed)
			{
				// ���� ���� ������ ����� ������ ����, �� ��������� ������
				if (event.key.code == Mouse::Left)
				{
					//printf("x = %d,y = %d\n LT_BUT_POSITION = %d, LB_BUT_POSITION = %d\n", x, y, LT_BUT_POSITION, LB_BUT_POSITION);
					if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
							window.close();
					}
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
								text.setString("�������� ����� ����:");

								text.move(-170, -330);

								// ���������� ��� � ������ �����
								rectangle.move(-170, -330);

								// ������������� ��� ����
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
						if(true)
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
										text.setString("����� ��� �������?");
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
										text.setString("���");

										REGIME_1 = false;
										//PLAY_AGAIN = true;
									}

									//printf("YES BUTTON\n");
								}
							}
						}
						//graphviz_dump();
					}
					else if (NEED_MENU)
					{
						printf("in menu\n");
						printf("x = %d,  y = %d\n", x , y);
						if ((100 <= x) && (x <= 100 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								printf("REGIME_1\n");
								NEED_MENU = false;
								REGIME_1 = true;

								//char* question = new char[tmp_root->length_];
								strncpy(question, root_->data_, root_->length_);
								question[root_->length_] = '?';
								question[root_->length_ + 1] = '\0';


								text.setCharacterSize(30);
								text.setString(question);
							}
							//WAIT_FOR_REGIME = false;
						}
						else if ((100 + X_BUT_SIZE + 50 <= x) && (x <= 100 + X_BUT_SIZE + 50 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_2 = true;

								//char* question = new char[tmp_root->length_];
								//strncpy(question, root_->data_, root_->length_);
								//question[root_->length_] = '?';
								//question[root_->length_ + 1] = '\0';


								//text.setCharacterSize(30);
								//text.setString(question);
							}
							//WAIT_FOR_REGIME = false;
						}
					}
					if ((100 + X_BUT_SIZE + 50 <= x) && (x <= 100 + X_BUT_SIZE + 50 + X_BUT_SIZE))
						if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
							window.close();

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
						if (event.key.code == Keyboard::Q) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::W) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::E) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::R) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::T) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Y) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::U) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::I) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::O) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::P) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::LBracket) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::RBracket) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::A) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::S) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::D) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::F) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::G) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::H) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::J) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::K) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::L) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Semicolon) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Hyphen) user_word[cur_size++] = '-';
						else if (event.key.code == Keyboard::Comma) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Period) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Quote) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Z) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::X) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::C) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::V) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::B) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::N) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::M) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Q) user_word[cur_size++] = '�';
						else if (event.key.code == Keyboard::Space) user_word[cur_size++] = ' ';
						else if (event.key.code == Keyboard::BackSpace) {
							if (cur_size > 0)
								user_word[cur_size--] = '\0';
							else printf("cur_size == 0\n");
						}

						user_word[cur_size] = '\0';
						user_text.setString(user_word);
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
						if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::W) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Space) user_question[cur_size_q++] = ' ';
						else if (event.key.code == Keyboard::E) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::R) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::T) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Y) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::U) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::I) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::O) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::P) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::LBracket) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::RBracket) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::A) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::S) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::D) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::F) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::G) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::H) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::J) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::K) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::L) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Semicolon) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Hyphen) user_question[cur_size_q++] = '-';
						else if (event.key.code == Keyboard::Comma) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Period) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Quote) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Z) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::X) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::C) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::V) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::B) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::N) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::M) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::Q) user_question[cur_size_q++] = '�';
						else if (event.key.code == Keyboard::BackSpace) {
							if (cur_size_q > 0)
								user_question[cur_size_q--] = '\0';
							else printf("cur_size_q == 0\n");
						}

						user_question[cur_size_q] = '\0';
						user_text.setString(user_question);
					}

				}

		}
		// ��������� ����� ���� - �����
		window.clear(Color::White);


		// ��������� ����
		window.draw(sprite);

		// ��������� ������ play
		window.draw(rectangle);

		/*printf("DRAW_BUTTON = %d\n"
				"NEED_MENU = %d\n"
				" FIND_WORD = %d\n"
				" REGIME_1 = %d\n"
				" WORD_DONE = %d\n", DRAW_BUTTON, NEED_MENU, FIND_WORD, REGIME_1, WORD_DONE);
				*/
		if (PLAY_AGAIN)
		{
			
			window.draw(rectangle);
			window.draw(text);
		}
		if (DRAW_BUTTON)
			window.draw(text);
		else if (NEED_MENU)
		{
			//printf("NEEW_MENU\n");
			window.draw(text);

			window.draw(reg1_rect);
			window.draw(regime1);

			window.draw(reg2_rect);
			window.draw(regime2);

		}
		else if (FIND_WORD && !WAIT_WORD)
		{
			window.draw(text);
			//text.setString("�������� ����� ����:");
			//PLAY_AGAIN = true;
			window.draw(rectangle);
			window.draw(text);

			//DRAW_BUTTON = false;
			//NEED_MENU = true;
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
			text.setString("��� ��� ������� ���������� �� �����?");
			user_text.setString("");
		}
		if (QUESTION_DONE)
		{

			printf("[%s]\n", user_question);
			QUESTION_DONE = false;
			NEED_UPDATE_BASE = true;
			text.move(75, 0);
			text.setString("������� ������� �� ����!");
			//NEED_MENU = true;
			//tmp_root = root_;
		}

		if (NEED_QUESTION)
		{
			printf("here\n");
			window.draw(text);

			window.draw(user_word_rect);
			window.draw(user_text);
		}
		if (WAIT_WORD)
		{
			window.draw(user_word_rect);
			window.draw(user_text);
		}
		if (REGIME_2)
		{
			show_tree();
			REGIME_2 = false;
			
			NEED_MENU = true;
			text.setString("�������� ����� ����:");
		}

		// EXIT BUTTON
		window.draw(exit_rect);
		window.draw(exit_but);


		// ��������� ����
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

		//printf("��� ������� [%s]\n", new_data);

		// USER WORD   -- TRUE   -- RIGHT RIGHT

		//printf("\t\t� ������ �����-������ ��� ��������, �������� ��� � ���� �����\n:");

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
		//printf("��� ������ [%s]\n", new_question);


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