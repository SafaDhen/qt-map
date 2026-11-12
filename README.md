# Qt Map

A small Google-Maps-style map application written in C++ with Qt.

University project, Hochschule Darmstadt (semester 2, solo ).



## Features

- [ e.g. load map data from a file]
- [ e.g. display roads and places]
- [ e.g. find the shortest route between two places]
- [ e.g. search for a place by name]


## Tech stack

C++, Qt Widgets, CMake

## Build and run

Requirements: Qt 6 (Widgets) , CMake, a C++17 compiler.

```bash
git clone https://github.com/SafaDhen/qt-map.git
cd qt-map
cmake -S . -B build
cmake --build build
```

Alternatively, open `CMakeLists.txt` in Qt Creator and press Run.

## What I learned

- How to build an Object-oriented design with inheritance, graph algorithms (Dijkstra), geomathematics (Haversine), advanced Qt GUI programming including custom painting, file serialization
- , unit testing, and build systems – embedded in a realistic navigation system project.
