COPY PremakeFiles\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\vendor\ImGui
COPY PremakeFiles\XEngine\premake5.lua
CALL vendor\premake\premake5.exe vs2019
RMDIR /Q /S PremakeFiles
DEL premake5.lua
DEL GenerateProject.bat
