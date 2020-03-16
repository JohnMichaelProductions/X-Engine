COPY PremakeFiles\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\vendor\ImGui
CALL vendor\bin\premake\premake5.exe vs2019
PAUSE