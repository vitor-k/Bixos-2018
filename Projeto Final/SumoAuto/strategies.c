#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void turn_edge(){
	motors(-SPEED,-SPEED);
	_delay_ms(500);
	motors(-TURN_SPEED,TURN_SPEED);
	_delay_ms(1000);
	motors(SPEED,SPEED);
}

void rush() {
	// int stop = 0;
    motors(SPEED,SPEED);

    for (;;){
		if(test_stop()){
			turn_edge();
		}
    }

}

void wait_n_see () {
	int flag = 0;
	// int stop = 0;
	// uint32_t tempo;
    for (;;) {
		update_distance_sensors();
		if(distance_sensors[LEFT] >= DISTANCE_THRESHOLD || distance_sensors[RIGHT] >= DISTANCE_THRESHOLD){ /**/
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
		if(test_stop()){
			turn_edge();
		}
    }

}

void search_rotate () {
	int flag = 0;
	// int stop = 0;
	/* uint32_t timer3;
	uint32_t timer4 = 0; */
	uint32_t tempo;

    for (;;) {
		update_distance_sensors();
		if(distance_sensors[LEFT] >= DISTANCE_THRESHOLD || distance_sensors[RIGHT] >= DISTANCE_THRESHOLD){
			flag = 1;
		}
		else{
			flag = 0;
		}

		/*tempo = get_tick();
		 if (tempo >= 5000000) { // 5000000 us → 5s
			flag = 1;
		}
		*/

		if(flag){
			motors(SPEED, SPEED);
		}
		else{
			motors(TURN_SPEED,-TURN_SPEED);
		}

		if(test_stop()){
			turn_edge();
		}
    }

}

void track(){
	uint8_t Lspeed=0, Rspeed=0;
	for(;;){
		update_distance_sensors();
Lspeed = TRACK_SPEED;
		if(distance_sensors[RIGHT] >= DISTANCE_THRESHOLD){
			Lspeed = TURN_SPEED;
		}
		Rspeed = TRACK_SPEED;
		if(distance_sensors[LEFT] >= DISTANCE_THRESHOLD){
			Rspeed = TURN_SPEED;
		}

		motors(SPEED, SPEED);
		if(test_stop()){
			turn_edge();
		}
  }
}
