//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "../include/UtileriasMinterminos.h"
#include "../include/mintermino.h"
#include "../include/serializacion.h"

using namespace std;
typedef long long ll;
#define sz(v) (int)v.size()

vector<int> minterminos;
vector<mintermino> minterminosNoUsados;
vector<vector<int>> tablaExpresionesFinales;
vector<int> indices;



extern "C" {

// Copiar string a memoria WASM (heap)
char* copiarStringAHeap(const char* inputStr, int length) {
    char* buffer = (char*) malloc(length + 1); // +1 para '\0'
    if (!buffer) return nullptr;
    memcpy(buffer, inputStr, length);
    buffer[length] = '\0';
    return buffer;
}

/**
 * Función principal exportada.
 * Recibe arreglo plano y tamaño, genera vector<mintermino> y matriz,
 * serializa ambos a JSON y los concatena en arreglo JSON,
 * copia a memoria WASM y retorna puntero.
 * outLength recibe el tamaño del JSON total.
 */

string json="";
char* procesarDatos(int* arr, int size, int* outLength) {
    minterminos = recibirArreglo(arr, size);
    quine();
    // mintermsGlobal = crearMinterminosDesdeVector(inputVec);
    // matrixGlobal = crearMatrizDesdeVector(inputVec);

    // string jsonMinterms = serializarMinterminosAJSON(minterminosNoUsados);
    // string jsonMatrix = serializarMatrizAJSON(tablaExpresionesFinales);

    string jsonIndices = serializarArr1DAJSON(indices);

    // Crear arreglo JSON con dos objetos: [minterms, matrix]
    string jsonFinal = "[" + json + jsonIndices + "]";

    if (outLength) *outLength = (int)jsonFinal.size();

    return copiarStringAHeap(jsonFinal.c_str(), (int)jsonFinal.size());
}

}





void quine(){
    json="";
    /**
     *Vector que almacena la clasificación de los mintérminos, en la primera pocision es el número de bits encendidos que tiene el mintermino
     *el par exterior en su primera posicion tiene otro par con la información del número en bits y en la segunda pocision tenemos el número 
     *del cual surgió el número binario
     *[iteracionDeLaTabla][minterminosAlmacenados]
     */
    vector<vector<mintermino>> clasificacionGlobalMinterminos(50);
    vector<string> minterminosBinario;
    

    //-----------------------------------
    //Lo recibe de WASM
    //vector<int> minterminos = {5, 7, 9, 12, 13, 15};
    
    sort(minterminos.begin(), minterminos.end());

    //-----------------------------------
    
    //Lectura de datos y retorno del mintérmino mas grande
    const int MINTERMINO_MAXIMO=minterminos[sz(minterminos)-1];
    int NUMERO_MINTERMINOS = sz(minterminos);
    
    //lecturaMinterminos(NUMERO_MINTERMINOS, minterminos);

    //Formación de los mintérminos completos
    const int NUM_BITS=formacionMinterminos(MINTERMINO_MAXIMO, minterminos, minterminosBinario, clasificacionGlobalMinterminos);

    //Llenado de la tabla ClasificacionGlobalMinterminos
    const int NUMERO_COLUMNAS=clasificacionMinterminos(NUM_BITS, clasificacionGlobalMinterminos);

    //Impresion de la tabla con las combinaciones generadas
    minterminosNoUsados=impresionTablaMinterminosTotales(NUMERO_COLUMNAS, NUM_BITS, clasificacionGlobalMinterminos);

    //Metrica para la construcción de la tabla
    const int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size(); 
    tablaExpresionesFinales.assign(NUM_MINTERMINOS_FINAL+1, vector<int>(NUMERO_MINTERMINOS));    //1 representa una X, 0 representa un espacio vacio

    //Impresion de la tabla final
    impresionTablaMinterminosFinal(minterminosNoUsados, tablaExpresionesFinales, minterminos, json);
    

    //Simplificación de la tabla final para obtener la expresión más simple
    indices = simplificacionTablaFinal(tablaExpresionesFinales, NUMERO_MINTERMINOS, minterminosNoUsados, json);

    //Impresion de la expresion booleana final
    cout<<"\n====================================================================================================    \n\n    Expresion booleana final:";
    cout<<"  ";

    for(auto each : indices){
        cout << each << ", ";
    }
    cout << endl;
    for(int i=0; i<indices.size(); i++){
        cout<<minterminosNoUsados[indices[i]].expresionBooleana;
        if(i!=indices.size()-1) cout<<" + ";
    }
    cout<<" \n"<<endl;
}

int main(){
    quine();
    return 0;
}
