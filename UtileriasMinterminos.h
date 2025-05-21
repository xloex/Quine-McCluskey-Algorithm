#ifndef UTILERIAS_MINTERMINOS_h
#define UTILERIAS_MINTERMINOS_h

#include <vector>
#include <string>
#include "mintermino.h"

/**
 * Funcion mediante la cual leemos los diferentes minterminos que se ingresen en el sistema
 * @param NUMERO_MINTERMINOS Valor por referencia para almacenar el número total de minterminos
 * @param minterminos Almacenamiento de los diferentes minterminos que se ingresen
 * @return Retorna el mintérmino más grande localizado, útil para la construcción de los mintérminos binarios
 */
int lecturaMinterminos(int&, std::vector<int>&);


/**
 * Formación de los demás elementos necesarios para definir los mintérminos iniciales como lo es el propio mintérmino
 * en su forma binaria, el mintérmino representado con variables XYZ, y definiendo que aún no se han usado
 * @param MAXIMO Elemento más grande que se encontro en la lectura de minterminos
 * @param minterminos Vector con los mintérminos almacenados anteriormente
 * @param minterminosBinario Vector que almacenará los mintérminos en su forma binaria
 * @param clasificacionGlobalMinterminos Vector que almacenará toda la información para las combinaciones posteriores
 * de los mintérminos, contieniendo TODA la información necesaria
 * @return Retorna el número de bits con los cuales se formaron los minterminos binarios
 */
int formacionMinterminos(int, std::vector<int>&, std::vector<std::string>& , std::vector<std::vector<std::vector<mintermino>>>&);


/**
 * Llenado completo de la tabla de clasificaciónG global de los mintérminos, generando todas las posibles combinaciones 
 * y almacenandolas
 * @param NUM_BITS Cantidad de bits que se necesitaron para el mintérmino más grande
 * @param clasificacionGlobalMinterminos Vector referencia en el que almacenaremos toda la información
 * @return Devuelve el número total de clumnas que se generaron al hacer todas las posibles combinaciones
 */
int clasificacionMinterminos(int, std::vector<std::vector<std::vector<mintermino>>>&);

/**
 * Funcion mediante la cual vamos a imprimir en la terminal toda la información generada en las combinaciones
 * @param NUMERO_COLUMNAS Número total de columnas con combinaciones
 * @param NUM_BITS Número total de bits que se utilizaron para crear las expresiones booleanas
 * @param clasificacionGlobalMinterminos Tabla con la información de las combinaciones realizadas en otra función
 * @return Retorna un vector con todos los minterminos que no se utilizaron en la construcción de las combinaciones
 */
std::vector<mintermino> impresionTablaMinterminosTotales(int,int, std::vector<std::vector<std::vector<mintermino>>>&);

#endif
