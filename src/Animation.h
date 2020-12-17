#ifndef ANIMATION_H
#define ANIMATION_h

class Animation {
public :
	unsigned int animationIndex; 
	unsigned int numFrames;
	unsigned int animationSpeed;
	Animation();
	Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
};


#endif