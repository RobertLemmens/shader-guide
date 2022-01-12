# Shader guide

## How to install
### Prerequisites
Make sure you have a command line that can compile C code. (check if you can execute the `cl` command, things should work if you can). 
Another good idea is to have an IDE that knows how cmake works and generates and builds things for you.
### Steps
Commandline:
1. Do a recursive clone `git clone --recursive https://github.com/RobertLemmens/shader-guide.git`
2. Run `build.bat` (windows) or `build.sh` (unix)

Cmake should configure, build and run the application


IDE:
1. Do a recursive clone `git clone --recursive https://github.com/RobertLemmens/shader-guide.git`
2. Import the cmake project into your IDE of choice. Things should work.

### Running
When running the application, keep in mind that your working directory must be the root of this project, 
else the application won't be able to find the shaders.