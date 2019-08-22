#pragma once
#include <vector>
#include "SmartPointer.h"
namespace Engine {
	namespace Controller
	{
		class BaseController
		{
		public:
			virtual ~BaseController() {};
			virtual void Update() = 0;
		};

		extern std::vector<BaseController *> Controllers;
		void Update();
		void CleanUp();
	}
}


