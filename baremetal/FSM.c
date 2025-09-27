//
// Finite State Machine for Traffic Light Control
//

#include <stdint.h>

// GPIO pin definitions (example)
#define NS_GREEN_PIN 0
#define NS_YELLOW_PIN 1
#define NS_RED_PIN 2
#define EW_GREEN_PIN 3
#define EW_YELLOW_PIN 4
#define EW_RED_PIN 5

// State enumeration
typedef enum {
    NS_GREEN, NS_YELLOW, NS_RED,
    EW_GREEN, EW_YELLOW, EW_RED
    } TrafficState;
// State durations (seconds)
const uint8_t state_durations[] = {30, 5, 35, 30, 5, 35};
// Global variables
volatile uint32_t timer_count = 0;
TrafficState current_state = NS_GREEN;
// Simulated GPIO functions
void gpio_set(uint8_t pin, uint8_t value) { /* Hardware-specific */ }
void timer_init(void) { /* Initialize 1s timer */ }
// Set LEDs based on state
void set_leds(TrafficState state) {
    gpio_set(NS_GREEN_PIN, 0); gpio_set(NS_YELLOW_PIN, 0); gpio_set(NS_RED_PIN, 0);
    gpio_set(EW_GREEN_PIN, 0); gpio_set(EW_YELLOW_PIN, 0); gpio_set(EW_RED_PIN, 0);
    switch (state) {
        case NS_GREEN: gpio_set(NS_GREEN_PIN, 1); gpio_set(EW_RED_PIN, 1); break;
        case NS_YELLOW: gpio_set(NS_YELLOW_PIN, 1); gpio_set(EW_RED_PIN, 1); break;
        case NS_RED: gpio_set(NS_RED_PIN, 1); gpio_set(EW_GREEN_PIN, 1); break;
        case EW_GREEN: gpio_set(EW_GREEN_PIN, 1); gpio_set(NS_RED_PIN, 1); break;
        case EW_YELLOW: gpio_set(EW_YELLOW_PIN, 1); gpio_set(NS_RED_PIN, 1); break;
        case EW_RED: gpio_set(EW_RED_PIN, 1); gpio_set(NS_GREEN_PIN, 1); break;
    }
}
// Get next state
TrafficState get_next_state(TrafficState state) {
    switch (state) {
        case NS_GREEN: return NS_YELLOW;
        case NS_YELLOW: return NS_RED;
        case NS_RED: return EW_GREEN;
        case EW_GREEN: return EW_YELLOW;
        case EW_YELLOW: return EW_RED;
        case EW_RED: return NS_GREEN;
    }
    return NS_GREEN; // Fallback
}
// Timer interrupt handler
void timer_isr(void) {
    timer_count++;
}

// FSM logic
void traffic_light_fsm(void) {
    if (timer_count >= state_durations[current_state]) {
        set_leds(current_state);
        current_state = get_next_state(current_state);
        timer_count = 0;
    }
}
int main(void) {
    timer_init();
    set_leds(current_state);
    while (1) {
        traffic_light_fsm();
    }
    return 0;
}

