#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void fastIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

struct mintermino{
    string formaBinaria;
    string formaMintermino;
    bool uso;
};


int main() {
    fastIO();
    int numeroDeMinterminos=0;
    vector<ll> minterminos;
    vector<string> minterminosBinario;
    /**
     *Vector que almacena la clasificación de los mintérminos, en la primera pocision es el número de bits encendidos que tiene el mintermino
     *el par exterior en su primera posicion tiene otro par con la información del número en bits y en la segunda pocision tenemos el número 
     *del cual surgió el número binario
     *[iteracionDeLaTabla][clasificacionPorBits][minterminosAlmacenados]

     * IMPORTANTE:
     * A partir de la iteracion 1, los minterminos seran clasificados de forma creciente con referencia
     * a la cantidad de bits encendidos sobre el cual se generó la combinación
     */
    vector<vector<vector<mintermino>>> clasificacionGlobalMinterminos;

    cout<<"Ingrese la cantidad de minterminos"<<endl;
    cin>>numeroDeMinterminos;

    clasificacionGlobalMinterminos=vector<vector<vector<mintermino>>>(50, vector<vector<mintermino>>(30));


    int minterminoMaximo=0;
    cout<<"Ingrese los minterminos:"<<endl;
    for(ll i=0; i<numeroDeMinterminos; i++){

        int minterm;
        cin>>minterm;
        minterminos.push_back(minterm);
        minterminoMaximo=max(minterminoMaximo, minterm);

    }

    //Mediante el valor más grande, definimos el número de bits que vamos a necesitar
    int NUM_BITS=0;
    while(minterminoMaximo){
        NUM_BITS++;
        minterminoMaximo>>=1;
    }

    //Transformamos los mintérminos a binario y los almacenamos
    for(ll i:minterminos){
        bitset<30> mintermToBit(i);
        /**
         * En base al valor mas grande tomamos unicamente los bits necesarios para que queden todos los minterminos
         * con la mínima cantidad de bits posible, para ello de todo el bitset solamente tomamos el segmento
         * que contiene a los bits significativos
         */
        minterminosBinario.push_back(mintermToBit.to_string().substr(((mintermToBit.to_string().size())-NUM_BITS), NUM_BITS));
    }

    /**
     * Clasificación de los mintérminos en su forma binaria dependiendo de la cantidad de bits que se encuentren prendidos, estos son 
     * almacenados en la iteracion 0 de la tabla y clasificados en su correspondiente cantidad de bits
    */
    ll indiceMinterminos=0;
    for(string mintermBits:minterminosBinario){
        ll cantidadBitsPrendidos=count(mintermBits.begin(), mintermBits.end(), '1');

        //Declaración mintérmino
        mintermino minterminoInicial;
        minterminoInicial.formaBinaria=mintermBits;
        minterminoInicial.formaMintermino=to_string(minterminos[indiceMinterminos++]);
        minterminoInicial.uso=false;

        clasificacionGlobalMinterminos[0][cantidadBitsPrendidos].push_back(minterminoInicial);
    }

    ll puntero1=0, puntero2=0, variableAuxiliarParaClasificarCombinaciones=0;
    //Parte en la que sacamos las primeras combinaciones de los mintérminos básicos
    while(puntero2<=NUM_BITS){

        //Buscamos la primera clasificación que contenga elementos
        while(clasificacionGlobalMinterminos[0][puntero1].empty() && puntero1<=NUM_BITS){
            if(puntero1+1>NUM_BITS){
                puntero2++;
                break;
            }
            puntero1++;
            puntero2++;
        }
        
        puntero2++;

        //Buscamos la segunda clasificacion que contenga elementos para comenzar a comparar
        while(clasificacionGlobalMinterminos[0][puntero2].empty() && puntero2<=NUM_BITS){
            if(puntero2+1>NUM_BITS){
                puntero2++;
                break;
            }
            puntero2++;
        }

        //Finalizamos el recorrido de todos los minterminos
        if(puntero1>NUM_BITS || puntero2>NUM_BITS) break;
        
        //PRUEBA======================================
        cout<<"============================="<<endl;
        cout<<"Combinacion de bits "<<puntero1<<","<<puntero2<<endl;
        //============================================


        for(mintermino mintermino1: clasificacionGlobalMinterminos[0][puntero1]){
            for(mintermino mintermino2: clasificacionGlobalMinterminos[0][puntero2]){
                string posibleCombinacion="";
                ll numeroDeCaracteresDiferentes=0;
                for(ll i=0; i<NUM_BITS; i++){
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
                    minterminoCombinado.formaBinaria=posibleCombinacion;
                    minterminoCombinado.formaMintermino=mintermino1.formaMintermino+","+mintermino2.formaMintermino;
                    minterminoCombinado.uso=false;

                    clasificacionGlobalMinterminos[1][variableAuxiliarParaClasificarCombinaciones].push_back(minterminoCombinado);

                    //actualizacion de los estados de los minterminos usados
                    mintermino1.uso=true;
                    mintermino2.uso=true;
                    cout<<"m("<<mintermino1.formaMintermino<<","<<mintermino2.formaMintermino<<") "<<posibleCombinacion<<endl;
                }
            }
        }

        variableAuxiliarParaClasificarCombinaciones++;
        puntero1++;
    }
    cout<<"============================="<<endl;
    //Recordemos que iteracion de combinacion está en 0

    /**
     * Ahora tenemos que añadir una segunda vuelta de código hasta que ya no podamos formar más combinaciones
     */
}