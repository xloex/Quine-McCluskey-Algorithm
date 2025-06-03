function quine(inputArray){
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
}

Module.onRuntimeInitialized = () => {
  document.getElementById('btnEnviar').addEventListener('click', () => {
    const rawInput = document.getElementById('inputMinterminos').value.trim();
    if (!rawInput) {
        document.getElementById('errorMsg').textContent = "Por favor ingresa al menos un mintermino.";
        return;
    }
    // Separar por espacios o comas
    const tokens = rawInput.split(/[\s,]+/);
    const minterms = [];
    for (let token of tokens) {
        if (!/^\d+$/.test(token)) {
            document.getElementById('errorMsg').textContent = `Error: "${token}" no es un número entero válido.`;
            return;
        }
        minterms.push(parseInt(token, 10));
    }
    document.getElementById('errorMsg').textContent = "";

    // Aquí pasamos el arreglo 'minterms' al WebAssembly
    console.log('Minterminos válidos:', minterms);
    quine(minterms);
  });
  
  
};
