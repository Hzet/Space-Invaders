#include <SFML/Graphics.hpp>
#include <vector>
#include "spacecraft-hostile.hpp"
#include "functions.hpp"
#include <Windows.h>

const int SCREEN_HEIGHT = 1024;
const int SCREEN_WIDTH = 1280;

int main()
{
	std::srand(std::time(NULL));

	// prepare game state info text objects to be printed
	sf::Font font;
	font.loadFromFile("impact.ttf");

	sf::Text scoreText;
	sf::Text livesText;
	sf::Text wavesText;
	sf::Text fpsText;

	scoreText.setFont(font);
	scoreText.setCharacterSize(25);

	livesText.setFont(font); 
	livesText.setCharacterSize(25);

	wavesText.setFont(font); 
	wavesText.setCharacterSize(25);

	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setCharacterSize(15);

	// prepare base textures for the game objects
	sf::Texture playerSpacecraftTexture;
	sf::Texture playerBulletTexture;
	sf::Texture hostileSpacecraftTexture;
	sf::Texture hostileBulletTexture;

	playerSpacecraftTexture.loadFromFile("playerSpacecraftTexture.png");
	playerBulletTexture.loadFromFile("playerBulletTexture.png");
	hostileBulletTexture.loadFromFile("hostileBulletTexture.png");
	hostileSpacecraftTexture.loadFromFile("hostileSpacecraftTexture.png");

	// prepare game objects
	gsi::CSpacecraft playerSpacecraft;
	gsi::CHostileSpacecraft hostileSpacecraftTemplate;
	std::vector<gsi::CHostileSpacecraft> hostileSpacecrafts;

	// prepare player's spacecraft
	gsi::CBullet playerBulletTemplate(playerBulletTexture);
	playerBulletTemplate.setVelocity(5.f);
	playerBulletTemplate.setDirection(gsi::EDirection::DIRECTION_UP);

	playerSpacecraft.setCooldown(750.f);
	playerSpacecraft.setVelocity(1.f);
	playerSpacecraft.setTexture(playerSpacecraftTexture);
	playerSpacecraft.setBullet(playerBulletTemplate);
	playerSpacecraft.setPosition(sf::Vector2f((float)SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 150.f));

	// prepare hostile spacecrafts
	gsi::CBullet hostileBulletTemplate(hostileBulletTexture);
	hostileBulletTemplate.setVelocity(0.3f);
	hostileBulletTemplate.setDirection(gsi::EDirection::DIRECTION_DOWN);

	hostileSpacecraftTemplate.setCooldown(1500.f);
	hostileSpacecraftTemplate.setVelocity(0.1f);
	hostileSpacecraftTemplate.setTexture(hostileSpacecraftTexture);
	hostileSpacecraftTemplate.setBullet(hostileBulletTemplate);
	hostileSpacecraftTemplate.setPosition(sf::Vector2f((float)SCREEN_WIDTH / 2.f, hostileSpacecraftTemplate.getTextureRect().height));
	hostileSpacecraftTemplate.setSwitchDistance(50.f);

	// key SPACE pressed event state 
	bool shootFlag = false;
	bool pauseFlag = false;
	bool endFlag = false;

	// game state information
	int score = 0;
	int lives = 4;
	int wave = 0;
	float hostileShootingDelay = 1500.f;
	float hostileShootingDelayCounter = 0.f;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");
	
	sf::Clock clock;
	float frameTime;
	float frameTimeCounter = 0.f;
	int frameCount = 0;
	clock.restart();

	while (window.isOpen())
	{
		frameTime = (float)clock.getElapsedTime().asMicroseconds() / 1000.f;
		clock.restart();
		frameTimeCounter += frameTime;
		frameCount++;
		hostileShootingDelayCounter += frameTime;

		// poll window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				endFlag = true;
				break;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					shootFlag = true;
					break;
				case sf::Keyboard::D:
					playerSpacecraft.setDirection(gsi::EDirection::DIRECTION_RIGHT);
					break;
				case sf::Keyboard::A:
					playerSpacecraft.setDirection(gsi::EDirection::DIRECTION_LEFT);
					break;
				case sf::Keyboard::Escape:
					pauseFlag = !pauseFlag;
					break;
				default:
					break;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					shootFlag = false;
					break;
				case sf::Keyboard::D:
					playerSpacecraft.setDirection(gsi::EDirection::DIRECTION_INVALID);
					break;
				case sf::Keyboard::A:
					playerSpacecraft.setDirection(gsi::EDirection::DIRECTION_INVALID);
					break;
				default:
					break;
				}
			}
		}
		
		// update flags actions
		if (pauseFlag)
		{
			clock.restart();
			sf::Text pauseText("PAUSE", font, 30);
			pauseText.setPosition(SCREEN_WIDTH / 2 - pauseText.getGlobalBounds().width / 2.f, SCREEN_HEIGHT / 2 - pauseText.getGlobalBounds().height / 2.f);
			window.draw(pauseText);
			window.display();
			continue;
		}

		if (endFlag)
			break;

		if (shootFlag)
			playerSpacecraft.shoot();

		// generate new wave if the player has REKT the previous one
		if (hostileSpacecrafts.empty())
		{
			lives++;
			wave++;
			hostileSpacecrafts = gsi::generateWave(wave, hostileSpacecraftTemplate, SCREEN_WIDTH);
			sf::Text infoText("STARTING NEW WAVE: " + std::to_string(wave), font, 25);
			infoText.setPosition(SCREEN_WIDTH / 2 - infoText.getGlobalBounds().width / 2.f, SCREEN_HEIGHT / 2 - infoText.getGlobalBounds().height / 2.f);
			window.draw(infoText);
			window.display();
			Sleep(2000);
			clock.restart();
			continue;
		}

		// shot and update shooting timers
		playerSpacecraft.updateBullets(frameTime);

		for (auto &v : hostileSpacecrafts)
			v.updateBullets(frameTime);

		if (hostileShootingDelayCounter >= hostileShootingDelay)
		{
			int random;
			if (hostileSpacecrafts.size() == 1)
				random = 0;
			else
				random = std::rand() % (hostileSpacecrafts.size() - 1);

			hostileSpacecrafts[random].shoot();
			hostileShootingDelayCounter -= hostileShootingDelay;
			if (hostileShootingDelayCounter >= hostileShootingDelay)
				hostileShootingDelayCounter = 0.f;
		}

		// move spacrafts and their's bullets
		playerSpacecraft.moveOverTime(frameTime);
		if (playerSpacecraft.getPosition().x + playerSpacecraft.getGlobalBounds().width / 2.f < 0.f)
			playerSpacecraft.setPosition(SCREEN_WIDTH - playerSpacecraft.getGlobalBounds().width / 2.f, playerSpacecraft.getPosition().y);
		else if (playerSpacecraft.getPosition().x + playerSpacecraft.getGlobalBounds().width / 2.f > SCREEN_WIDTH)
			playerSpacecraft.setPosition(-playerSpacecraft.getGlobalBounds().width / 2.f, playerSpacecraft.getPosition().y);


		for (auto &v : hostileSpacecrafts)
			v.moveOverTime(frameTime);

		// check for collisions, update player's score and restart the wave if necessary
		// player spacecraft and hostile bullets collision
		for (auto &v : hostileSpacecrafts)
			if (gsi::isColliding(playerSpacecraft, v.getBullets()))
			{
				wave--;
				lives--;
				if (lives < 0)
				{
					endFlag = true;
					break;
				}
				lives--;
				hostileSpacecrafts.clear();
				continue;
			}

		// player bullets with hostile spacecrafts collision
		for (int i = playerSpacecraft.getBullets().size() - 1; i >= 0; i--)
		{
			int tmp = gsi::isColliding(playerSpacecraft.getBullets()[i], hostileSpacecrafts);
			if (tmp > 0)
			{
				score += 2 * tmp;
				playerSpacecraft.getBullets().erase(playerSpacecraft.getBullets().begin() + i);
			}
		}
		
		// player bullets with hostile bullets collision
		for (int i = playerSpacecraft.getBullets().size() - 1; i >= 0; i--) 
			for (auto &v : hostileSpacecrafts)
			{
				int tmp = gsi::isColliding(playerSpacecraft.getBullets()[i], v.getBullets());
				if (tmp > 0)
				{
					score += tmp;
					playerSpacecraft.getBullets().erase(playerSpacecraft.getBullets().begin() + i);
					break;
				}
			}

		// hostile spacecrafts below the visible players position
		for(auto &v : hostileSpacecrafts)
			if (v.getPosition().y + v.getGlobalBounds().height / 2.f > playerSpacecraft.getPosition().y - playerSpacecraft.getGlobalBounds().height / 2.f)
			{
				wave--;
				lives--;
				if (lives < 0)
				{
					endFlag = true;
					break;
				}
				lives--;
				hostileSpacecrafts.clear();
				continue;
			}

		// update text objects
		scoreText.setString("SCORE " + std::to_string(score));
		livesText.setString(std::to_string(lives) + "\t<3");
		wavesText.setString("WAVE " + std::to_string(wave));
		if (frameTimeCounter >= 1000.f)
		{
			fpsText.setString("FPS: " + std::to_string(frameCount));
			frameTimeCounter -= 1000.f;
			if (frameTimeCounter >= 1000.f)
				frameTimeCounter = 0.f;
			frameCount = 0;
		}
		scoreText.setPosition(50.f, SCREEN_HEIGHT - 80.f);
		livesText.setPosition(scoreText.getPosition().x + scoreText.getLocalBounds().width + 150.f, SCREEN_HEIGHT - 80.f);
		wavesText.setPosition(livesText.getPosition().x + livesText.getLocalBounds().width + 150.f, SCREEN_HEIGHT - 80.f);

		// draw object onto the screen
		window.clear();
		window.draw(playerSpacecraft);
		for (const auto &v : playerSpacecraft.getBullets())
			window.draw(v);
		for (auto &v : hostileSpacecrafts)
		{
			for (const auto &vbullet : v.getBullets())
				window.draw(vbullet);
			window.draw(v);
		}
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(wavesText);
		window.draw(fpsText);
		window.display();
	}

	// display text when the game is finished
	sf::Text endgameText;
	endgameText.setFont(font);
	endgameText.setCharacterSize(30);

	if (lives < 0)
	{
		endgameText.setFillColor(sf::Color::Red);
		endgameText.setString("GAME LOST");
	}
	else
	{
		endgameText.setString("GAME ENDED");
	}
	endgameText.setPosition(SCREEN_WIDTH / 2 - endgameText.getGlobalBounds().width / 2.f, SCREEN_HEIGHT / 2 - endgameText.getGlobalBounds().height / 2.f);

	window.draw(endgameText);
	window.display();
	Sleep(4500);
	window.close();
}
