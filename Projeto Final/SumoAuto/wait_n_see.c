#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void wait_n_see () {
    motors_init();
    timer_init();
    sensors_init();
	int flag = 0;
	uint32_t tempo;
    for (;;) {
		update_distance_sensors();
		if(distance_sensors[LEFT] || distance_sensors[RIGHT]){ /**/
			flag = 1;
		}
		else{
			flag = 0;
		}

		tempo = get_tick();
		if (tempo >= 5000) { /* 5000 ms → 5s */
			flag = 1;
		}

		if(flag){
			motors(SPEED, SPEED);
		}
		else{
			motors(0,0);
		}

		test_stop();
    }
    
}

