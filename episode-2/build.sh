g++ main.cpp glad/glad.c -o game -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

if [ $? -eq 0 ]; then
    echo "Command Executed Successfully"
    ./game
else
    echo "Command Failed"
fi
