#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hardware.h"
#include "motors.h"
#include "sensors.h"
#include "utils.h"
#include "timer.h"

#define THRESHOLD 0
/*verificar como os sensores funcionam e definir a threshold corretamente*/
#define MULTIPLIER 16

#define AMORTECIMENTO 0.8f

#define DELAY 5

#define SPEED 128

int traduz(){
	switch(1){
		case sensor[0]>THRESHOLD:
			return (-3)*MULTIPLIER;
		case sensor[1]>THRESHOLD:
			return (-2)*MULTIPLIER;
		case sensor[2]>THRESHOLD:
			return (-1)*MULTIPLIER;
		case sensor[3]>THRESHOLD:
			return 0;
		case sensor[4]>THRESHOLD:
			return 1*MULTIPLIER;
		case sensor[5]>THRESHOLD:
			return 2*MULTIPLIER;
		case sensor[6]>THRESHOLD:
			return 3*MULTIPLIER;
	}
}

int main(void) {
	hardware_init();
	int erro=0;
	int erro_anterior=0;
	int erro_integral=0;
	int erro_diferencial=0;
	int outp;
	uint32_t dt=0;
	for (;;) {
		dt += get_tick();
		if(dt > DELAY){
			sensors_update();
			erro = traduz();
			erro_integral = erro_integral*AMORTECIMENTO + erro*dt;
			erro_diferencial = (erro - erro_anterior)/dt;
			outp = erro + erro_integral + erro_diferencial;
			
			set_motors(SPEED+outp, SPEED-outp);
			
			dt = 0;
		}
	}
	return 0;
}
