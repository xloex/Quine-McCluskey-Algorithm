#include <bits/stdc++.h>
#include "UtileriasMinterminos.h"
#include "mintermino.h"
using namespace std;

int lecturaMinterminos(int &NUMERO_MINTERMINOS, vector<int> &minterminos){

    cout<<"Ingrese la cantidad de minterminos"<<endl;
    cin>>NUMERO_MINTERMINOS;

    //Lectura de minterminos (int)
    int minterminoMaximo=0;
    cout<<"Ingrese los minterminos:"<<endl;
    for(int i=0; i<NUMERO_MINTERMINOS; i++){
        int minterm;
        cin>>minterm;
        minterminos.push_back(minterm);
        minterminoMaximo=max(minterminoMaximo, minterm);
    }

    //Ordenamos de manera creciente
    sort(minterminos.begin(), minterminos.end());

    //retornamos máximo
    return minterminoMaximo;
}



int formacionMinterminos(int MAXIMO, vector<int> &minterminos, vector<string> &minterminosBinario ,vector<vector<vector<mintermino>>> &clasificacionGlobalMinterminos){
    
    //Mediante el valor más grande, definimos el número de bits que vamos a necesitar
    int NUM_BITS=0;
    while(MAXIMO){
        NUM_BITS++;
        MAXIMO>>=1;
    }

    //Transformamos los mintérminos a binario y los almacenamos
    for(int i:minterminos){
        bitset<30> mintermToBit(i);
        /**
         * En base al valor mas grande tomamos unicamente los bits necesarios para que queden todos los minterminos
         * con la mínima cantidad de bits posible, para ello de todo el bitset solamente tomamos el segmento
         * que contiene a los bits significativos
         */
        minterminosBinario.push_back(mintermToBit.to_string().substr(((mintermToBit.to_string().size())-NUM_BITS), NUM_BITS));
    }


    int indiceMinterminos=0;
    /**
     * Clasificación de los mintérminos en su forma binaria dependiendo de la cantidad de bits que se encuentren prendidos, estos son 
     * almacenados en la iteracion 0 de la tabla y clasificados en su correspondiente cantidad de bits
    */
    for(string mintermBits:minterminosBinario){
        int cantidadBitsPrendidos=count(mintermBits.begin(), mintermBits.end(), '1');
        
        string expresionBool="";
        for(int i=0; i<NUM_BITS; i++){
            if(mintermBits[i]=='0') {expresionBool.push_back((char)('z'-NUM_BITS+(i+1))); expresionBool.push_back('\'');}
            else expresionBool.push_back((char)('z'-NUM_BITS+(i+1)));
        }

        //Declaración mintérmino
        mintermino minterminoInicial;
        minterminoInicial.formaBinaria=mintermBits;
        minterminoInicial.estructuraMintermino=to_string(minterminos[indiceMinterminos++]);
        minterminoInicial.uso=false;
        minterminoInicial.expresionBooleana=expresionBool;

        clasificacionGlobalMinterminos[0][cantidadBitsPrendidos].push_back(minterminoInicial);
    }
    return NUM_BITS;
}






int clasificacionMinterminos(int NUM_BITS, vector<vector<vector<mintermino>>>&clasificacionGlobalMinterminos){

    int numCombinacion=1, totalColumns=0;
    bool hasElements=true;

    //Parte en la que sacamos las combinaciones de los mintérminos
    while(hasElements){
        //Variables que nos permiten crear todas las combinaciones posibles conforme avanzamos entre columnas
        int puntero1=0, puntero2=0, posicionamiento=0;
        hasElements=false;
        //Cada que logremos hacer una nueva combinación aumentamos el total de combinaciones
        totalColumns++;

        while(puntero2<=NUM_BITS){
            //Dentro de la primera combinación de mintérminos buscamos el primer vector con elementos
            while(clasificacionGlobalMinterminos[0][puntero1].empty() && puntero1<=NUM_BITS){
                if(puntero1+1>NUM_BITS){
                    puntero2++;
                    break;
                }
                puntero1++;
                puntero2++;
            }
            
            puntero2++;

            //Buscamos el segundo vector que contenga elementos para comenzar a comparar
            while(clasificacionGlobalMinterminos[0][puntero2].empty() && puntero2<=NUM_BITS){
                if(puntero2+1>NUM_BITS){
                    puntero2++;
                    break;
                }
                puntero2++;
            }

            //Finalizamos el recorrido de todos los minterminos
            if(puntero1>NUM_BITS || puntero2>NUM_BITS) break;
            


            //Búsqueda de todos los elementos que puedan combinarse
            for(mintermino &mintermino1: clasificacionGlobalMinterminos[numCombinacion-1][puntero1]){
                for(mintermino &mintermino2: clasificacionGlobalMinterminos[numCombinacion-1][puntero2]){
                    string posibleCombinacion="";
                    int numeroDeCaracteresDiferentes=0;
                    for(int i=0; i<NUM_BITS; i++){
                        if(mintermino1.formaBinaria[i]!=mintermino2.formaBinaria[i]){
                            numeroDeCaracteresDiferentes++;
                            posibleCombinacion.push_back('_');
                        }else{
                            posibleCombinacion.push_back(mintermino1.formaBinaria[i]);
                        }
                    }
                    if(numeroDeCaracteresDiferentes==1){
                        //Creacion del nuevo mintermino combinado
                        mintermino minterminoCombinado;

                        string expresionBool="";
                        for(int i=0; i<NUM_BITS; i++){
                            if(posibleCombinacion[i]=='0') {expresionBool.push_back((char)('z'-NUM_BITS+(i+1))); expresionBool.push_back('\'');}
                            else if(posibleCombinacion[i]=='1') expresionBool.push_back((char)('z'-NUM_BITS+(i+1)));
                        }

                        minterminoCombinado.formaBinaria=posibleCombinacion;
                        minterminoCombinado.estructuraMintermino=mintermino1.estructuraMintermino+","+mintermino2.estructuraMintermino;
                        minterminoCombinado.uso=false;
                        minterminoCombinado.expresionBooleana=expresionBool;

                        clasificacionGlobalMinterminos[numCombinacion][posicionamiento].push_back(minterminoCombinado);

                        //actualizacion de los estados de los minterminos usados
                        mintermino1.uso=true;
                        mintermino2.uso=true;
                        hasElements=true;
                        // cout<<"m("<<mintermino1.estructuraMintermino<<","<<mintermino2.estructuraMintermino<<") "<<posibleCombinacion<<endl;
                    }
                }
            }

            posicionamiento++;
            puntero1++;
        }
        numCombinacion++;
    }
    return totalColumns;
}


vector<mintermino> impresionTablaMinterminosTotales(int NUMERO_COLUMNAS, int NUM_BITS, std::vector<std::vector<std::vector<mintermino>>>&clasificacionGlobalMinterminos){
    //Vector de apoyo para imprimir todos los elementos del vector ClasificacionGlobalMinterminos
    vector<queue<mintermino>> formacionTabla(50);

    for(int i=0; i<50; i++){
        for(int j=0; j<30; j++){
            if(clasificacionGlobalMinterminos[i][j].empty()) continue;
            for(mintermino minterm:clasificacionGlobalMinterminos[i][j]) formacionTabla[i].push(minterm);
        }
    }

    //construccion de la tabla, los datos de los if dependen del numero de datos, a su vez, almacenando los 
    //elementos que no hayan sido usados durante las combinaciones mediante una pila
    vector<mintermino> minterminosNoUsados;
    bool element=false;     //tracking si hubo elementos en la ultima iteración

    cout<<"\n====================================================================================================\n\n    Tabla de combinaciones\n"<<endl;
    for(int j=0; j<50; j++){
        element=false;
        for(int i=0; i<NUMERO_COLUMNAS; i++){
            if(j==0){
                if(i==0) cout<<setw(4)<<left<<""<<setw(20+NUM_BITS)<<left<<"minterminos";
                else {string combinacionN="combinacion "+to_string(i); cout<<setw(20+NUM_BITS)<<left<<combinacionN;}
                continue;
            }
            if(formacionTabla[i].empty()) continue;
            if(i==0) cout<<setw(4)<<left<<"";

            mintermino minterm=formacionTabla[i].front();
            string mparenthesis="";
            formacionTabla[i].pop();
            
            if(!minterm.uso) {mparenthesis.push_back('*'); minterminosNoUsados.push_back(minterm);}

            mparenthesis+="m("+minterm.estructuraMintermino+") -> "+minterm.formaBinaria;
            cout<<setw(20+NUM_BITS)<<left<<mparenthesis;
            element=true;
        }
        if(element || j==0) cout<<endl;
    }
    cout<<"\n    * : Elementos no utilizados durante las combinaciones\n\n===================================================================================================="<<endl;
    return minterminosNoUsados;
}
