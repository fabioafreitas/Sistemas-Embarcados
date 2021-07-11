int red = 11;
int green = 10;
int blue = 9;
int r = 0, g = 0, b = 0;
int x = 32;
void setup() {
  //Serial.begin(4800);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  delay(32);
  r+=x;
  if (r == 256) {
    r = 0;
    g+=x; 
  }
  if (g == 256) {
    g = 0;
    b+=x; 
  }
  if(b == 256) {
    b = 0;
  }
 /* Serial.print("Red:");
  Serial.println(r);
  Serial.print("Green:");
  Serial.println(g);
  Serial.print("Blue:");
  Serial.println(b);
  */
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}
