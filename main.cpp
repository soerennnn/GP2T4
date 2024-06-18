#define F_CPU 16000000UL // CPU läuft mit 16 MHz

#include <avr/io.h>


int main(void)  {
    // Konfiguration der DDR-Register
    DDRD &= ~(1 << PC0); // PC0 (Pin 37) als Eingang für den Taster
    DDRB |= (1 << PB5);  // PB5 (Pin 11) als Ausgang für die LED

    // Timer 1 konfigurieren
    TCCR1A |= (1 << COM1A0); // Toggle OC1A (PB1) on Compare Match
    TCCR1B |= (1 << WGM12);  // WGM12 = 1 Zähler wieder auf 0
    

    // Prescale auf 256 setzen
    TCCR1B |= (1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);

    // Compare Match Werte
    // int NullKomma5Hz = (F_CPU / 256); =  62500
    // int ZweiHz = (F_CPU / 256) / 4; = 15625


    while(1){
        // Überprüfen des Taster-Zustands
        // Während der Taster gedrückt ist, soll die LED mit 2Hz blinken. Ist der Taster nicht gedrückt dauerhaft leuchten
        if (PINC & (1 << PC0)) {
            TCCR1A |= (1 << COM1A0); // Toggle OC1A (PB1) on Compare Match
             // Taster gedrückt, setze Compare Match Wert für 2Hz
            OCR1A = 15625;
            }   
        else {
            // Taster nicht gedrückt
            TCCR1A &= ~(1 << COM1A0); // Toggle OC1A (PB1) on Compare Match
            PORTB |= (1<<PB5);
        }
}
}




    