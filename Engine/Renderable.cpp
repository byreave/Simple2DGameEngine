#include "Renderable.h"

void Engine::Render::Renderable::Render() const
{
	GLib::Sprites::RenderSprite(*m_Sprite, GetPosition(), m_Gameobject.AcquireOwnership()->GetZRotation() / 180.0f * 3.1415f);
}

void Engine::Render::RenderAll()
{
	for (auto it = RenderableInfo.begin(); it != RenderableInfo.end(); ++it)
	{
		Renderable * ren = *it;
		ren->Render();
	}
}

void Engine::Render::CleanUp()
{
	for (auto it = RenderableInfo.begin(); it != RenderableInfo.end(); ++it)
	{
		Renderable * ren = *it;
		delete ren;
	}
	RenderableInfo.~vector();
}
