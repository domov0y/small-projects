#define F_CPU 9600000UL  // Internal 9.6 МГц
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define POT_PIN PB3  // ADC3, пин 2 физически

void adc_init() {
  DDRB &= ~(1 << POT_PIN);  // Вход
  ADMUX = (1 << MUX1);      // ADC3, Vcc ref, right adjust
  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // ADC on, prescaler 128 (~75кГц)
}

uint16_t adc_read() {
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

int main() {
  DDRB |= (1 << PB1);  // PWM на PB1 (пин 6)
  int voltage=0;
  // PWM ~25 кГц: Fast PWM, prescaler 8, TOP=47

  TCCR0A = _BV(COM0B1) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS00);
  // Set TOP and initialize duty cycle to zero(0)
  OCR0A = 192; // TOP - DO NOT CHANGE, SETS PWM PULSE RATE
  OCR0B = 192; // duty cycle for Pin 1(PB1)
  
  adc_init();
  
  while(1) {
    uint16_t adc_val = adc_read();

     voltage= adc_val >> 2;  // 10-bit -> 8-bit (0-255)
     if (voltage <192)OCR0B=voltage; else OCR0B=192;
    _delay_ms(50);         // Обновление ~20 Гц
  }
}