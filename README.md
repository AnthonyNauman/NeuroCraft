<p align="center">
 <h1 align="center">NeuroCraft</h2>
</p>

NeuroCraft is a neurual networks constructor  in C++. 
It aims to provide a solid foundation for creating any neural network architectures and training them. Currently in the early stages of development.

## Supported compilers
- [x] MSVC (Stable)
- [x] MinGW
- [ ] Clang
- [x] GCC

## Supported platforms
- [x] Windows 10
- [ ] Linux (in development)

## Used libraries
  * [ImGUI](https://github.com/ocornut/imgui)
  * [glad](https://glad.dav1d.de)
  * [GLWF](https://github.com/glfw/glfw/tree/latest)
  * [glm](https://github.com/g-truc/glm/tree/master)
  * [spdlog](https://github.com/gabime/spdlog/tree/master)
  * [json](https://github.com/nlohmann/json)

## Branches 
 * master - branch for releases
 * develop - active development branch 
 * feature/* - branches for new features
 * tmp/* - temporary branches for experiments

## Building  

 ### Cloning repo
1. ```Clone repository ```
 ```bash
 git clone https://github.com/AnthonyNauman/NeuroCraft.git
 ```
2. ```Enter repo folder```
 ```bash
 cd NeuroCraft
 ```
3. ```Run command in repository folder```
```bash
git submodule update --init --recursive
```
4. ```Switch to the "develop" (or another one) branch```
 ```bash
 git switch develop
 ```

 ### Build with CMake & Visual Studio:
> [!IMPORTANT]
> ```Requirements:```
> - Visual Studio 2019 or newer
> - Install [MS Build Tools](https://download.visualstudio.microsoft.com/download/pr/996d318f-4bd0-4f73-8554-ea3ed556ce9b/9610a60ad452c33dd3f9e8d3b4ce5d88d278f8b063d88717e08e1c0c13c29233/vs_BuildTools.exe) 
> - Install CMake 3.16.0 or newer

1. ```Create build folder and enter it```
```bash
mkdir build
cd build
```
2. ```Generate Visual Studio solution. Choose an available generator after the -G flag```
```bash
cmake -G "Visual Studio 17 2022" ..
```
3. ```Open Visual Studio solution```

4. ```Run build```

 ### Build with MinGW & GCC
> [!IMPORTANT]
> ```Requirements:```
> - Install CMake 3.16.0 or newer
> - Install gcc (use [MSYS2](https://www.msys2.org) for install gcc on Windows)

1. ```Create build folder and enter it```
```bash
mkdir build
cd build
```
2. ```Generate Makefile```
```bash
cmake -G "MinGW Makefiles" ..
```
3. ```Build```
```bash
cmake --build .
```


 
    



  
  <!-- ## Features -->
