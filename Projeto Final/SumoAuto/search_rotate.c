#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void search_rotate () {
    motors_init();
    timer_init();
    sensors_init();
	
	int flag = 0;
	uint32_t tempo;

    for (;;) {
		update_distance_sensors();
		if(distance_sensors[LEFT] || distance_sensors[RIGHT]){
			flag = 1;
		}
		else{
			flag = 0;
		}

		tempo = get_tick();
		if (tempo >= 5000000) { /* 5000000 us → 5s */
			flag = 1;
		}
		
		if(flag){
			motors(SPEED, SPEED);
		}
		else{
			motors(TURN_SPEED,-TURN_SPEED);
		}

		test_stop();
    }
    
}

