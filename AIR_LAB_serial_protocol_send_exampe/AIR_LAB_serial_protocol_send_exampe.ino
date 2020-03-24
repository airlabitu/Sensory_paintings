void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(0); // channel
  Serial.print('c');
  Serial.print(999); // value
  Serial.print('w');  
  delay(100);
  Serial.print(1); // channel
  Serial.print('c');
  Serial.print(100); // value
  Serial.print('w');
  delay(2000);
}
