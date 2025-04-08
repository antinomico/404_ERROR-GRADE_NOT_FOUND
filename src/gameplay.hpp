#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "raylib.h"
#include "animation.hpp"

class Player {
	public:
		Player();
		Player(Vector2 position, float health, float speed, float radius, float widht, float height, Color color);
		
		void Init(Vector2 position, float health);
		void PosUpdate();
		void AnimUpdate();
		void Draw();
		void Unload();

		bool CollisionMesas() const;

		Vector2 getPosition() const;
	private:
		Vector2 position;
		Vector2 direction;
		Vector2 swordPosition;

		Color color;

		Animation idleAnimation;
		Animation runAnimation;
		Animation dashAnimation;
		Animation attackAnimation;
		Animation dieAnimation;

		float health;		
		float speed;
		float dash_timer;
		float radius;
		float width;
		float height;

		int state;
};

class ALBoss {
	public:
		ALBoss(Vector2 position, float health, float speed, float radius, Color color);

		void Init();
		void PosUpdate();
		void AnimUpdate();
		void Draw();
		void Unload();

		Vector2 getPosition() const;
	private:
		Vector2 position;
		Color color;

		Animation idleAnimation;
		Animation runAnimation;
		Animation attackAnimation;
		Animation dieAnimation;
	
		float health;
		float speed;
		float speed_dash;
		float speed_timer;
		float radius;
		
		int state;
};

#endif // !GAMEPLAY_HPP