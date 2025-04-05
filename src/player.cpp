#include "raylib.h"
#include "animation.hpp"
#include "gameplay.hpp"
#include "raymath.h"

typedef enum AnimationPlayer {
	IDLE = 0,
	RUN = 1,
	DASH = 2,
	ATTACK = 3,
	DIE = 4
};

Player::Player() :
	position({ 0, 0 }), swordPosition({ 0, 0 }), health(100.0f), speed(5.0f), radius(5.0f), width(20.0f), height(20.0f), color(RED), state(IDLE) {
	idleAnimation = Animation("rsc/player_idle.png", 4, 0.1f, 0.2f),
		runAnimation = Animation("rsc/player_run.png", 4, 0.1f, 0.2f),
		dashAnimation = Animation("rsc/player_dash.png", 4, 0.1f, 0.2f),
		attackAnimation = Animation("rsc/player_attack.png", 4, 0.1f, 0.2f),
		dieAnimation = Animation("rsc/player_die.png", 4, 0.1f, 0.2f);
	direction = { 0, 0 };
	dash_timer = 0.0f;
}

// exemplo de classe player com supostos sprites
Player::Player(Vector2 position, float health, float speed, float radius, float width, float height, Color color) :
	position(position), swordPosition(position), health(health), speed(speed), radius(radius), width(width), height(height), color(color), state(IDLE) {
	idleAnimation = Animation("rsc/player_idle.png", 4, 0.1f, 0.2f),
	runAnimation = Animation("rsc/player_run.png", 4, 0.1f, 0.2f),
	dashAnimation = Animation("rsc/player_dash.png", 4, 0.1f, 0.2f),
	attackAnimation = Animation("rsc/player_attack.png", 4, 0.1f, 0.2f),
	dieAnimation = Animation("rsc/player_die.png", 4, 0.1f, 0.2f);
	direction = { 0, 0 };
	dash_timer = 0.0f;
}

void Player::Init(Vector2 position, float health) {
	this->position = position;
	this->health = health;

	state = IDLE;
}

void Player::PosUpdate() {
	if (health <= 0) {
	}
	else {
		if (dash_timer > 0) {
			dash_timer++;
			if (dash_timer > 150.0f)
				dash_timer = 0.0f;
			else if (dash_timer > 10.0f)
				speed = 5.0f;
		}

		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			if (!dash_timer)
				dash_timer++;
			speed = dash_timer <= 10.0f ? 10.0f : 5.0f;			
		}
		
		if (IsKeyPressed(KEY_J)) {
		
		}
		
		direction = { 0, 0 };

		if (IsKeyDown(KEY_A)) {
			direction.x -= 1;
		}
		if (IsKeyDown(KEY_D)) {
			direction.x += 1;
		}
		if (IsKeyDown(KEY_W)) {
			direction.y -= 1;
		}
		if (IsKeyDown(KEY_S)) {
			direction.y += 1;
		}

		if (Vector2Length(direction) > 0) {
			direction = Vector2Normalize(direction);
			position.x += direction.x * speed;
			position.y += direction.y * speed;
		}
	}
}

void Player::AnimUpdate() {
	if (health <= 0) {
		state = DIE;
	}
	else {
		if (IsKeyPressed(KEY_SPACE)) {
			state = DASH;
		}
		else if (IsKeyPressed(KEY_J)) {
			if (dashAnimation.IsFinished())
				state = ATTACK;
		}
		else if (IsKeyDown(KEY_A)) {
			if (dashAnimation.IsFinished())
				state = RUN;
		}
		else if (IsKeyDown(KEY_D)) {
			if (dashAnimation.IsFinished())
				state = RUN;
		}
		else if (IsKeyDown(KEY_W)) {
			if (dashAnimation.IsFinished())
				state = RUN;
		}
		else if (IsKeyDown(KEY_S)) {
			if (dashAnimation.IsFinished())
				state = RUN;
		}
		else {
			state = IDLE;
		}
	}
}

void Player::Draw() {
	/*
	switch (state) {
	case IDLE:
		idleAnimation.Draw(position, GetKeyPressed());
		break;
	case RUN:
		runAnimation.Draw(position, GetKeyPressed());
		break;
	case DASH:
		dashAnimation.Draw(position, GetKeyPressed());
		break;
	case ATTACK:
		attackAnimation.Draw(position, GetKeyPressed());
		break;
	case DIE:
		dieAnimation.Draw(position, GetKeyPressed());
		break;
	}
	*/
	DrawRectangle(position.x, position.y, width, height, RED);
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
