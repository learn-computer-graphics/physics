# Physics

Basics dynamics used in real-time rendering simulations

## Projects

#### 01 Cloth simulation

![cloth](doc/project-01.png)

## Getting started

### Prerequisites

You need to install the CMake build system and a modern C++ compiler.

#### Linux

```
sudo apt-get install build-essential cmake
```

#### Windows

To get the MSVC compiler, you need to install [Visual Studio](https://visualstudio.microsoft.com/fr/) (and not VSCode) and select the C++ development package during install. You also need to install [CMake](https://cmake.org/) which can also be done by visual studio.

### Build

You can handle the `CMakeLists.txt` in any way you like, here's some way to use it :

#### `Option 1: CLI`

Go to the folder of this project and run :

```bash
mkdir build
cd build
cmake ..
make
```

#### `Option 2: Visual Studio (Windows only)`

Open this folder with the `CMake...` option in file->open on Visual Studio, and run the project.


#### `Option 3: VSCode`

Use the `CMakeTools` plugin, build with `f7` then run with `f5` (But be careful to be on the right platform, there is a launch file for windows and for linux).

### Launch

Simply open the `project01` file generated in the build directory and run it

## Sources

### Classes

| Name | Description |
| --- | --- |
| [M2 classes at Université Gustave Eiffel by Eric Incerti](https://nimbus.u-pem.fr/s/aTfzNXokqH6pexC?path=%2F) | |
| [Animation and simulation at Stanford by Doug James](http://graphics.stanford.edu/courses/cs348c/) | |
| [Modelling simulation nature processes by Coursera](https://www.coursera.org/learn/modeling-simulation-natural-processes) | |
| [Pixar in a box](https://www.khanacademy.org/computing/pixar) | |
| [Physics-based animation at University of Waterloo by Christopher Batty](https://cs.uwaterloo.ca/~c2batty/courses/CS888_2014/) | |
| [GDC - Technical Artist Bootcamp: Real-Time Cloth Solutions on 'Marvel's Spider-Man'](https://gdcvault.com/play/1025663/Technical-Artist-Bootcamp-Real-Time) | |

### Videos

| Name | Description |
| --- | --- |
| [GDC - Physics for game programmers, continuous collision](https://www.youtube.com/watch?v=7_nKOET6zwI) | |
| [GDC - Physics for game programmers, understanding constraints](https://www.youtube.com/watch?v=SHinxAhv1ZE) | |
| [GDC - Valve's physics for game programmers](https://www.youtube.com/watch?v=1RphLzpQiJY) | |
| [GDC - Cloth Self Collision with Predective Contacts](https://www.youtube.com/watch?v=XUsD3xrNJH0) | |
| [GDC - Ubisoft Cloth Simulation: Performance Postmortem and Journey from C++ to Compute Shaders](https://www.gdcvault.com/play/1022350/Ubisoft-Cloth-Simulation-Performance-Postmortem) | |
| [Inspecto - But how do Soft body simulations work ?](https://www.youtube.com/watch?v=kyQP4t_wOGI) | |
| [Two Minute Papers - Why are cloth simulations so hard ?](https://www.youtube.com/watch?v=UoKXJzTYDpw) | |

### Books

| Name | Description | Illustration |
| --- | --- | --- |
| [Fluid engine development](https://fluidenginedevelopment.org/) | | <img width="80" src="https://fluidenginedevelopment.org/assets/images/main/cover.png"> |
| [Foundations of Physically Based Modeling and Animation](https://www.cs.clemson.edu/savage/pba/) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/5130wQv0K4L._SX343_BO1,204,203,200_.jpg"> |
| [Game Physics Engine Development](http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Ian_Millington-Game_Physics_Engine_Development-EN.pdf) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/51wASB8fXcL.jpg"> |
| [Game Physics Pearls](https://www.amazon.fr/Game-Physics-Pearls-Gino-Bergen/dp/1568814747) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/5169anjHnOL._SX320_BO1,204,203,200_.jpg"> |
| [Physics for game programmers](https://www.amazon.fr/Physics-Game-Programmers-Grant-Palmer/dp/159059472X) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/71mDHlhXdUL.jpg"> |
| [Physics for game developers, 2nd edition](https://www.amazon.fr/Physics-Game-Developers-David-Bourg/dp/1449392512) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/71IdeyuYgSL.jpg"> |
| [Physics modeling for game programmers](https://www.amazon.fr/Physics-Modeling-Programmers-J-Robert-Ellis/dp/1592000932) | | <img width="80" src="https://images-na.ssl-images-amazon.com/images/I/51esKyMOd8L.jpg"> |
| [Game physics, 2nd edition](https://www.amazon.com/Physics-Second-Eberly-David-Hardcover/dp/B009O3BQGQ) | | <img width="80" src="https://images.routledge.com/common/jackets/originals/978012374/9780123749031.tif"> |
| [OpenGL 4 Shading Language Cookbook 3rd edition](https://www.amazon.fr/OpenGL-Shading-Language-Cookbook-high-quality-ebook/dp/B07HXYJ9VT) | The code repository can be found [here](https://github.com/PacktPublishing/OpenGL-4-Shading-Language-Cookbook-Third-Edition). Check chapter 11 for cloth simulation. | <img width="80" src="https://m.media-amazon.com/images/I/41Ldhjbj4CL.jpg"> |

### Papers

| Name                                                         | Year | Description |
| ------------------------------------------------------------ | ---- | ----------- |
| [Fast Simulation of Mass-Spring Systems](https://www.cs.utah.edu/~ladislav/liu13fast/liu13fast.html) | 2013 |             |

### Libraries

| Name | Description |
| --- | --- |
| [NVidia PhysX](https://github.com/NVIDIAGameWorks/PhysX) | |
| [Bullet](https://pybullet.org/wordpress/) | |
| [Box2D](https://box2d.org/) | |

### Repositories

| Name                                                         | Description |
| ------------------------------------------------------------ | ----------- |
| [Cloth Simulation in OpenGL](https://github.com/torresf/cloth-simulation) |             |
| [Cloth Simulation Viewer](https://github.com/dragonbleapiece/flag-viewer) |             |
| [Fast Mass Spring](https://github.com/sam007961/FastMassSpring) |             |
| [OpenGL Cloth](https://github.com/bailus/Cloth)              |             |

