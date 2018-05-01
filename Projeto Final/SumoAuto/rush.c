#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "strategies.h"


void rush() {
    motors_init();
    sensors_init();
    motors(SPEED,SPEED);
    for (;;){
        test_stop();
    }
    
}
