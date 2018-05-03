#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"



int main () {
    motors_init();
    timer_init();
    sensors_init();

	typedef void(*StrategyFunction)();

	int escolhida = 1; /*uma maneira eh usar esta variavel para escolher a estrategia, ou pode usar um define*/
	StrategyFunction strategy;

	switch(escolhida){
		case 0:
			strategy = rush;
			break;
		case 1:
			strategy = wait_n_see;
			break;
		case 2:
			strategy = search_rotate;
			break;
	}

    strategy();

    return 0;
}
