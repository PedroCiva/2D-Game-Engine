#include "Animation.h"

Animation::Animation() {

}
Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
	this->animationIndex = index;
	this->numFrames = numFrames;
	this->animationSpeed = animationSpeed;
}