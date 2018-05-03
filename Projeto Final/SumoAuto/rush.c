#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void rush() {
	int stop = 0;
    motors(SPEED,SPEED);

    for (;;){
        stop = test_stop();
		if(stop){
			motors(-SPEED,-SPEED);
			_delay_ms(500);
			motors(-TURN_SPEED,TURN_SPEED);
			_delay_ms(1000)
			motors(SPEED,SPEED);
		};
    }

}
