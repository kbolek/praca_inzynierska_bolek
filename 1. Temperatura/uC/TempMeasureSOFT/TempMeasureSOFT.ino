void setup() {
  Serial.begin(9600);
}

void loop() {
  String ser = Serial.readStringUntil('\n');
  Serial.print(String("test") + '\n');   
}
