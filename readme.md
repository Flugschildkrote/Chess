# 3D Chess 
![Preview](preview.jpg?raw=true "Preview")
## Context 
I started this project during my second year in High School (2015) and it was one of my very first project in programming. At the time I just started learning about programming on my own and i was trying to learn about video games, so this project was quite huge and took me some time. 

## Warning 
If you ever want read the code and get portions of it, be aware that it may contain dangerous sections like buffer overflows and memory leaks. The code was never modified since 2015 (excepted for some compile error fixes on vs2019)

## Not working 
- Check / checkmate detection not working properly. There are sometimes false positives. 
- 
## Build from sources
To build this project you need premake5 (available [here](https://premake.github.io/download)) and Visual Studio. This project is only tested on Windows with the Visual Studio 2019 IDE. No guarantees are made regarding other platforms. To build this project run `premake5 vs2019`. This will generate a solution (.sln) in the projects/vs2019 directory. 
To run the binary outside of visual studio, the executable must be started from the root directory.