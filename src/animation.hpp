#ifndef ANIMATION_HPP
#define	ANIMATION_HPP

#include "raylib.h"

class Animation {
	public:
		Animation();
		Animation(const char* fileName, int numFrames, float frameTime, float scale);
		void Init();
		void Update();
		void Draw(Vector2 position) const;
		void Unload() const;
	private:
		Texture2D texture;

		int numFrames;
		float frameTime;
		int currentFrame;
		int frameWidth;
		float scale;
};

#endif // !ANIMATION_HPP