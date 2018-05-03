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
	int stop = 0;
	uint32_t timer1;
	uint32_t timer2 = 0;
	uint32_t timer3;
	uint32_t timer4 = 0;
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

		stop = test_stop();
		if(stop){
			motors(-SPEED,-SPEED);
			timer1 = get_tick();
			while(timer2 - timer1 < 500000){
				timer2 = get_tick();
			}
			motors(-TURN_SPEED,TURN_SPEED);
			timer3 = get_tick();
			while(timer4-timer3 < 1000000 && !(distance_sensors[LEFT] || distance_sensors[RIGHT])){
				timer4 = get_tick();
				update_distance_sensors();	
			}
			motors(0,0);
		};
    }
    
}

