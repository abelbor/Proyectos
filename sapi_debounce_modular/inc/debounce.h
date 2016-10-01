/*
 * debounce.h
 *
 *  Created on: 18/9/2016
 *      Author: ab
 */

#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

/*==================[typedef]================================================*/
typedef struct{
   uint8_t digitalInput; //Que tec es?
   uint8_t tiempoDeb;  //Tiempo de Debounce 40 ms aprox
   bool_t estadoTec;   //estado de la tecla
} tecla_t;


/*==================[external functions declaration]=========================*/

bool_t TeclaConfig( tecla_t * tecla, uint8_t digitalIn );
bool_t TeclaToggle( tecla_t * tecla );
bool_t TeclaRead( tecla_t * tecla );
int ActualizaMef();
void IniciarMef();

#endif /*#_DEBOUNCE_H_ */
