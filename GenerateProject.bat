COPY PremakeFiles\GLFW\premake5.lua XEngine\Dependencies\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\Dependencies\vendor\ImGui
CALL Dependencies\premake\premake5.exe vs2019
PAUSE