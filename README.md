# Stonks
ICT290 Group Project Part 1

## Building
### Prerequisites
* macOS: [brew](https://brew.sh)
* Windows: [vcpkg](https://github.com/microsoft/vcpkg)

### Clone the repo
```
git clone --recurse-submodules https://github.com/opeik/ICT290.git
```

### Dependencies
* macOS: `brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer`
* Linux: `sudo apt-get install cmake libsdl2-dev libsdl2-image-dev
    libsdl2-ttf-dev libsdl2-mixer-dev`
* Windows: `.\vcpkg.exe install --triplet x64-windows sdl2 sdl2-image sdl2-ttf
    sdl2-mixer`

### Build
* Unix:
    ```
    cd ICT290 && cmake -B build . && cd build && cmake --build
    ```
* Windows:
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
        * [Visual Studio 2017](https://marketplace.visualstudio.com/items?itemName=mynkow.FormatdocumentonSave)
            * VS17 includes support for clang-format, but won't format
                unless you do it manually, so use this extension
        * [Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
    * Make sure to configure the extension to automatically apply formatting on
        save
