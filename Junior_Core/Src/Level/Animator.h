#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Animator.h
 * Description: Moves UV coordinates around to create animations inside sprite sheets
 * Created: 14-Feb-2019
 * Last Modified: 14-Feb-2019
*/

// Includes
#include "Component.h"			// Component

namespace Junior
{
	// Forward Declaration
	class MemoryManager;
	class Sprite;

	class Animator : public Component
	{
	private:
		// Private Member Variables

		// The current frame of the animation
		unsigned currentFrame_;
		// Is the animator playing the animation
		bool playing_;
		// Is the animation looping
		bool loop_;
		// The start of the animation
		unsigned start_;
		// The end of the animation
		unsigned end_;
		// The number of the colums in the animation
		unsigned numRows_;
		// The number of rows in the animation
		unsigned numColumns_;
		// The timer that counts the time between frames
		double timer_;
		// The time in between frames
		double timePerFrame_;
		// The original texture x offset
		unsigned originalXOffset_;
		// The original texture y offset
		unsigned originalYOffset_;
		// The size of texture in texture coordinates (x axis)
		float textureXSize_;
		// The size of texture in texture coordaintes (y axis)
		float textureYSize_;
		// Column size in texture coordinates
		float columnSize_;
		// Row size in texture coordinates
		float rowSize_;
		// The sprite component we are going to animate
		Sprite* sprite_;
	public:
		// Public Member Functions

		// Constructs the animator component
		// Params:
		//	colums: The number of columns in the sprite sheet
		//	rows: The number of rows in the sprite sheet
		Animator(unsigned columns, unsigned rows);
		// Initializes the component
		void Initialize() override;
		// Updates the component
		// Params:
		//	dt: The time in between frames
		void Update(double dt) override;
		// Shutsdown the component
		// Params:
		//	manager: The memory manager used to create this component
		void Clean(MemoryManager* manager) override;
		// Play the animation
		// Params:
		//	start: The starting frame of the animation
		//	end: The ending frame of the animation
		//	timePerFrame: The time in between frames
		//	looping: Whether the animation loops
		void Play(unsigned start, unsigned end, double timePerFrame = 0.2, bool looping = false);
		// Stop playing the animation
		void Stop();
		// Sets a frame of animation on display
		// Params:
		//	frame: The frame of animation in display
		void SetFrame(unsigned frame);
		// Returns: Whether an animation is playing or not
		bool IsPlaying() const;
	};
}