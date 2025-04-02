#include "raylib.h"
#include "animation.hpp"

Animation::Animation() :
	texture{0}, numFrames(0), frameTime(0), currentFrame(0), frameWidth(0), scale(0) {
}

Animation::Animation(const char* fileName, int numFrames, float frameTime, float scale) :
	numFrames(numFrames), frameTime(frameTime), scale(scale), texture{0} {
	texture = LoadTexture(fileName);
	currentFrame = 0;
	frameWidth = texture.width / numFrames;
}

void Animation::Init() {
	currentFrame = 0;
	frameTime = 0;
}

void Animation::Update() {
	frameTime += GetFrameTime();

	if (frameTime >= numFrames) {
		currentFrame = (currentFrame + 1) % numFrames;
		frameTime = 0;
	}
}

void Animation::Draw(Vector2 position, int key) {
	if  (key == KEY_A)
		frameAxis = 0;
	else if (key == KEY_D)
		frameAxis = 1;
	else if (key == KEY_W)
		frameAxis = 2;
	else if (key == KEY_S)
		frameAxis = 3;

	Rectangle source = { (float) currentFrame * frameWidth, (float) frameAxis * texture.width / 4, (float) frameWidth, (float) texture.height / 4 };
	Rectangle dest = { position.x, position.y, (float) frameWidth * scale, (float) texture.height * scale };
	DrawTexturePro(texture, source, dest, position, 0.0f, WHITE);
}

int Animation::IsFinished() const {
	if (currentFrame == 0)
		return 1;
	else
		return 0;
}

void Animation::Unload() const {
	UnloadTexture(texture);
}
