/*
 * debounce.h
 *
 *  Created on: 18/9/2016
 *      Author: ab
 */

#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_




/*==================[external functions declaration]=========================*/


typedef struct{
   uint8_t digitalInput; //Que tec es?
   uint8_t tiempoDeb;  //Tiempo de Debounce 40 ms aprox
   bool_t estadoTec;   //estado de la tecla
   uint8_t estadoEnum; //estado de enum para cada tecla
} tecla_t;

tecla_t T1;
tecla_t T2;
tecla_t T3;
tecla_t T4;

bool_t TeclaConfig( tecla_t * tecla, uint8_t digitalIn );
bool_t TeclaRead( tecla_t * tecla );

void ConfigTeclas(uint8_t Tuno,uint8_t Tdos, uint8_t Ttres, uint8_t Tcuatro);

void IniciarMef(uint8_t digitalIn);

bool_t ActualizaMef( tecla_t * tecla, uint8_t digitalIn );



#endif /*#_DEBOUNCE_H_ */
