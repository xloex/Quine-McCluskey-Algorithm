//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "../include/UtileriasMinterminos.h"
#include "../include/serializacion.h"
#include "../include/mintermino.h"

using namespace std;

// Función para convertir vector<int> plano recibido a vector<int>
vector<int> recibirArreglo(int* arr, int size) {
    if (arr == nullptr || size <= 0) return {};
    return vector<int>(arr, arr + size);
}


// Serialización de vector<mintermino> a JSON
string serializarMinterminosAJSON(const vector<mintermino>& minterms) {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < minterms.size(); ++i) {
        oss << "{";
        oss << "\"formaBinaria\":\"" << minterms[i].formaBinaria << "\",";
        oss << "\"estructuraMintermino\":\"" << minterms[i].estructuraMintermino << "\",";
        oss << "\"expresionBooleana\":\"" << minterms[i].expresionBooleana << "\",";
        oss << "\"uso\":" << (minterms[i].uso ? "true" : "false");
        oss << "}";
        if (i != minterms.size() - 1) oss << ",";
    }
    oss << "]";
    return oss.str();
}

// Serialización de matriz (vector<vector<int>>) a JSON
string serializarMatrizAJSON(const vector<vector<int>>& matrix) {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < matrix.size(); ++i) {
        oss << "[";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            oss << matrix[i][j];
            if (j != matrix[i].size() - 1) oss << ",";
        }
        oss << "]";
        if (i != matrix.size() - 1) oss << ",";
    }
    oss << "]";
    return oss.str();
}

string serializarArr1DAJSON(const vector<int>& arr) {
    ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        oss << arr[i];
        if (i != arr.size() - 1) oss << ",";
    }
    oss << "]";
    return oss.str();
}

