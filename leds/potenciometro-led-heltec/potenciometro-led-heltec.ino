int pinoLED = 12;
int pinoPOT = 13;
int brilho;
 
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup () {
pinMode(pinoPOT, INPUT);
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(pinoLED, ledChannel);
}
 
void loop () {
brilho = analogRead(pinoPOT);
brilho = map(brilho, 0, 4095, 0, 255);
ledcWrite(ledChannel, brilho);
delay(100);
}
