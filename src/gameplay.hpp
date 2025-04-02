#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "raylib.h"
#include "screens.hpp"
#include "animation.hpp"

class Player {
	public:
		Player(Vector2 position, float health, float speed, float radius, Color color);
		
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
		Animation dashAnimation;
		Animation attackAnimation;
		Animation dieAnimation;

		float health;		
		float speed;
		float radius;

		int state;
};

#endif // !GAMEPLAY_HPP