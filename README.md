# Manifold

Manifold is a C++ library that provides a collection of common utilities and tools for other projects. It aims to simplify development by offering reusable components and functions.

## Caveats

Manifold is currently in development and may not be ready for production use. The API is subject to change at any time. Additionally, the library requires the C++20 standard which may not be supported by all compilers.

## Features

- [x] Environment detection and utilities (getting environment variables, cpu count, etc.)
- [x] Filesystem utilities (path manipulation, file/directory creation, etc.)
- [x] String utilities (string splitting, string trimming, etc.)
- [x] Error handling utilities (Result type)
- [x] Useful C++ structures (BitFlags)
- [x] C++20 Concepts (EqualityComparable, CopyConstructible, etc.)
- [ ] Process utilities (process spawning, process termination, etc.)
- [ ] Threading utilities (thread spawning, thread termination, etc.)
- [ ] Networking utilities (socket creation, socket termination, etc.)
- [ ] Logging utilities (logging to stdout, logging to file, etc.)

## Installation

To include the Manifold library in your C++ project, you can use CMake's FetchContent module. Follow the steps below:

Add the following lines to your CMakeLists.txt file:

```cmake
include(FetchContent)

FetchContent_Declare(
  manifold
  GIT_REPOSITORY https://git.julesnieves.org/jules/manifold.git
  GIT_BRANCH main
)

FetchContent_MakeAvailable(manifold)
```

Then, you can link against the Manifold library in your CMakeLists.txt file:

```cmake
target_link_libraries(<target> PRIVATE manifold::manifold)
```

## Usage

To use the Manifold library in your C++ project, you can include the header files in your source files:

```cpp
#include <manifold/Environment.hpp>
```

or use the umbrella header:

```cpp
#include <manifold/manifold.hpp>
```

## License

Manifold is licensed under the MIT license. See [LICENSE](LICENSE) for more information.
