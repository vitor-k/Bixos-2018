#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void wait_n_see () {
	int flag = 0;
	int stop = 0;
	uint32_t timer3;
	uint32_t timer4 = 0;
	uint32_t tempo;
    for (;;) {
		update_distance_sensors();
		if(distance_sensors[LEFT] >= 750|| distance_sensors[RIGHT] >= 750){ /**/
			flag = 1;
		}
		else{
			flag = 0;
		}

		/*tempo = get_tick();
		if (tempo >= 5000000) { /* 5000000 us → 5s
			flag = 1;
		}*/

		if(flag){
			motors(SPEED, SPEED);
		}
		else{
			motors(0,0);
		}

		/*stop = test_stop();
		if(stop){
			motors(-SPEED,-SPEED);
			_delay_ms(500);
			motors(-TURN_SPEED,TURN_SPEED);
			timer3 = get_tick();
			while(timer4-timer3 < 1000000 && !(distance_sensors[LEFT] || distance_sensors[RIGHT])){
				timer4 = get_tick();
				update_distance_sensors();
			}
			motors(0,0);
		}*/
    }

}
