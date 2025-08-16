# SFGE - Simple and fast game engine

This library is open source 2D game engine based on SFML. It is written in C++ and provide access to features provided by SFML (except network), GUI, resources manager and some additional graphic features.<br>
Additional library provide some features for creating 2D RPG.<br>

## Structure of project
- CMakeModules - contains FindSFML.cmake
- SFGE_lib - main game engine library
- SFGE_test_app - test application
- SFRPG_lib - library for isometric RPG
- SFRPG_unittest - unittests for rpg library
- SFRPG_map_editor - application for generating and editing maps (WIP)
- include
    - SFGE - headers of SFGE_lib
    - SFRPG - headers of SFRPG_lib

## Requirement
The engine relies on several external libraries:
- [SFML](http://www.sfml-dev.org/download.php)
- [Catch2](https://github.com/catchorg/Catch2)
- [minizip](https://github.com/nmoinvaz/minizip)
- [zlib](https://github.com/madler/zlib)

These dependencies are no longer stored in the repository. They are downloaded and
built automatically using CMake's `ExternalProject_Add` when configuring the project.
Project is developed on Windows platform but it works (generally) on Linux too.<br>

## Quick start
To start using game engine you should download this project by command:<br>
`git clone https://github.com/DonRumata710/SFGE.git`<br>
All required third party libraries are fetched and built during configuration, so
no manual setup of the `3rd_party` folder is necessary.<br>

## Additional resources
Also in example of project were used fonts [PT Sans](https://fonts.google.com/)<br>

## Author
DonRumata710 (donrumata710@yandex.com)<br>
