#pragma once
#include <string>
#include <map>
#include "SmartPointer.h"
#include "GameObject.h"

namespace Engine {
	using GlobalFuncPtr = void(*) (StrongPointer<GameObject>);

	extern std::map<std::string, GlobalFuncPtr> * ControllerMapping;

	void RegisterController(std::string ControllerName, GlobalFuncPtr ControllerFactory);
	void CreateGO(const char * luaScript);
}