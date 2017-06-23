# SFGE - Simple and fast game engine

This library is open source 2D game engine based on SFML. It is written in C++ and provide access to features provided by SFML (except network), GUI, resources manager and some additional graphic features.<br>
Additional library provide some features for creating 2D RPG.<br>

## Structure of project
- 3rd_party - all dependencies of project
    - [Catch](https://github.com/philsquared/Catch)
    - [SFML](http://www.sfml-dev.org/download.php)
    - SFML_vs - VS project for building SFML
    - [minizip](https://github.com/nmoinvaz/minizip)
    - minizip_vs - VS project for building minizip
    - [zlib](https://github.com/madler/zlib)
    - zlib_vs - VS project for building zlib
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
To use this library you should download [SFML](http://www.sfml-dev.org/download.php). Currently library work with SFML 2.4.2.<br>
Library [Catch](https://github.com/philsquared/Catch) is used for unit-testing.<br>
Libraries [zlib](https://github.com/madler/zlib) and [minizip](https://github.com/nmoinvaz/minizip) were used for working with zip files.<br>
Project is developed on Windows platform but it works (generally) on Linux too.<br>

## Quick start
To start using game engine you should download this project by command:<br>
`git clone --recursive https://github.com/DonRumata710/SFGE.git`<br>
Then you should build 3rd-party libraries in folder "3rd-party": SFML, zlib, minizip. You can use VS projects from folders called "*_vs" for this. If you use cmake you should not build zlib and minizip - they will be automatically created by main project.<br>

## Additional resources
Also in example of project were used fonts [PT Sans](https://fonts.google.com/)<br>

## Author
DonRumata710 (donrumata710@yandex.com)<br>
