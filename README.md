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
git checkout add-stronk-engine && git submodule update --init
```

### Building
* Unix:
    ```
    cd ICT290 && cmake -B build . && cd build && cmake --build
    ```
* Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * In Visual Studio, select Open → CMake, select `CMakeLists.txt`
    * Select Build

## Contributing
* Ensure your editor uses Unix line endings and leaves an empty new line at
    the end of a file
    * Use [this plugin](https://marketplace.visualstudio.com/items?itemName=JakubBielawa.LineEndingsUnifier)
      for Visual Studio
        * Set `Add newlines on the last line` to `true`
        * Set `Default line ending` to `Linux`
        * Set `Save files after unifying` to `true`
* Use clang-format to style your source code
    * Install a clang-format extension to your editor of choice
        * [vim](https://github.com/rhysd/vim-clang-format)
        * [Atom](https://atom.io/packages/clang-format)
        * [Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
    * Make sure to configure the extension to automatically apply formatting on
        save

## License
This project is licensed under the ISC license. Please see the `LICENSE.md` file
for details.

[VS2019-dl]: https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16
[vcpkg-dl]: https://github.com/microsoft/vcpkg
[brew-dl]: https://brew.sh
