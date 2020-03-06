#ifndef CONTROLLER_H
#define CONTROLLER_H

void send_bit(int bit);

void send_start_word();

void controller_init(unsigned int data_gpio);

#endif
