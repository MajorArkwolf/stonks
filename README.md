<h1 align="center">
  <br>
  <img src="https://i.imgur.com/r9L3Px0.png" alt="stonks" width="200"></a>
  <br>
    Stonks
  <br>
</h1>

<p align=center>
  <b> ICT290 Assignment 1 </b>
</p>

<p align="center">
  <a href="#building">Building</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>

<p align="center">
  <a href="https://travis-ci.com/opeik/ICT290"> <img src="https://travis-ci.com/opeik/ICT290.svg?token=2cgrDpWeJERSzmm7HcTg&branch=develop"
     alt="build-badge"> </a>
</p>

## Building
### Tools
* macOS: [brew][brew-dl]
* Windows: [vcpkg][vcpkg-dl], [Visual Studio 2019][VS2019-dl]

### Dependencies
* macOS: `brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer glm`
* Linux: `sudo apt-get install cmake libsdl2-dev libsdl2-image-dev
    libsdl2-ttf-dev libsdl2-mixer-dev libglm-dev`
* Windows: `.\vcpkg.exe install --triplet x64-windows sdl2 sdl2-image sdl2-ttf
    sdl2-mixer glm`

### Cloning
```
git clone --recurse-submodules https://github.com/opeik/ICT290.git
# For the add-stonk-engine branch
git checkout add-stonk-engine && git submodule update --init
```

### Building
* Unix:
    ```
    cd ICT290 && cmake -B build . && cd build && cmake --build .
    ```
* Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * In Visual Studio, select Open → CMake, select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `shays-world.exe`

## Contributing
* Ensure your editor uses Unix line endings
    * Use the [Line Endings Unifier][leu-dl]
      plugin for Visual Studio
    * Here's the [suggested configuration][leu-config]
* Use **clang-format** to format your source code to the project standard
    * Install a clang-format extension to your text editor:
        * [vim][clang-format-vim]
        * [Atom][clang-format-atom]
        * [Visual Studio][clang-format-vs]
        * [Visual Studio Code][clang-format-vsc]

## License
This project is licensed under the ISC license. Please see the [`LICENSE.md`](LICENSE.md) file
for details.

[clang-format-vim]: https://github.com/rhysd/vim-clang-format
[clang-format-atom]: https://atom.io/packages/clang-format
[clang-format-vsc]: https://marketplace.visualstudio.com/items?itemName=xaver.clang-format
[clang-format-vs]: https://marketplace.visualstudio.com/items?itemName=mynkow.FormatdocumentonSave
[leu-config]: https://i.imgur.com/ZONPHau.png
[leu-dl]: https://marketplace.visualstudio.com/items?itemName=JakubBielawa.LineEndingsUnifier
[VS2019-dl]: https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16
[vcpkg-dl]: https://github.com/microsoft/vcpkg
[brew-dl]: https://brew.sh
