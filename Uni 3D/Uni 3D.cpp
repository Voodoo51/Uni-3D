#include <iostream>
#include <SDL2/SDL.h>
#include "Timer.h"
#include "Window.h"
#include "Map.h"
#include "Player.h"
#include "Renderer.h"

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
    map.Init();
    player.Init();
    //player.SetMap(map);

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
            
            if (input.KeyPressedOnce(SDLK_l))
                renderer.ChangeProjection();

            //camera.ProcessMouseMovement(input.mouseX, -input.mouseY);
            player.Update();
            vec3 target = renderer.modelRenders.Get(player.model).pos;
            target.y = 10;
            renderer.SetView(target);
            renderer.Draw();

            window.SwapWindow();
        }
    }

    window.DeleteContext();
    return 0;
}
