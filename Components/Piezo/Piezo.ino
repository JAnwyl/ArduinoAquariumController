/*
Jared Anwyl
Ground and Defined Pin Unless needs resistor
Tried resistor and was almost too quite to hear
wouldn't have heard it except breadboard was in face
*/
int pinSpeaker = 10;

void setup () {
    pinMode(pinSpeaker, OUTPUT);
}

void loop () {
    playTone(750, 500);
    delay(750);
}

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

