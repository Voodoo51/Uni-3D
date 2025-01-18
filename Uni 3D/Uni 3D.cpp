#include <iostream>
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Window.h"
#include "Map.h"
#include "Player.h"
#include "GameManager.h"
#include "Renderer.h"

bool Camera::freeFlightOn = false;

int main(int argc, char* argv[]) 
{
    window.Init(1920 / 1, 1080 / 1);
    timer.Init(70);
    Camera camera;
    camera.Position = vec3(0, 2, 0);
    camera.MouseSensitivity = 1;
    camera.Zoom = 90;
    camera.OrthographicSize = 30 ;
    renderer.Init(&camera);
    gameManager.Init();
    player.Init();

    while (!input.KeyPressed(SDLK_ESCAPE) && !window.quit)
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
            if (input.KeyPressed(SDLK_RIGHT))
                renderer.lightPos += vec3(timer.deltaTime / 10, 0, 0);
            if (input.KeyPressed(SDLK_LEFT))
                renderer.lightPos += vec3(-timer.deltaTime / 10, 0, 0);
            if (input.KeyPressed(SDLK_UP))
                renderer.lightPos += vec3(0, 0, -timer.deltaTime / 10);
            if (input.KeyPressed(SDLK_DOWN))
                renderer.lightPos += vec3(0, 0, timer.deltaTime / 10);

            fadeInOut.Update();

            if (input.KeyPressedOnce(SDLK_0))
            {
                renderer.lightPos += vec3(0, -1, 0);
                std::cout << "Y POS: " << renderer.lightPos.y << std::endl;
            }
            if (input.KeyPressedOnce(SDLK_1))
            {
                renderer.lightPos += vec3(0, 1, 0);
                std::cout << "Y POS: " << renderer.lightPos.y << std::endl;
            }
            if (input.KeyPressedOnce(SDLK_l))
                renderer.ChangeProjection();
            if (input.KeyPressedOnce(SDLK_j))
                Camera::freeFlightOn = !Camera::freeFlightOn;

            player.Update();
            if (Camera::freeFlightOn)
            {
                camera.ProcessMouseMovement(input.mouseX, -input.mouseY);
                renderer.SetView(camera.GetViewMatrix());
            }
            else
            {
                camera.Up = vec3(0, 1, 0);
                vec3 target = renderer.modelRenders.Get(player.model).pos;
                target.y = 10;
                renderer.SetView(target);
            }
            
            renderer.Draw();

            window.SwapWindow();
        }
    }

    window.DeleteContext();
    return 0;
}
