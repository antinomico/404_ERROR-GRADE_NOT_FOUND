#include "raylib.h"
#include "animation.hpp"
#include "gameplay.hpp"

typedef enum AnimationPlayer {
	IDLE = 0,
	RUN = 1,
	DASH = 2,
	ATTACK = 3,
	DIE = 4
};

// exemplo de classe player com supostos sprites
Player::Player(Vector2 position, float health, float speed, float radius, Color color) :
	position(position), health(health), speed(speed), radius(radius), color(color) {
	idleAnimation = Animation("rsc/player_idle.png", 4, 0.1f, 0.2f),
	runAnimation = Animation("rsc/player_run.png", 4, 0.1f, 0.2f),
	dashAnimation = Animation("rsc/player_dash.png", 4, 0.1f, 0.2f),
	attackAnimation = Animation("rsc/player_attack.png", 4, 0.1f, 0.2f),
	dieAnimation = Animation("rsc/player_die.png", 4, 0.1f, 0.2f);
	state = 0;
}

void Player::Init() {
	position = { 400, 225 };
	
	speed = 5.0f;
	radius = 20.0f;
	health = 100.0f;

	color = { 255, 255, 255, 255 };

	state = IDLE;
	
}

// criar outro método para update do animation?
void Player::Update() {
	if (health <= 0) {
		state = DIE;
	}
	else {
		if (IsKeyPressed(KEY_SPACE)) {
			state = DASH;
		}
		else if (IsKeyPressed(KEY_J)) {
			state = ATTACK;
		}
		else if (IsKeyDown(KEY_A)) {
			position.x -= speed;
			state = RUN;
		}
		else if (IsKeyDown(KEY_D)) {
			position.x += speed;
			state = RUN;
		}
		else if (IsKeyDown(KEY_W)) {
			position.y -= speed;
			state = RUN;
		}
		else if (IsKeyDown(KEY_S)) {
			position.y += speed;
			state = RUN;
		}
		else {
			state = IDLE;
		}
	}
}

void Player::Draw() {
	switch (state) {
	case IDLE:
		idleAnimation.Draw(position);
		break;
	case RUN:
		runAnimation.Draw(position);
		break;
	case DASH:
		dashAnimation.Draw(position);
		break;
	case ATTACK:
		attackAnimation.Draw(position);
		break;
	case DIE:
		dieAnimation.Draw(position);
		break;
	}
}

void Player::Unload() {
	idleAnimation.Unload();
	runAnimation.Unload();
	dashAnimation.Unload();
	attackAnimation.Unload();
	dieAnimation.Unload();
}

Vector2 Player::getPosition() const {
	return position;
}
