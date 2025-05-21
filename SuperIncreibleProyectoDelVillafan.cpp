#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef long long ll;

//0 4 8 5 12 11 7 15
void fastIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

struct mintermino{
    string formaBinaria;
    string estructuraMintermino;
    string expresionBooleana;
    bool uso;
    static int NUMERO_MINTERMINOS;
};


int main() {
    fastIO();
    int NUMERO_MINTERMINOS;
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
    cin>>NUMERO_MINTERMINOS;

    clasificacionGlobalMinterminos=vector<vector<vector<mintermino>>>(50, vector<vector<mintermino>>(30));


    ll minterminoMaximo=0;
    cout<<"Ingrese los minterminos:"<<endl;
    for(ll i=0; i<NUMERO_MINTERMINOS; i++){
        ll minterm;
        cin>>minterm;
        minterminos.push_back(minterm);
        minterminoMaximo=max(minterminoMaximo, minterm);
    }

    //Ordenamos de manera creciente
    sort(minterminos.begin(), minterminos.end());

    //Mediante el valor más grande, definimos el número de bits que vamos a necesitar
    int NUM_BITS=0;
    while(minterminoMaximo){
        NUM_BITS++;
        minterminoMaximo>>=1;
    }

    //Transformamos los mintérminos a binario y los almacenamos
    for(ll &i:minterminos){
        bitset<30> mintermToBit(i);
        /**
         * En base al valor mas grande tomamos unicamente los bits necesarios para que queden todos los minterminos
         * con la mínima cantidad de bits posible, para ello de todo el bitset solamente tomamos el segmento
         * que contiene a los bits significativos
         */
        minterminosBinario.push_back(mintermToBit.to_string().substr(((mintermToBit.to_string().size())-NUM_BITS), NUM_BITS));
    }


    ll indiceMinterminos=0;
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
        for(int i=0; i<totalColumns; i++){
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

    cout<<"\n    Tabla inicial formacion de minterminos no utilizados   \n"<<endl;
    
    



    int NUM_MINTERMINOS_FINAL=minterminosNoUsados.size(); //Metrica para la construcción de la tabla
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
    bool minterminosTablaVisitados[NUMERO_MINTERMINOS]={};
    int totalElementsVisted=0;
    int iteracion=1;

    while(totalElementsVisted!=NUMERO_MINTERMINOS){
        cout<<"\n\n===================================================================================================="<<endl;
        cout<<"\n    Iteración"<<iteracion<<endl;
        //Construcción del encabezado de la tabla (imagen)
        for(int i=-1; i<=NUMERO_MINTERMINOS; i++){
            if(i==-1) {cout<<setw(4)<<left<<""<<setw(15)<<left<<"Mintermino"; continue;}
            if(i==NUMERO_MINTERMINOS) {cout<<setw(18)<<left<<"Expresion booleana"<<endl; continue;}
            cout<<setw(4)<<left<<minterminos[i];
        }

        for(int j=1; j<=NUM_MINTERMINOS_FINAL; j++){
            
            mintermino minterm=minterminosNoUsados[NUM_MINTERMINOS_FINAL-j];

            //Identificación del mintérmino que utilizaremos en la iteración kesima

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
    }
}