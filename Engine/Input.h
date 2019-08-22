#pragma once

#include "Delegates.h"

namespace Engine {
	namespace Input {
		typedef unsigned int button_t;
		typedef Delegate<button_t, bool>	ButtonChangeReceiver_t;

		extern MultiCastDelegate<button_t, bool>	ButtonChangeReceivers;

		bool Init();
		void Release();
	} // namespace Input
} // namespace Engine
