COPY PremakeFiles\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\vendor\ImGui
RMDIR /Q /S PremakeFiles
CALL vendor\premake\premake5.exe vs2019
DEL GenerateProject.bat