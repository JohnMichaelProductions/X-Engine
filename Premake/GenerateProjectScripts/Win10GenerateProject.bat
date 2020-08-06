@echo off
PUSHD ..\..\
COPY Premake\Files\GLFW\premake5.lua X-Engine\vendor\GLFW\
COPY Premake\Files\ImGui\premake5.lua X-Engine\vendor\ImGui
COPY Premake\Files\GLAD\premake5.lua X-Engine\vendor\GLAD
COPY Premake\Files\X-Engine\premake5.lua
CALL Premake\Premake\premake5.exe vs2019
DEL premake5.lua
DEL X-Engine\vendor\GLAD\premake5.lua
DEL X-Engine\vendor\ImGui\premake5.lua
DEL X-Engine\vendor\GLFW\premake5.lua
POPD
PAUSE