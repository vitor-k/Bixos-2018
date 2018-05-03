#include <avr/io.h>
#include "sensors.h"
#include "motors.h"

uint16_t line_sensors[2];
uint16_t distance_sensors[2];
uint32_t timer1;
uint32_t timer2 = 0;
uint32_t timer3;
uint32_t timer4 = 0;

/* inicializa os sensores */
void sensors_init() {
    DDRC &= ~(1 << PC0) & ~(1 << PC1) & ~(1 << PC2) & ~(1 << PC3);
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2);
}

/* atualiza valor dos sensores de linha */
void update_line_sensors() {
    ADMUX = (ADMUX & 0xF8) | 2;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    line_sensors[0] = ADC;

    ADMUX = (ADMUX & 0xF8) | 3;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    line_sensors[1] = ADC;
}

/* atualiza valor dos sensores de distância */
void update_distance_sensors() {
    ADMUX = (ADMUX & 0xF8) | 0;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    distance_sensors[0] = ADC;

    ADMUX = (ADMUX & 0xF8) | 1;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    distance_sensors[1] = ADC;
}

/* para os motores caso o robo detecte a linha*/
int test_stop(){
    update_line_sensors();
    if(line_sensors[RIGHT] >= 800 || line_sensors[LEFT] >= 800)
    {
        motors(0,0);
        return 1;
    }
    else{
        return 0;
    }
}
