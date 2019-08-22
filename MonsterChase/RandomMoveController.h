#pragma once
#include <BaseController.h>
#include <GameObject.h>
#include <stdlib.h>
#include "Game.h"
namespace Engine {
	namespace Controller
	{
		class RandomMoveController :
			public BaseController
		{
		public:
			RandomMoveController(StrongPointer<GameObject> i_GameObject) :
				m_GameObject(i_GameObject)
			{
				srand(time(0));
				m_GameObject.AcquireOwnership()->SetVelocity(Point2D<float>((rand() % 10 - 5) / 10.0f, (rand() % 10 - 5) / 10.0f));
			}
			~RandomMoveController() {}
			WeakPointer<GameObject> m_GameObject;

			void Update()
			{
				if (m_GameObject.AcquireOwnership()->GetPosition().getY() <= -300.0f)
					Game::GameOver();
			}
			static void RandomMoveControllerFactory(StrongPointer<GameObject>);
		};
	}
}

