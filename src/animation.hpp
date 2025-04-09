#ifndef ANIMATION_HPP
#define	ANIMATION_HPP

#include "raylib.h"

class Animation {
	public:
		Animation();
		Animation(const char* fileName, int numFrames, float frameTime, float scale);
		
		void Init();
		void Update();
		void Draw(Vector2 position, int key);
		int IsFinished() const;
		void Unload() const;
	private:
		Texture2D texture;

		int numFrames;
		float frameTime;
		int currentFrame;
		int frameAxis;
		int frameWidth;
		float scale;
};

class Dialog {
	public:
		Dialog();
		Dialog(const Font font, int frameTime);

		void Init(const char* text, Vector2 position);
		void Update(int FrameTimes);
		void Draw();
		bool IsFinished() const;
		void Unload() const;
	private:
		const Font font;
		Vector2 position;

		const char* text;
		int indexWord;
		int frameTime;
		int frameCounter;
};

#endif // !ANIMATION_HPP