#include <bits/stdc++.h>
#include <iomanip>
#include "UtileriasMinterminos.h"
#include "mintermino.h"

using namespace std;
typedef long long ll;

// 0 4 8 5 12 11 7 15
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
    const int minterminoMaximo=lecturaMinterminos(NUMERO_MINTERMINOS, minterminos);

    //Formación de los mintérminos completos
    const int NUM_BITS=formacionMinterminos(minterminoMaximo, minterminos, minterminosBinario, clasificacionGlobalMinterminos);

    //Llenado de la tabla ClasificacionGlobalMinterminos
    const int NUMERO_COLUMNAS=clasificacionMinterminos(NUM_BITS, clasificacionGlobalMinterminos);

    //Impresion de la tabla con las combinaciones generadas
    vector<mintermino> minterminosNoUsados=impresionTablaMinterminosTotales(NUMERO_COLUMNAS, NUM_BITS, clasificacionGlobalMinterminos);



    //Impresion de la tabla final con los minterminos no utilizados de la forma vista en clase
    cout<<"\n    Tabla inicial formacion de minterminos no utilizados   \n"<<endl;

    const int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size(); //Metrica para la construcción de la tabla
    vector<vector<int>> tablaExpresionesFinales(NUM_MINTERMINOS_FINAL+1, vector<int>(NUMERO_MINTERMINOS));    //1 representa una X, 0 representa un espacio vacio
    //Formación del encabezado de la tabla (variable)
    for(int i=0; i<NUMERO_MINTERMINOS+1; i++){
        tablaExpresionesFinales[0][i]=minterminos[i];
    }

    //Construcción del encabezado de la tabla (imagen)
    for(int i=-1; i<=NUMERO_MINTERMINOS; i++){
        if(i==-1) {cout<<setw(4)<<left<<""<<setw(15)<<left<<"Mintermino"; continue;}
        if(i==NUMERO_MINTERMINOS) {cout<<setw(18)<<left<<"Expresion booleana"<<endl; continue;}
        cout<<setw(4)<<left<<minterminos[i];
    }

    for(int j=1; j<=NUM_MINTERMINOS_FINAL; j++){
        
        mintermino minterm=minterminosNoUsados[NUM_MINTERMINOS_FINAL-j];
        unordered_map<int,int> minterminosInt;

        string numStr="";
        for(int i=0; i<=minterm.estructuraMintermino.size(); i++){
            if(i==minterm.estructuraMintermino.size()){
                int numInt=stoi(numStr);
                minterminosInt[numInt]=1;
                continue;
            }
            if(minterm.estructuraMintermino[i]==','){
                int numInt=stoi(numStr);
                minterminosInt[numInt]=1;
                numStr="";
                continue;
            }
            numStr.push_back(minterm.estructuraMintermino[i]);
        }

        for(int i=-1; i<=NUMERO_MINTERMINOS; i++){
            if(i==-1){
                string mparenthesis="m("+minterm.estructuraMintermino+")";
                cout<<setw(4)<<left<<""<<setw(15)<<left<<mparenthesis;
                continue;
            }
            if(i==NUMERO_MINTERMINOS){
                cout<<setw(18)<<left<<minterm.expresionBooleana<<endl;
                continue;
            }

            if(minterminosInt[minterminos[i]]==1){
                cout<<setw(4)<<left<<"X";
                tablaExpresionesFinales[j][i]=1;
            }else {
                cout<<setw(4)<<left<<"";
                tablaExpresionesFinales[j][i]=1;
            }
        }
    }


    //===== Construccion de la tabla por cada iteración ======
    // bool minterminosTablaVisitados[NUMERO_MINTERMINOS]={};
    // int totalElementsVisted=0;
    // int iteracion=1;
}