#pragma once
#include "GameObject.h"
#include "GLib.h"
class Renderable
{
private:
	GameObject * m_Gameobject;
	GLib::Sprites::Sprite * m_Sprite;
public:
	Renderable();
	~Renderable();
};

