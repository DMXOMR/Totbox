
//----------- VARIABLES FOR THE SEVEN SEGMENT DISPLAY FUN --------------- 
const byte ledCharSet[10] = {B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111};   // NEED TO UNDERSTAND THIS BETTER

const int DATA = 17;            // assigns DATA to pin 17 (A3) on Arduino
const int LATCH = 18;           // assigns DATA to pin 18 (A4) on Arduino
const int CLOCK = 19;           // assigns DATA to pin 19 (A5) on Arduino
const int buttonPin = 2;        // assigns buttonPin to pin 2 on Arduino

int buttonState = 0;            // variable for reading the pushbutton status
int buttonVal = 1;              // variable to hold button counter value
int prestate = 0;               // variable to hold button counter value


//----------- VARIABLES FOR THE RGB LED FUN ---------------
const int bluePin = 10;         // assigns bluePin to pwm pin 10 on Arduino
const int greenPin = 6;         // assigns bluePin to pwm pin 6 on Arduino
const int redPin = 5;           // assigns bluePin to pwm pin 5 on Arduino

long int fade_goTime;
int fade_break = 20;

// -- SPECIAL THANKS TO ARDUINO FORUM FOR HELP/SOURCE CODE FOR THE FADE & RGB FUNCTIONS: https://forum.arduino.cc/index.php?topic=397913.0


//----------- VARIABLES FOR THE SPEAKER FUN ---------------
const int speakerPin = 8;       // assigns speakerPin to  pin 8 on Arduino
const int potPin = 14;          // assigns potPin to pin 14 (A0) on Arduino
 
int toneValue = 0;              // variable to hold the tone/speaker value, set to 0
int tonePot = 0;                // variable to hold the potentiometer, set to 0


boolean prevButton = LOW;       // defines a variable for the previous button state
boolean currentButton = LOW;    // defines a variable for the current button state



void setup() 
{
  fade_goTime = millis();
  
  pinMode(buttonPin, INPUT); 
  
  pinMode(LATCH, OUTPUT); 
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA,OUTPUT);
 
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  pinMode(speakerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  if(  millis() >= fade_goTime) fade();
  
  tonePot= analogRead(potPin);
  if(tonePot > 5) {
  toneValue = map(tonePot, 0, 1023, 250, 500);
  tone(speakerPin, toneValue);
  Serial.println(toneValue);
  }
  
  buttonState = debounce(buttonPin);          // read the state of the pushbutton value:
  
  if (buttonVal > 9) {buttonVal = 1; }        // if statement to make sure counter value never get higher than 9
  
  if (buttonState == HIGH && prestate == 0)   // check if the pushbutton is pressed. If it is, then the buttonState is HIGH:
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

}

//------- NOT EXACTLY SURE WHAT THIS FUNCTION DOES ------------
void fade()
{
 
  static unsigned int rgbColor[3] = {255,0,0}; //Start on red
  static int incColor = 1;
  static int decColor = 0;
  static int i = -1;
     
      // cross-fade the two colours.
      i++;
      if(i > 254) {
        i=0;
        decColor ++;
        if(decColor >2) decColor = 0;     
        if (decColor == 2)  incColor = 0;
        else incColor = decColor +1;
      }

        rgbColor[decColor] -= 1;
        rgbColor[incColor] += 1;
       
        setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);     
       fade_goTime = millis() + fade_break;       
   }
   
//------- NOT EXACTLY SURE WHAT THIS FUNCTION DOES
void setColorRgb(unsigned int redVal, unsigned int greenVal, unsigned int blueVal) {
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
 }

//------- DEBOUNCING FUNCTION
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
