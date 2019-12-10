#include "AnimationCreator.h"

AnimationCreator* AnimationCreator::animationCreator{nullptr};

AnimationCreator* AnimationCreator::getInstance()
{
	if (animationCreator) {
		return animationCreator;
	}
	animationCreator = new AnimationCreator();
	return animationCreator;
}

Animate* AnimationCreator::createAnimate(string path, int imAmount, int imWidth, int imHeight, float time)
{
	Vector<SpriteFrame*> picsVector;
	picsVector.reserve(imAmount);
	for (int i = 0; i < imAmount; i++) {
		picsVector.pushBack(SpriteFrame::create(path, Rect(i * imWidth, 0, imWidth, imHeight)));
		picsVector.at(i)->getTexture()->setAliasTexParameters();
	}
	auto animation = Animation::createWithSpriteFrames(picsVector, time, -1);
	Animate* animate = Animate::create(animation);
	animate->retain();

	return animate;
}
