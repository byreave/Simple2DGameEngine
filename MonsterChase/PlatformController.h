#pragma once
#include "BaseController.h"
#include "Input.h"
#include "GameObject.h"
namespace Engine
{
	namespace Controller
	{
		class PlatformController :
			public BaseController
		{

		public:
			PlatformController(Engine::StrongPointer<GameObject> i_GameObject, const Point2D<float> & i_MoveSpeed) :
				gameObject(i_GameObject),
				MoveSpeed(i_MoveSpeed)
			{
				Input::ButtonChangeReceivers.AddDelegate(Input::ButtonChangeReceiver_t::Create<PlatformController, &PlatformController::HandleButtonMovement>(this));
			}

			void HandleButtonMovement(unsigned int i_Vkey, bool b_WentDown);

			~PlatformController()
			{
				Input::ButtonChangeReceivers.RemoveDelegate(Input::ButtonChangeReceiver_t::Create<PlatformController, &PlatformController::HandleButtonMovement>(this));
			}
			void Update()
			{

			}
			static void PlatformControllerFactory(Engine::StrongPointer<GameObject> i_GameObject);
			Engine::WeakPointer<GameObject> gameObject;
			Point2D<float> MoveSpeed;
		};

	}
}

