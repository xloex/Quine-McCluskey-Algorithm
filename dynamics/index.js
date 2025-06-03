var Module = {
  onRuntimeInitialized(){
    const variablesBase = (() => { 
      let arr = []
      for(let i = 25; i>=0; i--){
        arr.push(String.fromCharCode(97 + i))
      }
      return arr
    })();
    console.log(variablesBase);

    let minterms = [];
    let flag = false;
    
  
    document.getElementById('inputMinterminos').addEventListener('input', () => {
      const rawInput = document.getElementById('inputMinterminos').value.trim();
      const mathDiv = document.getElementById('mathExpression');

      minterms = []; // Reiniciamos el arreglo cada vez que cambie el input

      if (!rawInput) {
        mathDiv.textContent = '\\( f() = \\)';
        MathJax.typesetPromise(); // Re-render
        flag = false;
        return;
      }

      const tokens = rawInput.split(/[\s,]+/);

      for (let token of tokens) {
        if (!/^\d+$/.test(token)) {
          console.log(`Error: "${token}" no es un número entero válido.`);
          flag = false;
          return;
        }
        minterms.push(parseInt(token, 10));
      }

      flag = true;

      // Determinar cuántas variables usar (máx el tamaño del arreglo)
      const numVars = Math.min(variablesBase.length, Math.ceil(Math.log2(Math.max(...minterms) + 1)));
      const selectedVars = variablesBase.slice(0, numVars).reverse(); // de z hacia atrás

      const expr = `\\( f(${selectedVars.join(', ')}) = \\)`;
      mathDiv.textContent = expr;
      MathJax.typesetPromise();
    });


    document.getElementById("btnEnviar").addEventListener("click", () =>{
      if(!flag) return;
      
      console.log(minterms);
      const size = minterms.length;

      // Reservar memoria y copiar datos a WASM
      const ptrInput = Module._malloc(size * 4);
      Module.HEAP32.set(minterms, ptrInput / 4);

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
      let obj = JSON.parse(jsonStr);

      // console.log("Vector<mintermino> recibido en JS:", miniterms);
      // console.log("Matriz recibida en JS:", matrix);
      console.log(obj);
    });
  }
};