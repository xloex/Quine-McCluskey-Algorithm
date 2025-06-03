function construirTablas(data) {
  const container = document.querySelector('.container');
  
  // Vamos a iterar por cada "tabla" que viene en el JSON excepto la última posición que es un arreglo de indices
  for (let i = 0; i < data.length - 1; i++) {
    const [titulo, minterminos, matriz] = data[i];
    
    // Crear el div card para la tabla
    const card = document.createElement('div');
    card.className = 'card';
    
    // Título
    const h3 = document.createElement('h3');
    h3.textContent = titulo;
    card.appendChild(h3);
    
    // Crear tabla HTML
    const table = document.createElement('table');
    table.style.width = '100%';
    table.style.borderCollapse = 'collapse';
    
    // Crear encabezado de tabla
    const thead = document.createElement('thead');
    const trHead = document.createElement('tr');
    
    // Primera columna vacía para la cabecera de mintermino
    let th = document.createElement('th');
    th.textContent = 'Mintermino';
    th.style.border = '1px solid black';
    th.style.padding = '6px';
    trHead.appendChild(th);
    
    // Segunda columna Expresión Booleana
    th = document.createElement('th');
    th.textContent = 'Expresión Booleana';
    th.style.border = '1px solid black';
    th.style.padding = '6px';
    trHead.appendChild(th);
    
    // Las demás columnas son los valores de matriz[0] (que es el array de minterminos)
    for (const val of matriz[0]) {
      th = document.createElement('th');
      th.textContent = val;
      th.style.border = '1px solid black';
      th.style.padding = '6px';
      trHead.appendChild(th);
    }
    
    thead.appendChild(trHead);
    table.appendChild(thead);
    
    // Crear cuerpo de tabla
    const tbody = document.createElement('tbody');
    
    // Por cada mintermino (cada fila)
    for (let fila = 0; fila < minterminos.length; fila++) {
      const tr = document.createElement('tr');
      
      // Columna Mintermino (estructuraMintermino)
      let td = document.createElement('td');
      td.textContent = minterminos[fila].estructuraMintermino;
      td.style.border = '1px solid black';
      td.style.padding = '6px';
      tr.appendChild(td);
      
      // Columna ExpresionBooleana
      td = document.createElement('td');
      td.textContent = minterminos[fila].expresionBooleana;
      td.style.border = '1px solid black';
      td.style.padding = '6px';
      tr.appendChild(td);
      
      // Las columnas siguientes son el valor en matriz (segundo array, tercero, etc.)
      for (let col = 0; col < matriz[fila].length; col++) {
        td = document.createElement('td');
        const val = matriz[fila+1][col];
        let displayChar = '';
        if (val === 0) displayChar = ' ';
        else if (val === 1) displayChar = 'X';
        else if (val === -1) displayChar = '#';
        td.textContent = displayChar;
        
        td.style.border = '1px solid black';
        td.style.padding = '6px';
        td.className = `cell-${displayChar === ' ' ? 'blank' : displayChar === 'X' ? 'x' : 'hash'}`;
        tr.appendChild(td);
      }
      
      tbody.appendChild(tr);
    }
    
    table.appendChild(tbody);
    card.appendChild(table);
    
    container.appendChild(card);
  }
}
function mostrarTerminoReducido(data) {
  const container = document.querySelector('.container');
  
  // El último elemento del arreglo es un array de indices
  const indices = data[data.length - 1];
  
  // El vector minterminos es el primer arreglo del último objeto tipo tabla
  const ultimoObjetoTabla = data[data.length - 2]; // penúltimo porque el último son indices
  
  const minterminos = ultimoObjetoTabla[1]; // primer arreglo del objeto tabla (array de objetos minterminos)
  
  // Construir la expresión sumatoria igual que en el C++
  let resultado = '';
  for (let i = 0; i < indices.length; i++) {
    const idx = indices[i];
    resultado += minterminos[idx].expresionBooleana;
    if (i !== indices.length - 1) {
      resultado += ' + ';
    }
  }
  
  // Crear el div card que contendrá el resultado
  const card = document.createElement('div');
  card.className = 'card';
  
  // Crear el div mathExpression con el contenido actual de la expresión en la página
  const mathDiv = document.createElement('div');
  mathDiv.id = 'mathExpressionRes';
  
  // Obtener el contenido base actual para mantener la parte f(...) =
  const baseExpr = document.querySelector('.equation-input #mathExpression').textContent;
  
  // Construimos el texto final
  // El baseExpr es tipo: "f(w,x,y,z) = "
  mathDiv.textContent = baseExpr + " "+resultado;
  
  card.appendChild(mathDiv);
  container.appendChild(card);
  
  // Rerenderizar MathJax para que reconozca la fórmula nueva
  MathJax.typesetPromise();
}


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
      construirTablas(obj);
      mostrarTerminoReducido(obj);
    });
  }
};