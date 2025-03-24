#include "raylib.h"
#include "animation.hpp"

Animation::Animation() : numFrames(0), frameTime(0), currentFrame(0), frameWidth(0), scale(0) {
}

Animation::Animation(const char* fileName, int numFrames, float frameTime, float scale) :
	numFrames(numFrames), frameTime(frameTime), scale(scale) {
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

void Animation::Draw(Vector2 position) const {
	Rectangle source = { (float) currentFrame * frameWidth, 0, (float) frameWidth, (float) texture.height };
	Rectangle dest = { position.x, position.y, (float) frameWidth * scale, (float) texture.height * scale };
	DrawTexturePro(texture, source, dest, position, 0.0f, WHITE);
}

void Animation::Unload() const {
	UnloadTexture(texture);
}
