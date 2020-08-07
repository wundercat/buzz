
// GPIO pin names
// int led = 8;    // "D8" is Nano pin 11
int led = 13;
int D7 = 7;  // a green led
int D6 = 6;  // a green led
int D9 = 9;    // speaker +
int D10 = 10;    // speaker -
int D11 = 11;    // headphone +
int D12 = 12;     // headphone switch
// "D4" is 7

int ticker=0;
int modulate=0;
unsigned char pinn=13;     // pin numbers
unsigned char speak = 0;   // make noise


// Voltage on the test leads in 5 millivolt steps.
int    redlead, blacklead, same, spkr;
int    diffi, absi =1, ;
int    phonesin = 0; 

void setup() {                
  noInterrupts();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  for (pinn=2; pinn < 12; pinn++){
    pinMode(pinn, OUTPUT);
    digitalWrite (pinn, LOW);
  }
  pinMode(D12, INPUT_PULLUP);  // high = phones connected
  pinMode(A0,  INPUT);
  pinMode(A1,  INPUT);

  //  Unused pins shouldn't dangle.
  pinMode(A2,  OUTPUT);
  pinMode(A3,  OUTPUT);
  pinMode(A4,  OUTPUT);
  pinMode(A5,  OUTPUT);
  pinMode(A6,  OUTPUT);
  pinMode(A7,  OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);

  Serial.begin(9600);
  Serial.println( "Starting." );

  OCR0A = 0xAF;          //  a value that appears once in ticker's range
  TIMSK0 |= _BV(OCIE0A);   //  enable the Timer 0 interrupt
  interrupts();
  
}

void pip(){
  digitalWrite( D10, LOW );
  digitalWrite( D9, HIGH);
  delayMicroseconds( 80 );
  digitalWrite( D9, LOW);
  delayMicroseconds( 80 );
}

void beepspkr(){
  for (pinn = 0; pinn < 6; pinn++){
    pip();
  }
}

void clickky(){
  digitalWrite( D11, LOW );
  digitalWrite( D11, HIGH);
  delayMicroseconds( 80 );
  digitalWrite( D11, LOW);
  delayMicroseconds( 80 );
}
void beepphones(){
  for (pinn = 0; pinn < 6; pinn++){
    clickky();
  }
}

SIGNAL(TIMER0_COMPA_vect) 
{
//  1 ms timer service 
  ticker++;
  if( ticker >=4096 ){
    ticker=0;
  }


  //   If headphone plug is present, D12 pullup will read high.
  //   If no phones present, D11 will drive D12 low.
  digitalWrite( D11, LOW);
  phonesin = digitalRead( D12 );
  if (speak) {
    if (phonesin) {
      beepphones();
    }else{
      beepspkr();
    }
  }
}


void darkled() {
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}

void greenled() {
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
}

void loop() {
  
  redlead   = analogRead(A0);
  blacklead = analogRead(A1);
  
  diffi     = redlead - blacklead ;
  
  // absolute value
  if( redlead > blacklead ){
    absi = redlead - blacklead ;
  }else{
    absi = blacklead - redlead ;
  }
  if ( redlead == blacklead ){
    absi = 0;
  }
  
  if (  absi < 2  ){   //  < 10 mv  +/- 5
    greenled();
    speak = 1;
  }else{
    darkled();
    speak = 0;
  }
  
}
