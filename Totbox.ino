
//const variables 

const byte ledCharSet[10] = {B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111};
const int buttonPin = 12;
const int blue = 11;
const int green = 10;
const int red = 9;
const int LATCH = 7;
const int CLOCK = 8;
const int DATA = 4;
const int speaker = 2;


boolean prevButton = LOW;        // defines a variable for the previous button state
boolean currentButton = LOW;    // defines a variable for the current button state
int buttonState = 0;            // variable for reading the pushbutton status
int buttonVal = 1;              // variable to hold button counter value
int prestate =0;
int toneValue = 0;            // variable to hold the tone/speaker value
int redValue = 10;
int blueValue = 10;
int greenValue = 10;

void setup() 
{
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input
  pinMode(6, INPUT);
  pinMode(LATCH, OUTPUT); 
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(speaker, OUTPUT); // initializes the speaker pin as an output
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {

  int switchVal = digitalRead(6);
  if(switchVal == LOW){
    analogWrite(green, 0);
    analogWrite(red, 0);
    analogWrite(blue, 0);
  }

  if(switchVal == HIGH){
  
    RGBled(); // function that drives the RGB LED

  }
  
  int pot1= analogRead(A0);
  buttonState = debounce(buttonPin); // read the state of the pushbutton value:
  
  


  if(pot1 > 5) {
  toneValue = map(pot1, 0, 1023, 250, 500);
  tone(speaker, toneValue);
  }
  

  if (buttonVal > 9) {buttonVal = 1; } // if statement to make sure counter value never get higher than 9
  
  if (buttonState == HIGH && prestate == 0)  // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
  {
    buttonVal++;
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,~(ledCharSet[buttonVal]));
    digitalWrite(LATCH,HIGH);
    prestate = 1;
   } 
    
  if(buttonState == LOW) 
  {
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,~(ledCharSet[buttonVal]));
    digitalWrite(LATCH,HIGH);
    prestate = 0;
  }
// noTone(speaker);

}

 // RGB LED fader function

void RGBled()
{
  int redVal = 255;
  int blueVal = 0;
  int greenVal = 0;
  for( int i = 0 ; i < 255 ; i += 1 ){
    greenVal += 1;
    redVal -= 1;
    analogWrite(green, greenVal );
    analogWrite(red, redVal );

    delay(5);
  }

  redVal = 0;
  blueVal = 0;
  greenVal = 255;
  
  for( int i = 0 ; i < 255 ; i += 1 ){
    blueVal += 1;
    greenVal -= 1;
    analogWrite(blue, blueVal );
    analogWrite(green, greenVal );

    delay(5);
  }

  redVal = 0;
  blueVal = 255;
  greenVal = 0;
  for( int i = 0 ; i < 255 ; i += 1 ){
    redVal += 1;
    blueVal -= 1;
    analogWrite(red, redVal );
    analogWrite(blue, blueVal );

    delay(5);
  }
}


// debouncing function 
boolean debounce(boolean prev)
{
  boolean current = digitalRead(buttonPin); // checks the button state and storing it in the freshly defined boolean variable current
  if (prev != current)                  // if the prev variable is not equal to current
  {
    delay(5);                           // wait 5 milliseconds
    current = digitalRead(buttonPin);      // checks the button state and stores it in the variable current
  }
  return current;             //returns the value in the current variable back from the function
}
