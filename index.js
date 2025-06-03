Module.onRuntimeInitialized = () => {
  const inputArray = [0, 1, 5, 21, 85];
  const size = inputArray.length;

  // Reservar memoria y copiar datos a WASM
  const ptrInput = Module._malloc(size * 4);
  Module.HEAP32.set(inputArray, ptrInput / 4);

  // Reservar memoria para tamaño del JSON resultante
  const ptrLength = Module._malloc(4);

  // Llamar función WASM, obtener puntero al JSON serializado
  const ptrJson = Module.ccall(
    'procesarDatos',  // función exportada
    'number',         // tipo retorno: puntero (int)
    ['number', 'number', 'number'], // tipos de parámetros
    [ptrInput, size, ptrLength]     // parámetros
  );

  // Leer tamaño JSON
  const length = Module.HEAP32[ptrLength / 4];

  // Leer el JSON desde la memoria WASM
  const jsonStr = new TextDecoder('utf8').decode(
    new Uint8Array(Module.HEAPU8.buffer, ptrJson, length)
  );

  console.log("JSON recibido desde WASM:", jsonStr);

  // Liberar memoria WASM
  Module._free(ptrInput);
  Module._free(ptrLength);
  Module._free(ptrJson);

  // Parsear JSON para obtener el arreglo con 2 objetos
  const [minterms, matrix] = JSON.parse(jsonStr);

  console.log("Vector<mintermino> recibido en JS:", minterms);
  console.log("Matriz recibida en JS:", matrix);
};
