#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	Bug* trg = nullptr;
	float min_dst = INFINITE;
	for (auto obj : g_Game->objects)
		if (obj->GetRTTI() == Bug::s_RTTI)
		{
			if (obj->disabled)
				continue;
			float dst = position.Distance2(obj->position);
			if (dst < min_dst)
			{
				min_dst = dst;
				trg = static_cast<Bug*>(obj);
			}
		}
	return trg;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	auto vel = target_dir * target_vel;
	auto a = vel.Length2() - bullet_vel * bullet_vel;

	auto dist = target_pos - position;
	auto b = 2 * (vel.x * dist.x + vel.y * dist.y);
	auto c = dist.Length2();

	auto disc = b * b - 4 * a * c;
	if (disc == 0)
		return dist;

	auto t1 = (-b + sqrt(disc)) / (2 * a);
	auto t2 = (-b - sqrt(disc)) / (2 * a);
	auto t = std::max(t1, t2);

	return vel * t + dist;
}
