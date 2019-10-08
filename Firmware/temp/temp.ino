int a = 0;
void setup() {
  // put your setup code here, to run once:
  long baudRate = 9600;
  Serial.begin(baudRate);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int l = analogRead(A0);
  int r = analogRead(A1);

  Serial.println("Left");
  Serial.println(l);
  Serial.println("Right");
  Serial.println(r);
  Serial.println();

  delay(1000);
}
