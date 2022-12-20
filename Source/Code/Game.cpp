#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		auto obj = objects[i];

		obj->visible = NeedsRender(tank->position, obj->position);

		if (!obj->disabled)
		{
			obj->Update(dt);
		}
		else
		{
			delete obj;
			objects.erase(objects.begin() + i);
		}
	}
}

bool Game::NeedsRender(const Point& center, const Point& object)
{
	auto dist = center - object;

	return fabs(dist.y) < 1000 && fabs(dist.x) < 1000;

}

void Game::OnRender() const
{
	for (auto& obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	if (object->GetRTTI() == Bug::s_RTTI)
	{
		object->visible = false;
		object->disabled = false;
	}
	objects.push_back(object);
}

void Game::OnBugsSpawned()
{
}


Game::~Game()
{
	for (auto obj : objects)
		delete(obj);
}
