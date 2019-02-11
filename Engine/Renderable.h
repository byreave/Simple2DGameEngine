#pragma once
#include "GameObject.h"
#include "GLib.h"
#include "SmartPointer.h"
#include <vector>
namespace Render
{
	class Renderable
	{
	private:
		WeakPointer<GameObject> m_Gameobject;
		GLib::Sprites::Sprite * m_Sprite;
		inline GLib::Point2D GetPosition() const;
	public:
		Renderable(const StrongPointer<GameObject> &  i_GameObject, GLib::Sprites::Sprite * i_Sprite) :
			m_Gameobject(i_GameObject),
			m_Sprite(i_Sprite)
		{
		}
		~Renderable()
		{
			m_Gameobject.~WeakPointer();
			GLib::Sprites::Release(m_Sprite);
		}

		void Render() const;
	};
	inline GLib::Point2D Renderable::GetPosition() const
	{
		GLib::Point2D tmpPoint;
		Point2D<float> tmpPoint2D = m_Gameobject.AcquireOwnership()->GetPosition();
		tmpPoint.x = tmpPoint2D.getX();
		tmpPoint.y = tmpPoint2D.getY();
		return tmpPoint;
	}



	//lists of all renderable
	extern std::vector<Renderable *> RenderableInfo;
	void RenderAll();
	void CleanUp();
}


