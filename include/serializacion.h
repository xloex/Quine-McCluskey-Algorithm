#ifndef SERIALIZACION_h
#define SERIALIZACION_h

#include <vector>
#include <string>
#include "mintermino.h"

// Función para convertir vector<int> plano recibido a vector<int>
std::vector<int> recibirArreglo(int* , int );


// Serialización de vector<mintermino> a JSON
string serializarMinterminosAJSON(const vector<mintermino>&) ;

// Serialización de matriz (vector<vector<int>>) a JSON
string serializarMatrizAJSON(const vector<vector<int>>& );

string serializarArr1DAJSON(const vector<int>&);



#endif