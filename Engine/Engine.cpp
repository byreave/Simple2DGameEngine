#include "Engine.h"
#include <assert.h>
#include <iostream>
#include "ConsoleLog.h"
#include "Input.h"
#include "PhysicsSystem.h"
#include "Renderable.h"
#include "Collision.h"
#include "LuaCreateGO.h"
#include "BaseController.h"
std::vector<Engine::StrongPointer<Engine::GameObject>> Engine::AllGameObjects;
std::vector<Engine::Physics::PhysicsSystem *> Engine::Physics::PhysicsInfo;
std::vector<Engine::Render::Renderable *> Engine::Render::RenderableInfo;
std::vector<Engine::CollisionSystem::Collision *> Engine::CollisionSystem::CollisionObjects;
std::vector<Engine::Controller::BaseController *> Engine::Controller::Controllers;
std::map<std::string, Engine::GlobalFuncPtr> * Engine::ControllerMapping = new std::map<std::string, Engine::GlobalFuncPtr>();

bool Engine::Startup(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//PressToMove pressToMove;
	Input::Init();
	/*Input::ButtonChangeReceivers.AddDelegate(
		Input::ButtonChangeReceiver_t::Create<PressToMove, &PressToMove::TestKeyCallback>(&pressToMove)
	);*/
	//Delegates__UnitTest();
	// IMPORTANT: first we need to initialize GLib
	return GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
}

void Engine::Shutdown()
{
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}
GLib::Sprites::Sprite * Engine::CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = Engine::LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture;
	if (pTextureFile)
		pTexture = GLib::CreateTexture(pTextureFile, sizeTextureFile);
	else
		pTexture = nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
	{
		delete[] pTextureFile;
	}

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void * Engine::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
	{
		DEBUG_PRINT("ERROR: ", "File Open Error!\n");
		return NULL;
	}

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

