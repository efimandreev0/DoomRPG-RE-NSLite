//Using SDL and standard IO
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <zlib.h>

#include "Z_Zone.h"
#include "DoomRPG.h"
#include "DoomCanvas.h"
#include "Player.h"
#include "Hud.h"
#include "MenuSystem.h"
#include "SDL_Video.h"
#include "Z_Zip.h"
#ifdef __aarch64__
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "logger.h"

#include <switch.h>
#endif

extern DoomRPG_t* doomRpg;
void printfile(const char* path)
{
	FILE* f = fopen(path, "r");
	if (f) {
		char mystring[100];
		while (fgets(mystring, sizeof(mystring), f)) {
			int a = strlen(mystring);
			if (mystring[a-1] == '\n') {
				mystring[a-1] = 0;
				if (mystring[a-2] == '\r')
				{
					char mystring[100];
					while (fgets(mystring, sizeof(mystring), f))
					{
						int a = strlen(mystring);
						if (mystring[a-1] == '\n')
						{
							mystring[a-1] = 0;
							if (mystring[a-2] == '\r')
								mystring[a-2] = 0;
						}
						puts(mystring);
					}
					printf(">>EOF<<\n");
					fclose(f);
				} else {
					printf("errno is %d, %s\n", errno, strerror(errno));
				}
			}
		}
	}
}

int main(int argc, char* args[])
{
	SDL_Event ev;
	int		UpTime = 0;
	int		mouseTime = 0;
	int		key, oldKey, mouse_Button;

	Z_Init();
	SDL_InitVideo();
	SDL_InitAudio();
	//openZipFile("sdmc:/switch/DoomRPG.zip", &zipFile);

	/*int size;
	byte* data;
	data = readZipFileEntry("c.bmp", &zipFile, &size);

	SDL_RWops* rw;
	rw = SDL_RWFromFile("c.bmp", "w");
	SDL_RWwrite(rw, data, sizeof(byte), size);
	SDL_RWclose(rw);

	SDL_free(data);

	closeZipFile(&zipFile);*/

	if (DoomRPG_Init() == 0) {
		DoomRPG_Error("Failed to initialize Doom Rpg\n");
	}

	//Hud_addMessage(doomRpg->hud, "Bienvenido a Doom RPG por GEC...");
#ifdef __aarch64__
	padConfigureInput(1, HidNpadStyleSet_NpadStandard);

	// Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
	PadState pad;
	padInitializeDefault(&pad);
	u64 kDown = padGetButtonsDown(&pad);
#else
	const Uint8* state = (const Uint8*)SDL_GameControllerGetButtonID();
#endif

	key = 0;
	oldKey = -1;

#ifdef __aarch64__
	//logger_init();
	//logger_write("Reached main loop.");
	Result rc = fsdevMountSdmc();
	if (R_FAILED(rc))
		printf("romfsInit: %08X\n", rc);
	else
	{
		printf("romfs Init Successful!\n");
	}
#endif
	
	while (doomRpg->closeApplet != true
		#ifdef __aarch64__
	&& appletMainLoop()
#endif
	)
	{
		int currentTimeMillis = DoomRPG_GetUpTimeMS();

		mouse_Button = MOUSE_BUTTON_INVALID;

		while (SDL_PollEvent(&ev))
		{
			// check event type
			switch (ev.type) {

				// Mouse Event
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				{
					Uint32 buttons = SDL_GetMouseState(NULL, NULL);

					if ((buttons & SDL_BUTTON_LMASK) != 0) {
						mouse_Button = MOUSE_BUTTON_LEFT;
					}
					else if ((buttons & SDL_BUTTON_MMASK) != 0) {
						mouse_Button = MOUSE_BUTTON_MIDDLE;
					}
					else if ((buttons & SDL_BUTTON_RMASK) != 0) {
						mouse_Button = MOUSE_BUTTON_RIGHT;
					}
					else if ((buttons & SDL_BUTTON_X1MASK) != 0) {
						mouse_Button = MOUSE_BUTTON_X1;
					}
					else if ((buttons & SDL_BUTTON_X2MASK) != 0) {
						mouse_Button = MOUSE_BUTTON_X2;
					}
					break;
				}

				case SDL_MOUSEWHEEL:
				{
					if (currentTimeMillis > mouseTime) {
						mouseTime = currentTimeMillis + 128;
						if (ev.wheel.y > 0) {
							mouse_Button = MOUSE_BUTTON_WHELL_UP;
						}
						else if (ev.wheel.y < 0) {
							mouse_Button = MOUSE_BUTTON_WHELL_DOWN;
						}
					}
					break;
				}

				case SDL_MOUSEMOTION:
				{
					if (!doomRpg->menuSystem->setBind) {
						if (currentTimeMillis > mouseTime) {
							mouseTime = currentTimeMillis + 128;
							int x = 0, y = 0;
							SDL_GetRelativeMouseState(&x, &y);

							int sensivity = (doomRpg->doomCanvas->mouseSensitivity * 1000) / 100;

							if (x <= -sensivity) {
								mouse_Button = MOUSE_BUTTON_MOTION_LEFT;
							}
							else if (x >= sensivity) {
								mouse_Button = MOUSE_BUTTON_MOTION_RIGHT;
							}

							if (doomRpg->doomCanvas->mouseYMove) {
								if (y <= -sensivity) {
									mouse_Button = MOUSE_BUTTON_MOTION_UP;
								}
								else if (y >= sensivity) {
									mouse_Button = MOUSE_BUTTON_MOTION_DOWN;
								}
							}
						}
					}
					break;
				}
				
				case SDL_WINDOWEVENT:
				{
					if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
						//printf("MESSAGE:Resizing window...\n");
						//SDL_Rect rect = { 0,0,640,480};
						//SDL_RenderSetViewport(sdlVideo.renderer, &rect);
						//resizeWindow();
					}

					if (ev.window.event == SDL_WINDOWEVENT_CLOSE) {
						SDL_Log("Window %d closed", ev.window.windowID);
						closeZipFile(&zipFile);
						DoomRPG_FreeAppData(doomRpg);
#ifndef __aarch64__
						SDL_CloseAudio();
#endif
						SDL_Close();
						exit(0);
						break;
					}

					if (ev.window.event != SDL_WINDOWEVENT_CLOSE)
					{
						int w, h;
						SDL_GetWindowSize(sdlVideo.window, &w, &h);
						SDL_WarpMouseInWindow(sdlVideo.window, w / 2, h / 2);
						SDL_GetRelativeMouseState(NULL, NULL);
					}
					break;
				}

				case SDL_QUIT:
				{
					// shut down
					exit(0);
					break;
				}
			}

			key = DoomRPG_getEventKey(mouse_Button,
#ifdef __aarch64__
			pad
#else
			state
#endif
			);
			if (key != oldKey) {
				//printf("oldKey %d\n", oldKey);
				//printf("key %d\n", key);

				oldKey = key;
				if (!doomRpg->menuSystem->setBind) {
					DoomCanvas_keyPressed(doomRpg->doomCanvas, key);
				}
				else {
					goto setBind;
				}
			}
			else if (key == 0) {
			setBind:
				if (doomRpg->menuSystem->setBind) {
					//DoomRPG_setBind(doomRpg, mouse_Button, state);
				}
			}
		}
		
		if (currentTimeMillis > UpTime) {
			UpTime = currentTimeMillis + 15;
			DoomRPG_loopGame(doomRpg);
		}
	}

	closeZipFile(&zipFile);
	DoomRPG_FreeAppData(doomRpg);
#ifndef __aarch64__
	SDL_CloseAudio();
#endif
	SDL_Close();

	return 0;
}