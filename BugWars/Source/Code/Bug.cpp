#include "pch.h"
#include "Bug.h"
#include "Game.h"

IMPLEMENT_RTTI(Bug);


void Bug::OnUpdate(float dt)
{
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
