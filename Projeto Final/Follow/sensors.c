#include <avr/io.h>
#include <util/delay.h>
#include "sensors.h"
#include "utils.h"

unsigned int sensors[NUM_SENSORS];

/*  Inicialização dos sensores.
 *
 *  Inicializa ADCs com maior prescaler para precisão máxima e tensão de referência no
 *  no pino AREF (ligado em 5V)
 */

void sensorsInit(void) {
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

/*  Atualização de todos os sensores
 *   
 *  Atualiza o vetor sensors com a leitura ADC dos sensores.
 *
 *  A ordem é da esquerda para a direita (0 o da esquerda e 6 o da direita)
 *
 */

void sensorsUpdate(void) {
	sensors[0] = sensorRead(SENSOR1);
	sensors[1] = sensorRead(SENSOR2);
	sensors[2] = sensorRead(SENSOR3);
	sensors[3] = sensorRead(SENSOR4);
	sensors[4] = sensorRead(SENSOR5);
	sensors[5] = sensorRead(SENSOR6);
	sensors[6] = sensorRead(SENSOR7);
}

/*  Le o valor não processado de um canal de ADC.
 *
 *	Le o resultado da conversão ADC de um canal especificado.
 *
 *	sensor é o canal ADC especificado.
 *
 *	Retorna o resultado da conversão ADC do canal especificado.
 *
 */

unsigned int sensorRead(sensor_t sensor) {
	// ADC channel must be within range 0 ~ 7.
	sensor &= 7;

	// Sets ADC MUX pins to select the desired channel.
	ADMUX = sensor;

	// Start conversion.
	ADCSRA |= (1<<ADSC);

	// Wait for conversion to finish.
	while(!(ADCSRA & (1<<ADIF)));

	// Clear conversion flag by setting ADIF bit.
	ADCSRA |= (1<<ADIF);

	// Return ADC (ADCH<<8 + ADCL) register.
	return ADC;
}
