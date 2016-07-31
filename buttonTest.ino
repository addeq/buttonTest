
int amount = 0;
int mode = 1;
String RFID_KEY = "12002935500";
int inputMode = 1; //trigger for input
int balance = 0;
int price = 4; 
String dataVB = "";

void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,INPUT);
  Serial.begin(9600);
}

//////////////////////////////////////////////////////////////////////////////////

void loop() {
  //INPUTS
  switch(inputMode)
  
  case 1: ///////////////////////////RFID INPUT 
  {
  int RFID = digitalRead(10);
  //LCD PRINT "TAP YOUR RFID"
    if (RFID == HIGH){
    digitalWrite(13,HIGH);
    Serial.println(RFID_KEY); // KEY SEND TO VB
    inputMode = 2;
  }
  else {
     digitalWrite(13,LOW);
    }
  }
  break;
  
  case 2: ///////////////////////////BUTTONS
  {
  int CANCEL = digitalRead(11);
  int OK = digitalRead(12);

  if(CANCEL == HIGH) {
    inputMode = 1;
    }

    //BUYING PROCESS HERE!
    BUY();
      
  }
  break;

  default:
    inputMode = 1;
  break;
  
//////////////////////////////////////////////////////////////////////////////////

  //IF DATA FROM VB IS PRESENT - READ IT!
      if (Serial.available() > 0){
      dataVB = Serial.readString();
      }
      

//////////////////////////////////////////////////////////////////////////////////

    //BUYING & PRINTING
void BUY(){
  switch(mode)
  case 1: //GET DATA FROM VB (BALANCE) OR IF NOT EXIST
  {
  if (dataVB == "NOTEX"){
    //LCD PRINT NOT EXIST
    delay(3000);
    mode = 1;
    inputMode = 1;
  }
  else {
    if (dataVB == ""){
        //LCD PRINT PLEASE WAIT
    }

    else {
           balance = dataVB.toInt()
    //LCD PRINT BALANCE
    delay(3000);
    mode++;
    }
  }
 }
  break;

  
///////////////////////////////////////////////////////////

  case 2: //GET NUMBER OF BOOKLETS
  {
 ///////////////////////////// NEED DEBOUNCE!!!!!!
 // int plus = digitalRead();
 // int minus = digitalRead();

 if(plus == HIGH){
   if ( (amount+price) > balance) {
  //LCD PRINT NOT ENOUGH BALANCE
 }
 else{
  ++booklet;
  changeBalance();
 }
}

 else if (minus == HIGH){
  if((--booklet < 0)){
  /// - NUMBERS NOT ALLOWED
  }
  else {
    --booklet;
    changeBalance();
  }
 }




 //LCD PRINT BALANCE, AMOUNT, BOOKLET COUNT

 if(OK == HIGH)
 {
  mode++;
 }
 
  }
  break;

///////////////////////////////////////////////////////////

  case 3: //SEND NEW BALANCE TO VB
  {
  Serial.println(balance);
  count++;
  }
  break;
  
///////////////////////////////////////////////////////////
  case 4: // DISPENSE BOOKLET
  {
    //MACHINE PROCESS HERE!
  }
  break;
  
  default: // RESET BACK TO DEFAULT VALUES
    amount = 0;
    mode = 1;
    dataVB = "";
    RFID_KEY = "";
    inputMode = 1;
    balance = 0;
  break;

}

  // delay(2000);



  void changeBalance(){
  amount = booklet * price;
  balance -= amount;
  }

   

}
