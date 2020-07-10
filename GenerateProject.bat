COPY PremakeFiles\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\vendor\ImGui
COPY PremakeFiles\GLAD\premake5.lua XEngine\vendor\GLAD
COPY PremakeFiles\XEngine\premake5.lua
CALL vendor\premake\premake5.exe vs2019
DEL premake5.lua
DEL XEngine\vendor\GLAD\premake5.lua
DEL XEngine\vendor\ImGui\premake5.lua
DEL XEngine\vendor\GLFW\premake5.lua
PAUSE