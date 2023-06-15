# About
LibThinkGearCpp is a library to handling ThinkGear. 
Entire code is rewritten in c++ basing on ofxThinkGear from [BrainwaveOSC](https://github.com/trentbrooks/BrainWaveOSC) by [trentbrooks](https://github.com/trentbrooks).
The goal of this project is make independent of frameworks

# Build
Type:
```
cd libThinkGearCpp
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .
```

# Usage
To use this library, you add to CMakeLists.txt
```
find_package(thinkgearcpp)
```
and
```
target_link_libraries(${PROJECT_NAME} PUBLIC thinkgearcpp)
```

In header/source files in C/C++ add:
```
#include "thinkgearcpp/ThinkGear.h"
```

In Makefile add to CFLAGS or CXXFLAGS ```-L[thinkGearCpp path] -I[thinkGearCpp path] -lthinkgearcpp```

For more info see [examples](https://github.com/donarturo11/libThinkGearCpp/tree/main/examples) subdirectory.

# Contact
To contact me, please use my [contact form](https://freeshell.de/~arturwro/contact.php?lang=en)
