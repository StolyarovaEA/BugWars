#include "pch.h"
#include "Bug.h"
#include "Game.h"
#include "GameBase/Framework.h"
#include "GameBase/TankBase.h"

IMPLEMENT_RTTI(Bug);


void Bug::OnUpdate(float dt)
{
	if (g_Game->framework) {
		Point border1 = g_Game->tank->position - g_Game->framework->screenSize / 2;
		Point border2 = border1 + g_Game->framework->screenSize;
		visible = position.x + GetSize().x / 2 > border1.x &&
			position.y + GetSize().y / 2 > border1.y &&
			position.x - GetSize().x / 2 < border2.x &&
			position.y - GetSize().y / 2 < border2.y;
	}
}

BugBase* Bug::FindBugToEat() const
{
	BugBase* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	for (auto object : g_Game->objects)
	{
		if (object->GetRTTI() == Bug::s_RTTI)
		{
			if (object == this)
				continue;

			if (object->disabled)
				continue;

			if (object->id > id)
				continue; // Can't eat that

			float dist = position.Distance2(object->position);
			if (dist < min_dist)
			{
				min_dist = dist;
				target = static_cast<BugBase*>(object);
			}
		}
	}

	return target;
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	if (first.id > second.id)
	{
		second.disabled = true;
		second.visible = false;
	}
	else
	{
		first.disabled = true;
		first.visible = false;
	}
}
