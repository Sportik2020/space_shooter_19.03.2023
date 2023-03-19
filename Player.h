#pragma once
#include "settings.h"
#include "cmath"
#include <list>
#include "Bullet.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int angle;
	float speed, speedx, speedy;
	std::list<Bullet*> bullets;
	sf::Clock timer;

public:
	Player() {
		texture.loadFromFile(Player_File_Name);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		angle = 0;
		speed = 0.f;
		timer.restart();
	}

	void update() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			angle -= 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 3;
		}
		sprite.setRotation(angle);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			speed += 0.5f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			speed -= 0.25f;
		}
		if (speed < 0) speed = 0.f;
		else if (speed > 10.f) speed = 10.f;

		speedx = speed * sin(angle * PI / 180);
		speedy = -speed * cos(angle * PI / 180);
		sprite.move(speedx, speedy);
		fire();
		for (auto bullet : bullets) {
			bullet->update();
		}
	}

	void fire() {
		int now = timer.getElapsedTime().asMilliseconds();
		if (now > fire_cooldown) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				auto bullet = new Bullet(sprite.getPosition(), angle);
				bullets.push_back(bullet);
				timer.restart();
			}
		}
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		for (auto bullet : bullets) {
			window.draw(bullet->getSprite());
		}
	}
};