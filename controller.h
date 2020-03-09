#ifndef CONTROLLER_H
#define CONTROLLER_H

//void send_bit(int bit);

//void send_start_word(void);

void controller_init(unsigned int out_gpio, unsigned int in_gpio);

void controller_start_asm(void); 

#endif
