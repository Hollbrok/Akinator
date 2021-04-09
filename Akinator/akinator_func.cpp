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
void graphic_play()
{
	// Устанавливаем 8-й уровень сглаживания
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	bool DRAW_BUTTON = true;
	bool NEED_MENU = false;
	bool REGIME_1 = true;

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


	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{

		// Получаем координаты курсора мышки относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x;
		int y = pos.y;

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{

			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
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
					else
					{
						if ((LT_BUT_POSITION <= x) && (x <= (LT_BUT_POSITION + X_BUT_SIZE)))
						{
							if ((LB_BUT_POSITION + Y_BUT_SIZE + 10 <= y) && (y <= LB_BUT_POSITION + Y_BUT_SIZE + Y_BUT_SIZE + 10))
								window.close();
						}
						else if ((100 <= x) && (x <= 100 + X_BUT_SIZE))
						{
							if ((340 <= y) && (y <= 340 + Y_BUT_SIZE))
							{
								NEED_MENU = false;
								REGIME_1 = true;
								text.setString("Кот?");
							}
						}
					}

				}
			}

		}
		// Установка цвета фона - белый
		window.clear(Color::White);


		// Отрисовка фона
		window.draw(sprite);

		// Отрисовка кнопки play
		window.draw(rectangle);

		if (DRAW_BUTTON)
			window.draw(text);
		else if (NEED_MENU)
		{
			window.draw(text);

			window.draw(reg1_rect);
			window.draw(regime1);

		}
		else if (REGIME_1)
		{
			window.draw(text);

			window.draw(yes_rect);
			window.draw(no_rect);

			window.draw(yes_text);
			window.draw(no_text);

		}

		// EXIT BUTTON
		window.draw(exit_rect);
		window.draw(exit_but);


		// Отрисовка окна
		window.display();
	}
}