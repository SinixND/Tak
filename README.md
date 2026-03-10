
<div align="center">
<!-- <img src="assets/favicon.ico" alt="Logo" width="80" height="80"> -->
<h1> Tak </h1>
<p> The boardgame from the "King Killer Chronicles" novel series </p>

[![Issues](https://img.shields.io/github/issues/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/issues)
[![Github-Projects](https://github.com/users/SinixND/projects/6)]

[![MIT-License](https://img.shields.io/badge/MIT-License-yellow?style=for-the-badge)](https://opensource.org/licenses/MIT)

[![Stars](https://img.shields.io/github/stars/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/stargazers)
[![Contributors](https://img.shields.io/github/contributors/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/graphs/contributors)
[![Forks](https://img.shields.io/github/forks/SinixND/Tak?style=for-the-badge)](https://github.com/SinixND/Tak/network/members)

</div>


## About The Project
**[Insert screenshot here](path/to/screenshot)**

Implementation of the two player board game from the novel series "King Killer Chronicles" by Patrick Rothfuss.

For more information about the game's rules, see [ustak.org](https://ustak.org/play-beautiful-game-tak/#)

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
[![raylib](https://img.shields.io/badge/library-raylib-white?style=for-the-badge)](https://github.com/raysan5/raylib)
[![Unity](https://img.shields.io/badge/testing-unity-red?style=for-the-badge)](https://github.com/ThrowTheSwitch/Unity)

<!-- #### Excluded -->

<p align="right">(<a href="#readme-top">top</a>)</p>


### How to play

<p align="right">(<a href="#readme-top">top</a>)</p>


### Features

<p align="right">(<a href="#readme-top">top</a>)</p>


### Conventions
#### Branches
- Name: <branchtype>/<issue-tracker-number>/<title>
- Rebase feature onto parent (feature or develop) before merging
- Merge commit: Makes `git bisect` work better (really need clean history?)
- Squash merge: Only for `develop` into `main` (prefer clear history on main)
- Rebase merge: No. Prefer verbosity of merge commit

#### Coding guideline
(based on NASA's [`The Power of 10`](https:/spinroot.com/gerard/pdf/P10.pdf))
1. No recursion
1. No dynamic memory allocation after app initialization
1. No function longer than ~60 lines
1. Two assertions per function (on average)
1. Declare data objects at smallest possible scope
1. Must validate all parameters inside functions
1. Must handle/check all return values
1. Minimal macro usage; must expand to sideffect and recursive free synactic unit
1. Restrict pointer usage; no hidden pointers; no function pointers
1. All code must compile without warnings and with extensive warnings and static analyzers enabled 

#### Style guide
- Types: PascalCase
- Functions: camelCase, starting with verb
- Global constants, enums and macros: all caps with underscore
- 2+ function parameters and arguments on separate lines
- type _before_ const keyword (`int const`)
- (*) to type (`int* pointer`)
- Parameters: 
    - `I/O` before `Output` before `Input`
    - Returned `I/O` parameter always first


<p align="right">(<a href="#readme-top">top</a>)</p>


### Code & Directory Strcture
- Components: Data only

- Entities: SoAs that link Entities/Ids to (their) components/data

- Systems: Logic only (on components/entities)

- Data: Constant, shared variables

- Configs: Changeable, shared variables

- Utility: Shared functions

<p align="right">(<a href="#readme-top">top</a>)</p>


### (Desired) Development workflow
(Try first time with this project)

Utilize the following concepts:
1. Main / develop / feature branches
1. Data first, logic next
1. Test desired behaviour (like a demo)
1. Bug? -> make new assertion
1. Pull Requests (manage via browser)

<p align="right">(<a href="#readme-top">top</a>)</p>


## References
- [Tak terminology](https://ustak.org/tak-terminology/) Official Tak rules

<p align="right">(<a href="#readme-top">top</a>)</p>


## Acknowledgements
- [Artful Bytes' Youtube series](https://www.youtube.com/watch?v=HXd7g3RlCIs&list=PLS_iNJJVTtiRV0DZRDcTHnvAuDrKGPN40&index=6) about his Embedded System Project of building a sumobot
- [The Modern Rogue - Tak](https://youtube.com/watch?v=Te0Wm_GCCAQ) Beautiful video explanation of the game

<p align="right">(<a href="#readme-top">top</a>)</p>


## ToDo notes
- [ ] Undo Placement
- [ ] Redo Placement
- [ ] PickUp: Only owned! -> input dependent
- [ ] Store origin and direction in StackBuffer? (for GameSystem:Drop verification)
    - Set direction if is still 0;
    - Add direction verification function to StackBuffer

- [ ] Record PlayerAction: Move/Drop stone
    - appendDropCount? consider squareIdx
    - [ ] Add tests for
        - record (move)

<p align="right">(<a href="#readme-top">top</a>)</p>
