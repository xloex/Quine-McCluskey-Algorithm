#ifndef UTILERIAS_MINTERMINOS_h
#define UTILERIAS_MINTERMINOS_h

#include <vector>
#include <string>
#include "mintermino.h"

void quine();
/**
 * Funcion mediante la cual leemos los diferentes minterminos que se ingresen en el sistema.
 * @param NUMERO_MINTERMINOS Valor por referencia para almacenar el número total de minterminos
 * @param minterminos Almacenamiento de los diferentes minterminos que se ingresen
 * @return Retorna el mintérmino más grande localizado, útil para la construcción de los mintérminos binarios
 */
int lecturaMinterminos(int&, std::vector<int>&);


/**
 * Formación de los demás elementos necesarios para definir los mintérminos iniciales como lo es el propio mintérmino
 * en su forma binaria, el mintérmino representado con variables XYZ, y definiendo que aún no se han usado.
 * @param MINTERMINO_MAXIMO Elemento más grande que se encontro en la lectura de minterminos
 * @param minterminos Vector con los mintérminos almacenados anteriormente
 * @param minterminosBinario Vector que almacenará los mintérminos en su forma binaria
 * @param clasificacionGlobalMinterminos Vector que almacenará toda la información para las combinaciones posteriores
 * de los mintérminos, contieniendo TODA la información necesaria
 * @return Retorna el número de bits con los cuales se formaron los minterminos binarios
 */
int formacionMinterminos(int, std::vector<int>&, std::vector<std::string>& , std::vector<std::vector<mintermino>>&);


/**
 * Llenado completo de la tabla de clasificaciónG global de los mintérminos, generando todas las posibles combinaciones 
 * y almacenandolas.
 * @param NUM_BITS Cantidad de bits que se necesitaron para el mintérmino más grande
 * @param clasificacionGlobalMinterminos Vector referencia en el que almacenaremos toda la información
 * @return Devuelve el número total de clumnas que se generaron al hacer todas las posibles combinaciones
 */
int clasificacionMinterminos(int, std::vector<std::vector<mintermino>>&);

/**
 * Funcion mediante la cual vamos a imprimir en la terminal toda la información generada en las combinaciones.
 * @param NUMERO_COLUMNAS Número total de columnas con combinaciones
 * @param NUM_BITS Número total de bits que se utilizaron para crear las expresiones booleanas
 * @param clasificacionGlobalMinterminos Tabla con la información de las combinaciones realizadas en otra función
 * @return Retorna un vector con todos los minterminos que no se utilizaron en la construcción de las combinaciones
 */
std::vector<mintermino> impresionTablaMinterminosTotales(const int, const int, std::vector<std::vector<mintermino>>&);


/**
 * Función sobre la cual organizamos, almacenamos e imprimimos los diferentes mintérminos que no hayan
 * sido utilizados durante las combinaciones de mintérminos, incluyendo su estilo en mintérmino, la posicion
 * de las X dentro de la tabla y su forma como espresion booleana.
 * @param minterminosNoUsados Vector que almacena los mintérminos no utilizados
 * @param tablaExpresionesFinales Matriz que almacena la tabla con los mintérminos finales y la posición de las X
 * @param minterminos Vector con los mintérminos totales
 */
void impresionTablaMinterminosFinal(std::vector<mintermino>&, std::vector<std::vector<int>>&, std::vector<int>&);

/**
 * Función en la que imprimimos todas las simplificaciónes de la tabla final, de forma que mantengamos solamente
 * las expresiones booleanas escenciales
 * @param tablaExpresionesFinales Matriz con la información de la tabla final
 * @param NUMERO_MINTERMINOS Cantidad de minterminos a procesar
 * @param minterminosNoUsados Vector con los elementos que no se hayan combinado
 * @return Retorna una lista con los indices asociados a los mintérminos escenciales
 */
std::vector<int> simplificacionTablaFinal(std::vector<std::vector<int>>&, const int, std::vector<mintermino>&);


/**
 * Función en la cual actualizamos la tanla de expresiones finales, dando como entrada las coordenadas del punto
 * sobre el cual comenzaremos la simplificación
 * @param tablaExpresionesFinales Tabla sobre la cual se hará la actualización
 * @param row Fila en la que se encuentra el punto inicial para la eliminación de los elementos
 * @param minterminosExpresados Vector que almacena los elementos ya procesados
 * @return Retorna el número de mintérminos que lograron ser expresados por la combinación
 */
int actualizacionImpresionTabla(std::vector<std::vector<int>>&, int, std::vector<bool>&, std::vector<mintermino>&);
#endif
