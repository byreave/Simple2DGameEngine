#include "Renderable.h"

void Render::Renderable::Render() const
{
	GLib::Sprites::RenderSprite(*m_Sprite, GetPosition(), 0.0f);
}

void Render::RenderAll()
{
	for (auto it = RenderableInfo.begin(); it != RenderableInfo.end(); ++it)
	{
		Renderable * ren = *it;
		ren->Render();
	}
}

void Render::CleanUp()
{
	for (auto it = RenderableInfo.begin(); it != RenderableInfo.end(); ++it)
	{
		Renderable * ren = *it;
		delete ren;
	}
}
