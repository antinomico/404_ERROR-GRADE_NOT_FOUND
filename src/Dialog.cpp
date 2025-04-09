#include "raylib.h"
#include "animation.hpp"

Dialog::Dialog() :
	font({ 0 }), position({ 0, 0 }), text(nullptr), indexWord(0), frameTime(0), frameCounter(0) {
}

Dialog::Dialog(const Font font, int frameTime) :
	font(font), position({ 0, 0 }), text(nullptr), indexWord(0), frameTime(frameTime), frameCounter(0) {
}

void Dialog::Init(const char* text, Vector2 position) {
	this->text = text;
	this->position = position;
	frameCounter = 0;
	indexWord = 0;
}

void Dialog::Update(int frameTimes) {
	frameCounter++;
	if (frameCounter >= frameTimes) {
		frameCounter = 0;
		indexWord++;
	}
}

void Dialog::Draw() {
	DrawTextEx(font, TextSubtext(text, 0, indexWord), position, 20, 4, RAYWHITE);
}

bool Dialog::IsFinished() const {
	return (indexWord >= TextLength(text));
}

void Dialog::Unload() const {
	UnloadFont(font);
}