#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;
typedef vector<vpll> vvpll;
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define fori(i,a,n) for(ll i = a; i < n; i++)
#define foi(i,n) for(ll i = 0; i < n; i++)
#define test(x) cout<<x<<endl
const int MOD = 1e9+7;
const int INF = INT_MAX;

void fastIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}


int main() {
    fastIO();
    ll numMinterminos=0;
    vll minterminos;
    vector<string> minterminosBinario;
    //Vector que almacena la clasificación de los mintérminos, en la primera pocision es el número de bits encendidos que tiene el mintermino
    //el par exterior en su primera posicion tiene otro par con la información del número en bits y en la segunda pocision tenemos el número 
    //del cual surgió el número binario
    //                                                 ================================ Elementos ================================
    //clasificacionMinterminos[numeroDeBitsEncendidos][{{ElementoEnBits,ElementoUsadoEnCombinacion?}, valorDelCualProvienenLosBits}]
    vector<vector<pair<pair<string,bool>, string>>> clasificacionMinterminos, combinacionesMinterminos;

    cout<<"Ingrese la cantidad de minterminos"<<endl;
    cin>>numMinterminos;
    cout<<"Ingrese los minterminos:"<<endl;

    //Almacenado de los diferentes minterminos en su forma decimal
    ll minterminoMaximo=0;
    for(ll i=0; i<numMinterminos; i++){
        ll aux;
        cin>>aux;
        minterminos.push_back(aux);
        minterminoMaximo=max(minterminoMaximo, aux);
    }

    //Mediante el valor más grande, definimos el número de bits que vamos a necesitar
    int NUM_BITS=0;
    while(minterminoMaximo){
        NUM_BITS++;
        minterminoMaximo=minterminoMaximo>>1;
    }

    //Transformamos los mintérminos a binario y los almacenamos
    for(ll i:minterminos){
        bitset<60> minToBit(i);
        minterminosBinario.push_back(minToBit.to_string().substr(((minToBit.to_string().size())-NUM_BITS), NUM_BITS));
    }

    clasificacionMinterminos=vector<vector<pair<pair<string,bool>,string>>>(NUM_BITS+1);
    combinacionesMinterminos=vector<vector<pair<pair<string,bool>,string>>>(numMinterminos*numMinterminos);

    /**
     * Clasificación de los mintérminos en su forma binaria dependiendo de la cantidad de bits que se encuentren prendidos, estos son 
     * almacenados en un vector de vectores de string, donde el primer indice indica el número de bits prendidos
    */
    ll aux111=0;
    for(string minBits:minterminosBinario){
        ll cantidadBitsPrendidos=count(all(minBits), '1');
        clasificacionMinterminos[cantidadBitsPrendidos].push_back({{minBits, false}, to_string(minterminos[aux111])});
        
        aux111++;
    }

    ll puntero1=0, puntero2=0;
    ll iteracionCombinacion=0;
    bool outOfRange=false;
    //Parte en la que sacamos las primeras combinaciones de los mintérminos básicos
    while(puntero2<=NUM_BITS){
        if(puntero1>NUM_BITS){
            outOfRange=true;
        }
        while(clasificacionMinterminos[puntero1].empty() && !outOfRange){
            if(puntero1+1>NUM_BITS){
                outOfRange=true;
                break;
            }
            puntero1++;
            puntero2++;
        }
        
        puntero2++;
        
        if(puntero2>NUM_BITS){
            outOfRange=true;
        }
        while(clasificacionMinterminos[puntero2].empty() && !outOfRange){
            if(puntero2+1>NUM_BITS){
                outOfRange=true;
                break;
            }
            puntero2++;
        }
        
        cout<<"============================="<<endl;
        cout<<"Combinacion de bits "<<puntero1<<","<<puntero2<<endl;

        if(puntero2>NUM_BITS || outOfRange){
            break;
        }

        for(pair<pair<string,bool>,string> &mintermino1: clasificacionMinterminos[puntero1]){
            for(pair<pair<string,bool>,string> &mintermino2: clasificacionMinterminos[puntero2]){
                string posibleCombinacion="";
                ll numeroCaracteresDiferentes=0;
                for(ll i=0; i<mintermino1.first.first.size(); i++){
                    if(mintermino1.first.first[i]!=mintermino2.first.first[i]){
                        numeroCaracteresDiferentes++;
                        posibleCombinacion.push_back('_');
                    }else{
                        posibleCombinacion.push_back(mintermino1.first.first[i]);
                    }
                }
                if(numeroCaracteresDiferentes==1){
                    combinacionesMinterminos[iteracionCombinacion].push_back({{posibleCombinacion, false}, mintermino1.second+","+mintermino2.second});
                    mintermino1.first.second=true;
                    mintermino2.first.second=true;
                    cout<<"m("<<mintermino1.second<<","<<mintermino2.second<<") "<<posibleCombinacion<<endl;
                }
            }
        }
        puntero1++;
    }
    cout<<"============================="<<endl;
    //Recordemos que iteracion de combinacion está en 0

    /**
     * Ahora tenemos que añadir una segunda vuelta de código hasta que ya no podamos formar más iteraciones
     */
    while(!combinacionesMinterminos[iteracionCombinacion].empty()){

        iteracionCombinacion++;
    }
}