#pragma once
#include "GameBase/BulletBase.h"

struct Bullet : public BulletBase
{
	Bullet()
	{
		visible = true;
		disabled = false;
	};
	DEFINE_RTTI;

	virtual void OnStart(Point direction) override;
	virtual void OnUpdate(float dt) override;
	virtual void OnLifeEnd() override;
};