int vibr_pin=6;
int LED_Pin=13;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(vibr_pin,INPUT);
pinMode(LED_Pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int val=digitalRead(vibr_pin);
Serial.println(val);
if(val==1)
  {
    digitalWrite(LED_Pin,HIGH);
    delay(1000);
    digitalWrite(LED_Pin,LOW);
    delay(1000);
   }
   else
   digitalWrite(LED_Pin,LOW);
}
