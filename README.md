# Pong

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)

## About <a name = "about"></a>

It's a basic engine created in C++ using SDL2 as a library for rendering the project. In the engine, the use of colliders was implemented for entities, and collision detection is performed using AABB to determine if there was a collision.
## Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

What things you need to install the software and how to install them.

- C++20
- CMake Version 3.27
- SDL2
- glm
- entt


## Usage <a name = "usage"></a>

Before you can use the provided scripts, you may need to grant them execution permissions. To do this, open your terminal and navigate to the project directory. Then, run the following commands:

```shell
chmod +x run.sh build.sh configure.sh
```

To run CMake and execute the build, run the following command:
```
 ./run.sh 
```

To delete the build run the following command:
```
./clean.sh 
```

