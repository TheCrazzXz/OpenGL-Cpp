g++ main.cpp include/glad/glad.c include/stb/stb.cpp -I include -o game -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lassimp

if [ $? -eq 0 ]; then
    echo "Command Executed Successfully"
    ./game
else
    echo "Command Failed"
fi
