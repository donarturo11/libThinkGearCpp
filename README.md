# About
LibThinkGearCpp is a library to handling ThinkGear. 
Entire code is rewritten in c++ basing on ofxThinkGear from [BrainwaveOSC](https://github.com/trentbrooks/BrainWaveOSC) by [trentbrooks](https://github.com/trentbrooks).
The goal of this project is make independent of frameworks

# Build
In square parenthesis is a option to build example projects to test or find own inspiration for own projects.
Type:
```
cd libThinkGearCpp
mkdir build
cd build
cmake .. [-DCOMPILE_PROJECTS=1]
cmake --build .
cmake --install .
```

# Usage
To use this library, you can add to CMakeLists.txt
```
find_package(thinkgearcpp)
```
and
```
target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp)
```

In Makefile add to CFLAGS or CXXFLAGS ```-lthinkgearcpp```

# Contact
To contact me, please use my [contact form](https://freeshell.de/~arturwro/contact.php?lang=en)
