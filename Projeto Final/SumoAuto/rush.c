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
	uint32_t timer3;
	uint32_t timer4 = 0;
    motors(SPEED,SPEED);

    for (;;){
        stop = test_stop();
		if(stop){
			motors(-SPEED,-SPEED);
			_delay_ms(500);
			motors(-TURN_SPEED,TURN_SPEED);
			timer3 = get_tick();
			while (get_tick() - timer3 < 1000000 /* && !(distance_sensors[LEFT] || distance_sensors[RIGHT])*/){
                update_distance_sensors();
			}
			motors(SPEED,SPEED);
		};
    }

}
