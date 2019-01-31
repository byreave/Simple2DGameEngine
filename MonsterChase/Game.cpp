#include<iostream>
#include<stdlib.h> //random
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
#include "ConsoleLog.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include "Game.h"
#include "Clock.h"
//#include <vector>
#include "Character.h"
#include "PhysicsSystem.h"

std::vector<Physics::PhysicsSystem *> Physics::PhysicsInfo;
std::vector<Character *> GameCharacters;
void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	if (i_VKeyID == 'a' || i_VKeyID == 'A')
	{
		if (bWentDown)
		{
			DEBUG_PRINT("Info", "A pressed!");
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(-100.0f, 0.0f);
			}
		}
		
	}
	else if (i_VKeyID == 'd' || i_VKeyID == 'D')
	{
		if (bWentDown)
		{
			DEBUG_PRINT("Info", "D pressed!");
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(100.0f, 0.0f);
			}
		}
	}
#ifdef _DEBUG
	/*const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);*/
#endif // __DEBUG
}

GLib::Sprites::Sprite * Game::CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
	{
		DEBUG_PRINT("ERROR: ", "Empty image file!\n");
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

void * Game::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
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

bool Game::Startup(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);
		GLib::Sprites::Sprite * pGoodGuy;
		// Create a couple of sprites using our own helper routine CreateSprite
		pGoodGuy = CreateSprite("data\\Tracer.dds");
		// Clock Time
		Timing::deltaTime = Timing::Clock::now();

		Character * tmpGoodGuy = new Character("Byreave", 3, Point2D<float>(0.0f, 150.0f), pGoodGuy);
		GameCharacters.push_back(tmpGoodGuy);

		Physics::PhysicsSystem * tmpPhysics = new Physics::PhysicsSystem(tmpGoodGuy);
		Physics::PhysicsInfo.push_back(tmpPhysics);
	}
	return bSuccess;
}

void Game::Run()
{  
	bool bQuit = false;

	do
	{
		// IMPORTANT: We need to let GLib do it's thing. 
		GLib::Service(bQuit);

		if (!bQuit)
		{
			float deltaTime = Timing::GetTimeSinceLastCall();
			//DEBUG_PRINT("Time: ", "Time Since Last Call : %f", Timing::GetTimeSinceLastCall());
			Physics::Update(deltaTime);
			DEBUG_PRINT("Debug", "Character x pos: %f", (*GameCharacters.begin())->GetPosition().getX());
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();
			

			for (auto renderObj = GameCharacters.begin(); renderObj != GameCharacters.end(); ++renderObj)
			{
				Character * c = *renderObj;
				GLib::Point2D tmpPoint;
				tmpPoint.x = c->GetPosition().getX();
				tmpPoint.y = c->GetPosition().getY();
				GLib::Sprites::RenderSprite(*(c->GetSprite()), tmpPoint, 0.0f);

			}
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}
	} while (bQuit == false);
}

void Game::Shutdown()
{
	for (auto gameObj = GameCharacters.begin(); gameObj != GameCharacters.end(); ++gameObj)
	{
		if(static_cast<Character *>(*gameObj)->GetSprite())
			GLib::Sprites::Release((*gameObj)->GetSprite());
		if (*gameObj)
		{
			delete *gameObj;
		}
	}
	GameCharacters.clear();
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}
