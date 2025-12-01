<!-- PROJECT LOGO -->
<div align="center">
<!-- <img src="assets/favicon.ico" alt="Logo" width="80" height="80"> -->
<h1> Tak </h1>
<p> The boardgame from the "King Killer Chronicles" novel series </p>

[![MIT-License](https://img.shields.io/badge/MIT-License-yellow?style=for-the-badge)](https://opensource.org/licenses/MIT)

[![Stars](https://img.shields.io/github/stars/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/stargazers)
[![Issues](https://img.shields.io/github/issues/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/issues)

[![Contributors](https://img.shields.io/github/contributors/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/graphs/contributors)
[![Forks](https://img.shields.io/github/forks/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/network/members)

</div>


## About The Project
**[Insert screenshot here](path/to/screenshot)**

Implementation of the two player board game from the novel series "King Killer Chronicles" by Patrick Rothfuss.

For more information about the game's rules, see [ustak.org](https://ustak.org/play-beautiful-game-tak/#)

### Code Directory Strcture
- Components:
  - Data only
  - Stored in container/array
  - Container represents association between an entity (id) and its component (value)
  - Optional: grouped in (entity-) struct

- Entities: Is an id; Used as index into component containers

- Systems: Logic only (on components/entities)

- Data: Constant, shared variables

- Configs: Changeable, shared variables

- Utility: Shared functions

<p align="right">(<a href="#readme-top">top</a>)</p>


### Dependencies
Dependencies that are or are planned to be used:
#### Toolchains (not provided)
[![make](https://img.shields.io/badge/toolchain-gnumake-darkred?style=for-the-badge)](https://www.gnu.org/software/make/)
[![clang](https://img.shields.io/badge/compiler-clang-blue?style=for-the-badge)](https://clang.llvm.org)
[![emscripten](https://img.shields.io/badge/toolchain-emscripten-green?style=for-the-badge)](https://github.com/emscripten-core/emscripten)

#### Tools (not provided)
[![clang-format](https://img.shields.io/badge/compiler-clang-blue?style=for-the-badge)](https://clang.llvm.org/docs/ClangFormat.html)
[![compiledb](https://img.shields.io/badge/generator-compiledb-white?style=for-the-badge)](https://github.com/nickdiego/compiledb)
[![doxygen](https://img.shields.io/badge/generator-doxygen-blue?style=for-the-badge)](https://www.doxygen.nl/)
[![cppcheck](https://img.shields.io/badge/analyser-cppcheck-darkblue?style=for-the-badge)](https://cppcheck.sourceforge.io/)

#### Libraries (provided)
[![ncurses](https://img.shields.io/badge/library-ncurses-white?style=for-the-badge)](https://github.com/mirror/ncurses)
[![raylib](https://img.shields.io/badge/library-raylib-white?style=for-the-badge)](https://github.com/raysan5/raylib)
[![catch2](https://img.shields.io/badge/testing-catch2-red?style=for-the-badge)](https://github.com/catchorg/Catch2)

<!-- #### Excluded -->

<p align="right">(<a href="#readme-top">top</a>)</p>


### Getting Started
#### Run

#### Develop and build
1. Install toolchain and tools

<p align="right">(<a href="#readme-top">top</a>)</p>


### Features

<p align="right">(<a href="#readme-top">top</a>)</p>


### (Desired) Development workflow
(Try first time with this project)
1. Create feature branch
1. Create necessary data structure
1. TDD:
    1. Fail test
    1. Code / solve test
    1. Refactor
1. Run and test new feature
    1. Bug? -> Make new assert or test!
1. Backup to temporary branch (local only)
1. Rebase HEAD onto base
1. Create PR (squash merge onto dev; merge rebase onto main)
1. (Optional/Recommended) Wait a bit/Work on something else
1. Close PR (via browser!)

<p align="right">(<a href="#readme-top">top</a>)</p>


### Roadmap
See the [open issues](https://github.com/SinixND/Tak/issues) for a full list of planned and implemented features as well as known issues.

<p align="right">(<a href="#readme-top">top</a>)</p>


## References
- [Tak terminology](https://ustak.org/tak-terminology/) Official Tak rules

<p align="right">(<a href="#readme-top">top</a>)</p>


## Acknowledgements
- [Artful Bytes' Youtube series](https://www.youtube.com/watch?v=HXd7g3RlCIs&list=PLS_iNJJVTtiRV0DZRDcTHnvAuDrKGPN40&index=6) about his Embedded System Project of building a sumobot
- [The Modern Rogue - Tak](https://youtube.com/watch?v=Te0Wm_GCCAQ) Beautiful video explanation of the game

<p align="right">(<a href="#readme-top">top</a>)</p>
