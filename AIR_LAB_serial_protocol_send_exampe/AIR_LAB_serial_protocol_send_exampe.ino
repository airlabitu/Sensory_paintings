
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print('c');
  Serial.print("111");
  Serial.print('w');
  Serial.print(222);
  delay(2000);
}
