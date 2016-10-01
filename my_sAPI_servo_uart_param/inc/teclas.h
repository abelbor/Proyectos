/*
 * teclas.h
 *
 *  Created on: 9/9/2016
 *      Author: Marcelo
 */

#ifndef _TECLAS_H_
#define _TECLAS_H_

#define NO_TECLA	0
#define TECLA_1		1
#define TECLA_2		2
#define TECLA_3		3
#define TECLA_4		4

typedef struct{
	uint8_t nro;
	bool_t pressed_val;
	bool_t release_val;
	uint8_t debounce;
	uint8_t status;
}tecla_t;

bool_t isPressed (tecla_t *tecla);

#endif /* PROYECTOS_MY_BAREMETAL_INC_PERI_TECLAS_H_ */
