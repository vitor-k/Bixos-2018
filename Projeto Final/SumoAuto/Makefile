
#avr-gcc -c arquivo.c -o arquivo.o -mmcu=id_microcontrolador -std=c99 -Wall -Wextra -Os
#avr-gcc -o main.elf <arquivos objeto> -mmcu=id_microcontrolador -std=c99 -Wall -Wextra -Os
#avr-objcopy -j .text -j .data -O ihex main.elf main.hex
.PHONY : clean

clean: 
	rm main.o motors.o sensors.o utils.o timer.o rush.o search_rotate.o wait_n_see.o main.elf
	
main.hex : main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf : main.o motors.o sensors.o utils.o timer.o rush.o search_rotate.o wait_n_see.o
	avr-gcc -o main.elf main.o motors.o sensors.o utils.o timer.o rush.o search_rotate.o wait_n_see.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

main.o : main.c
	avr-gcc -c main.c -o main.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

timer.o : timer.c
	avr-gcc -c timer.c -o timer.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

utils.o : utils.c
	avr-gcc -c utils.c -o utils.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

sensors.o : sensors.c
	avr-gcc -c sensors.c -o sensors.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

motors.o : motors.c
	avr-gcc -c motors.c -o motors.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

wait_n_see.o : wait_n_see.c
	avr-gcc -c wait_n_see.c -o wait_n_see.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

rush.o : rush.c
	avr-gcc -c rush.c -o rush.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

search_rotate.o : search_rotate.c
	avr-gcc -c search_rotate.c -o search_rotate.o -mmcu=atmega168 -std=c99 -Wall -Wextra -Os


