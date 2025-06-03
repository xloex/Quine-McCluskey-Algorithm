#ifndef SERIALIZACION_h
#define SERIALIZACION_h

#include <vector>
#include <string>
#include "mintermino.h"

// Función para convertir vector<int> plano recibido a vector<int>
std::vector<int> recibirArreglo(int* , int );


// Serialización de vector<mintermino> a JSON
std::string serializarMinterminosAJSON(const std::vector<mintermino>&) ;

// Serialización de matriz (vector<vector<int>>) a JSON
std::string serializarMatrizAJSON(const std::vector<std::vector<int>>& );

std::string serializarArr1DAJSON(const std::vector<int>&);



#endif