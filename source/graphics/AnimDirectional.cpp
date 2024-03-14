#include "../../include/graphics/AnimDirectional.h"
#include "../../include/graphics/SpriteSheet.h"

void AnimDirectional::frameStep()
{
	if (startFrame < endFrame)	curFrame++;
	else						curFrame--;

	if ((startFrame < endFrame && curFrame > endFrame) || (startFrame > endFrame && curFrame < endFrame))
	{
		if (loop)
		{
			curFrame = startFrame;
			return;
		}
		curFrame = endFrame;
		pause();
	}

}

void AnimDirectional::cropSprite()
{
	const auto spriteSize = spriteSheet->getSpriteSize();
	size_t numAnimations = spriteSheet->getNumAnimations();
	size_t x = spriteSize.x * curFrame;
	size_t y = spriteSize.y * (frameRow + numAnimations * static_cast<short>(spriteSheet->getSpriteDirection()));
	sf::IntRect rect(static_cast<int>(x), static_cast<int>(y), spriteSize.x, spriteSize.y);
	spriteSheet->cropSprite(rect);
}

void AnimDirectional::readIn(std::stringstream& st)
{
	st >> startFrame >> endFrame >> frameRow >> frameTime >> frameActionStart >> frameActionEnd;
}
