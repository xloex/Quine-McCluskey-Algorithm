#include <bits/stdc++.h>
#include <iomanip>
#include "UtileriasMinterminos.h"
#include "mintermino.h"

using namespace std;
typedef long long ll;

//  
// COMPILA DE LA SIGUIENTE FORMA, NECESITAS TENER TODOS LOS ARCHIVOS DEL GITHUB, TODO EN UNA MISMA CARPETA
// g++ SuperIncreibleProyectoDelVillafan.cpp UtileriasMinterminos.cpp -o programa
// ./programa

int main() {

    /**
     *Vector que almacena la clasificación de los mintérminos, en la primera pocision es el número de bits encendidos que tiene el mintermino
     *el par exterior en su primera posicion tiene otro par con la información del número en bits y en la segunda pocision tenemos el número 
     *del cual surgió el número binario
     *[iteracionDeLaTabla][clasificacionPorBits][minterminosAlmacenados]

     * IMPORTANTE:
     * A partir de la iteracion 1, los minterminos seran clasificados de forma creciente con referencia
     * a la cantidad de bits encendidos sobre el cual se generó la combinación
     */
    vector<vector<vector<mintermino>>> clasificacionGlobalMinterminos(50, vector<vector<mintermino>>(30));
    vector<int> minterminos;  vector<string> minterminosBinario;
    int NUMERO_MINTERMINOS;

    //Lectura de datos y retorno del mintérmino mas grande
    const int MINTERMINO_MAXIMO=lecturaMinterminos(NUMERO_MINTERMINOS, minterminos);

    //Formación de los mintérminos completos
    const int NUM_BITS=formacionMinterminos(MINTERMINO_MAXIMO, minterminos, minterminosBinario, clasificacionGlobalMinterminos);

    //Llenado de la tabla ClasificacionGlobalMinterminos
    const int NUMERO_COLUMNAS=clasificacionMinterminos(NUM_BITS, clasificacionGlobalMinterminos);

    //Impresion de la tabla con las combinaciones generadas
    vector<mintermino> minterminosNoUsados=impresionTablaMinterminosTotales(NUMERO_COLUMNAS, NUM_BITS, clasificacionGlobalMinterminos);

    //Metrica para la construcción de la tabla
    const int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size(); 
    vector<vector<int>> tablaExpresionesFinales(NUM_MINTERMINOS_FINAL+1, vector<int>(NUMERO_MINTERMINOS));    //1 representa una X, 0 representa un espacio vacio

    //Impresion de la tabla final
    impresionTablaMinterminosFinal(minterminosNoUsados, tablaExpresionesFinales, minterminos);
    

    //Simplificación de la tabla final para obtener la expresión más simple
    vector<int> indices = simplificacionTablaFinal(tablaExpresionesFinales, NUMERO_MINTERMINOS, minterminosNoUsados);

    //Impresion de la expresion booleana final
    cout<<"\n====================================================================================================    \n\n    Expresion booleana final:";
    cout<<"  ";
    for(int i=0; i<indices.size(); i++){
        cout<<minterminosNoUsados[indices[i]].expresionBooleana;
        if(i!=indices.size()-1) cout<<" + ";
    }
    cout<<endl;
    return 0;
}