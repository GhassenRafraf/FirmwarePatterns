//
// Sine wave generation with DAC
//

#include <stdint.h>
#define TABLE_SIZE 32
const uint16_t sine_table[TABLE_SIZE] = {
    2048, 2832, 3496, 3996, 4287, 4392, 4307, 4032,
    3584, 2992, 2312, 1592, 896, 352, 88, 32,
    88, 352, 896, 1592, 2312, 2992, 3584, 4032,
    4307, 4392, 4287, 3996, 3496, 2832, 2048, 0
    };
void configure_dac(void) { /* DAC config */ }
void configure_timer(void) { /* Timer config for 32 kHz */ }
void write_dac(uint16_t value) { /* Write to DAC */ }
void init_dac(void) {
    configure_dac();
    configure_timer();
}
void timer_isr(void) {
    static uint8_t index = 0;
    write_dac(sine_table[index]);
    index = (index + 1) % TABLE_SIZE;
}
int main(void) {
    init_dac();
    while (1) {
        /* Wait for timer */
    }
    return 0;
}