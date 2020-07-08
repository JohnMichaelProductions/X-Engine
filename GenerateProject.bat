ECHO OFF
COPY PremakeFiles\GLFW\premake5.lua XEngine\vendor\GLFW\
COPY PremakeFiles\ImGui\premake5.lua XEngine\vendor\ImGui
COPY PremakeFiles\XEngine\premake5.lua
CALL vendor\premake\premake5.exe vs2019
ECHO IMPORTANT!!! If you are using this for development don't delete the premake files(press no when it prompts for deletion), if you are using this in release you can delete the files
PAUSE
RMDIR /S PremakeFiles
IF EXIST PremakeFiles\XEngine\premake5.lua EXIT
DEL premake5.lua
DEL GenerateProject.bat
