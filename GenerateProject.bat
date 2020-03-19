COPY PremakeFiles\GLFW\premake5.lua XEngine\Dependencies\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\Dependencies\ImGui
CALL Dependencies\bin\premake\premake5.exe vs2019
PAUSE