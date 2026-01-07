# Quine-McCluskey
A Boolean expression simplifier based on the Quine-McCluskey algorithm. This project provides an efficient way to minimize logical functions by identifying prime implicants and finding the essential ones to produce the simplest possible expression.
## Web Demo
You can try the web version here: [https://xloex.github.io/Quine-McCluskey-Algorithm/](https://xloex.github.io/Quine-McCluskey-Algorithm/)

## System Requirements

To compile and run this project, you will need the following installed:

1. **C++ Compiler:** Support for C++11 or higher (e.g., **g++** from MinGW on Windows, or the standard g++ on Linux/macOS).
2. **Git:** To clone the repository.

### For Web Version (WebAssembly)
1. **Emscripten SDK (emsdk):** Required to compile C++ into WASM/JS.
   - You must have `emcc` installed and active in your environment variables.
   - Run `.\emsdk_env.bat` (Windows) or `source ./emsdk_env.sh` (Linux/Mac) before compiling.

## How to Clone the Project
> **Disclaimer:** Before running the command below, ensure you have navigated in your terminal to the specific folder where you want this project to live (e.g., `Documents/Projects`). Use the `cd` command to change directories first.

Open your terminal and run the following command to get a local copy of the repository:

```bash
git clone https://github.com/xloex/Quine-McCluskey-Algorithm.git
cd Quine-McCluskey-Algorithm
```
## First version (completely in console with C++)
To compile and run using g++
```BASH
g++ src/main.cpp src/UtileriasMinterminos.cpp src/serializacion.cpp -I include -o program
./program
```

## Second version (Web using WASM)
To compile the source files for web integration:
```BASH
emcc src/quine.cpp src/UtileriasMinterminos.cpp src/serializacion.cpp -I include -o build/quine.js -s INVOKE_RUN=0 -s EXPORTED_FUNCTIONS="['_procesarDatos', '_malloc', '_free']" -s EXPORTED_RUNTIME_METHODS="['ccall','cwrap','HEAP32','HEAPU8']" -s MODULARIZE=0
```
