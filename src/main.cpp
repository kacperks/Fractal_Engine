#include "fractal.hpp"

using namespace std;
using namespace fr;
using namespace ECS;

string font[2];
string graphics[6];

bool debug = false;

void setup(){
            font[0] = "../res/Fonts/Roboto-Black.ttf";
            font[1] = "../res/Fonts/Roboto-BlackItalic.ttf";
            font[2] = "../res/Fonts/Roboto-Bo";

            graphics[0] = "../res/Graphics/add.png";
            graphics[1] = "../res/Graphics/camera.png";
            graphics[2] = "../res/Graphics/Logo.png";
            graphics[3] = "../res/Graphics/mesh render.png";
            graphics[4] = "../res/Graphics/remove.png";
            graphics[5] = "../res/Graphics/RigidBody.png";
            graphics[6] = "../res/Graphics/transform.png";
}

int main(){
    setup();
}