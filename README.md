# X-Engine
Repository for X-Engine. A fast, efficient, easy to use 2D Game Engine. Currently under production and unstable.

## Set-Up
Currently this is the way to set up X-Engine:

1. Cloning: Go to into command prompt and type:
```
git clone https://github.com/JohnMichaelProductions/X-Engine.git
```
2. Updating Submodules: In order to update and clone submodules into the repository(they are needed), go into command prompt inside the repository and type:
```
git submodule init
git submodule update
```
3. Go into the 'PremakeFiles' folder and copy and paste the premake files(GLFW, ImGui) into their respective sub repository, they are located in XEngine/vendor/GLFW and ImGui(Replace the file GLFW's repository). This task should be automated soon.

4. Run the GenerateProject.bat file.

5. Run the solution file at the top of the repository, when you are in visual studios, build the project and X-Engine will run(If it doesn't work the first time, build again).

For questions, concerns, or a bug report email: XOS.Development.Main@gmail.com
