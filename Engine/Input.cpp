#include "Input.h"
#include "GLib.h"

namespace Engine {
	namespace Input {

		MultiCastDelegate<button_t, bool>	ButtonChangeReceivers;

		void ButtonChangeCallback(unsigned int i_VKey, bool bWentDown)
		{
			ButtonChangeReceivers.ExecuteOnBound(i_VKey, bWentDown);
		}

		bool Init()
		{
			GLib::SetKeyStateChangeCallback(ButtonChangeCallback);

			return true;
		}

		void Release()
		{
			ButtonChangeReceivers.~MultiCastDelegate();
		}
	} // namespace Input
} // namespace Engine
