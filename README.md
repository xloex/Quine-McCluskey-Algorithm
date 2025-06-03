# Quine-McCluskey

## Primera versión (completamente en consola con C++)
Para compilar usando g++
```BASH
g++ main.cpp UtileriasMinterminos.cpp -o programa
./programa
```

## Segunda versión (Web usando WASM)
Línea para compilar el archivo quine.cpp para 
```BASH
emcc quine.cpp UtileriasMinterminos.cpp -o quine.js -s INVOKE_RUN=0 -s EXPORTED_FUNCTIONS="['_procesarDatos', '_malloc', '_free']" -s EXPORTED_RUNTIME_METHODS="['ccall','cwrap','HEAP32','HEAPU8']" -s MODULARIZE=0
```
