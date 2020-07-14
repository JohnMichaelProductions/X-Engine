@echo off
PUSHD ..\..\
COPY Premake\Files\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY Premake\Files\ImGui\premake5.lua XEngine\vendor\ImGui
COPY Premake\Files\GLAD\premake5.lua XEngine\vendor\GLAD
COPY Premake\Files\XEngine\premake5.lua
CALL Premake\premake\premake5.exe vs2019
DEL premake5.lua
DEL XEngine\vendor\GLAD\premake5.lua
DEL XEngine\vendor\ImGui\premake5.lua
DEL XEngine\vendor\GLFW\premake5.lua
POPD
PAUSE