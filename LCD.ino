
//const variables 

const byte ledCharSet[10] = {B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111};
const int ledPin = 5;
const int buttonPin = 12;
const int LATCH = 7;
const int CLOCK = 8;
const int DATA = 4;


boolean prevButton = LOW;        // defines a variable for the previous button state
boolean currentButton = LOW;    // defines a variable for the current button state
int buttonState = 0;            // variable for reading the pushbutton status
int buttonVal = 1;              // variable to hold button counter value
int prestate =0;

void setup() 
{
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input:
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  Serial.println(buttonVal);
  buttonState = debounce(buttonPin); // read the state of the pushbutton value:
  
  if (buttonVal > 9) { // if statement to make sure counter value never get higher than 9
    buttonVal = 1; }
  

  if (buttonState == HIGH && prestate == 0)  // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
  {
    buttonVal++;
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,~(ledCharSet[buttonVal]));
    digitalWrite(LATCH,HIGH);
    prestate = 1;
   } 
    
  else if(buttonState == LOW) 
  {
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,~(ledCharSet[buttonVal]));
    digitalWrite(LATCH,HIGH);
    prestate = 0;
  
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
