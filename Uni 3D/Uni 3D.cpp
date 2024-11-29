﻿#include <iostream>
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Window.h"
#include "Renderer.h"

int main(int argc, char* argv[]) 
{
    window.Init(1920 / 2, 1080 / 2);
    timer.Init(60);
    Camera camera;
    camera.MouseSensitivity = 1;
    camera.Zoom = 90;
    camera.OrthographicSize = 30 ;
    renderer.Init(&camera);

    while (!input.KeyPressed(SDLK_ESCAPE))
    {
        timer.Tick();
        if (timer.CanUpdate())
        {
            window.PollEvents();
            
            if (input.KeyPressed(SDLK_w))
                camera.ProcessKeyboard(FORWARD, timer.deltaTime / 1000);
            if (input.KeyPressed(SDLK_s))
                camera.ProcessKeyboard(BACKWARD, timer.deltaTime / 1000);
            if (input.KeyPressed(SDLK_d))
                camera.ProcessKeyboard(RIGHT, timer.deltaTime / 1000);
            if (input.KeyPressed(SDLK_a))
                camera.ProcessKeyboard(LEFT, timer.deltaTime / 1000);
            
            if (input.KeyPressedOnce(SDLK_f))
                renderer.ChangeProjection();

            camera.ProcessMouseMovement(input.mouseX, -input.mouseY);

            renderer.Draw();

            window.SwapWindow();
        }
    }

    window.DeleteContext();
    return 0;
}