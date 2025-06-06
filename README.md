# UE4Source_iOS

## Overview

The **UE4Source_iOS** project aims to port external Unreal Engine 4 (UE4) source code, originally developed for Windows, to be compatible with Apple's iOS platform by creating a dynamic library (`.dylib`). This enables the integration of existing UE4 functionalities into iOS applications, facilitating cross-platform development and deployment.

## Repository Contents

- `Cheats.cpp` / `Cheats.h`: Implements cheat functionalities tailored for iOS compatibility.
- `Tweak.xm`: (Equivalent to Windows' `Main.cpp`) Serves as the primary entry point for the dynamic library.
- `Memory.cpp` / `Memory.h`: Manages memory operations, ensuring efficient handling within the iOS environment.
- `Offsets.h`: Contains memory offset definitions pertinent to iOS.
- `classes.cpp`: Provides implementations for the classes defined in `Classes.h`.
- `Classes.h`: Defines core classes and data structures essential for the project.
- `MemX/`: Sources for the **MemX-Jailed** library used for memory access in jailed environments.
- Theos build files (`Makefile`, `control`, etc.) for creating jailbreak packages.


## Build and Package

1. **Install Theos**
   - Ensure the Xcode command line tools are installed on macOS.
   - Follow the [Theos installation guide](https://github.com/theos/theos/wiki/Installation) to clone the framework and export the `THEOS` environment variable.
2. **Create the package**
   - Run `make package` in the project directory to compile the dynamic library and generate a `.deb` file under `packages/`.

## MemX-Jailed Library

The project relies on the [`MemX-Jailed`](https://github.com/itsnebulalol/MemX-Jailed) library for memory access from a jailed iOS environment.

```objc
#import <MemX/MemX.h>

void example_read(uint64_t addr) {
    uint32_t value = 0;
    memx_read(task_self(), addr, &value, sizeof(value));
}
```
