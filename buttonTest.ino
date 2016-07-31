
String trigger  = "OK"; 
void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,INPUT);
  Serial.begin(9600);
}

void loop() {
  int a = digitalRead(10);
      if (Serial.available() > 0){
      trigger = Serial.readString();
      }
  if (a == HIGH){
    if (trigger == "OK"){
    
    Serial.println("INPUT");
    digitalWrite(13,HIGH);
    trigger = "NO";
    }
  }
  else {
    digitalWrite(13,LOW);
  }
  // delay(2000);

   

}
