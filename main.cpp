//main.cpp 
#include "settings.h" 
using namespace sf;

int main()
{
	// Объект, который, собственно, является главным окном приложения 
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);
	//создание объектов игры 
	//ракетки 
	RectangleShape leftBat, rightBat;
	leftBat.setSize(batSize);
	rightBat.setSize(batSize);
	leftBat.setFillColor(leftBatColor);
	rightBat.setFillColor(rightBatColor);
	leftBat.setPosition(batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	rightBat.setPosition(WINDOW_WIDTH - batOffset - batWidth, (WINDOW_HEIGHT - batHeight) / 2);
	float leftbatSpeedY = 0.f;
	float rightbatSpeedY = 0.f;

	//шарик 
	CircleShape ball(ballRadius);
	ball.setFillColor(ballColor);
	ball.setPosition((WINDOW_WIDTH - 2 * ballRadius) / 2,
		(WINDOW_HEIGHT - 2 * ballRadius) / 2);

	float arr_speed[]{ -5.f,-4.f,-3.f,-2.f,-1.f,1.f,2.f,3.f,4.f,5.f };
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
	index = rand() % 10;
	float ball_speedy = arr_speed[index];

	//счёт
	int leftPlayerScore = 0;
	int rightPlayerScore = 0;

	Font font;
	font.loadFromFile("ds-digib.ttf");

	Text leftPlayerScoreText;
	leftPlayerScoreText.setString(std::to_string (leftPlayerScore));//передать строку для отображения
	leftPlayerScoreText.setFont(font);
	leftPlayerScoreText.setCharacterSize(64);
	leftPlayerScoreText.setPosition(200.f, 10.f);
	

	Text rightPlayerScoreText;
	rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
	rightPlayerScoreText.setFont(font);
	rightPlayerScoreText.setCharacterSize(64);
	rightPlayerScoreText.setPosition(560.f, 10.f);

	
	float midLeftX = ball.getPosition().x;
	float midLeftY = ball.getPosition().y + ballRadius;
	if (leftBat.getPosition().x <= midLeftX && midLeftX <= leftBat.getPosition().x + batWidth) {
		ball_speedx = -ball_speedx;
	}
	if (leftBat.getPosition().y <= midLeftY && midLeftY <= leftBat.getPosition().y + batHeight) {
		ball_speedx = -ball_speedx;
	}


	float midBottomX = ball.getPosition().x;
	float midBottomY = ball.getPosition().y + ballRadius;
	if (leftBat.getPosition().x <= midBottomX && midBottomX <= leftBat.getPosition().x + batWidth) {
		ball_speedy = -ball_speedy;
	}
	if (leftBat.getPosition().y <= midBottomY && midBottomY <= leftBat.getPosition().y + batHeight) {
		ball_speedy = -ball_speedy;
	}




	// Главный цикл приложения. Выполняется, пока открыто окно 
	while (window.isOpen())
	{
		//1 Обрабатываем очередь событий в цикле 
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно? 
			if (event.type == Event::Closed)
				// тогда закрываем его 
				window.close();
		}

		//2 Обновление объектов 
		//шарик 
		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().x <= 0)
		{
			ball_speedx = -ball_speedx;
			rightPlayerScore++;
			rightPlayerScoreText.setString(std::to_string(rightPlayerScore));
		}

		if (ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius))
		{
			ball_speedx = -ball_speedx;
			leftPlayerScore++;
			leftPlayerScoreText.setString(std::to_string(leftPlayerScore));
		}

		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= (WINDOW_HEIGHT - 2 * ballRadius))
		{
			ball_speedy = -ball_speedy;
		}
		//Проверка нажатий клавишь 
		//если клавиша W нажата - левая ракетка 
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			leftbatSpeedY = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			leftbatSpeedY = batSpeed;
		}
		leftBat.move(0, leftbatSpeedY);
		leftbatSpeedY = 0.f;
		//границы экрана для левой ракетки 
		if (leftBat.getPosition().y <= 0)
		{
			leftBat.setPosition(batOffset, 0);
		}
		if (leftBat.getPosition().y >= WINDOW_HEIGHT - batHeight)
		{
			leftBat.setPosition(batOffset, WINDOW_HEIGHT - batHeight);
		}

		//управление правой ракеткой 
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			rightbatSpeedY = -batSpeed;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			rightbatSpeedY = batSpeed;
		}
		rightBat.move(0, rightbatSpeedY);
		rightbatSpeedY = 0.f;
		//границы для правой ракетки 
		if (rightBat.getPosition().y <= 0)
		{
			rightBat.setPosition(WINDOW_WIDTH - batOffset, 0);
		}
		if (rightBat.getPosition().y >= WINDOW_HEIGHT - batHeight)
		{
			rightBat.setPosition(WINDOW_WIDTH - batOffset, WINDOW_HEIGHT - batHeight);
		}


		//3 Отрисовка окна 
		//3.1 Очистка окна 
		window.clear();
		//3.2 Отрисовка объектов (В ПАМЯТИ!) 
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		window.draw(leftPlayerScoreText);
		window.draw(rightPlayerScoreText);
		//3.3 вывод на экран 
		window.display();
	}

	return 0;
}
