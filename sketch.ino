#define RED 25
#define YELLOW 26
#define GREEN 27
#define BUTTON 18
int currentState = 0;
unsigned long startTime = 0;
bool emergencyMode = false;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
int stableButtonState = HIGH;
const unsigned long RED_TIME = 5000;
const unsigned long YELLOW_TIME = 2000;
const unsigned long GREEN_TIME = 5000;
const unsigned long DEBOUNCE_DELAY = 50;

void setup()
{
  
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  digitalWrite(RED,LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(GREEN,LOW);
  currentState = 0;
  startTime = millis();

}
void updateLights()
{
  switch(currentState)
  {
    case 0:
       digitalWrite(RED,HIGH);
       digitalWrite(YELLOW,LOW);
       digitalWrite(GREEN,LOW); 
       break;
    case 1:
      digitalWrite(RED,LOW);
      digitalWrite(YELLOW,HIGH);
      digitalWrite(GREEN,LOW);
      break;
    case 2:
      digitalWrite(RED,LOW);
      digitalWrite(YELLOW,LOW);
      digitalWrite(GREEN,HIGH);
      break;
    default:
      digitalWrite(RED,LOW);
      digitalWrite(YELLOW,LOW);
      digitalWrite(GREEN,LOW);
  }
}

void updateState()
{
  if(currentState == 0)
  {
    if((millis()-startTime) >= RED_TIME)
    {
      currentState = 1;
      startTime = millis();
    }

  }

  else if(currentState == 1)
  {
    if((millis()-startTime) >= YELLOW_TIME)
    {
      currentState = 2;
      startTime = millis();
    }
  }
 else if(currentState == 2)
  {
    if((millis()-startTime) >= GREEN_TIME)
    {
      currentState = 0;
      startTime = millis();
    }
  }
}
void loop()
{
  int reading = digitalRead(BUTTON);

  if (reading != lastButtonState)
  {
      lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    if (reading != stableButtonState)
    {
        stableButtonState = reading;

        if (stableButtonState == LOW)
        {
            emergencyMode = !emergencyMode;
            currentState = 0;
            startTime = millis();
        }
    }
  }

  lastButtonState = reading;

    

  if(emergencyMode)
  {
    digitalWrite(RED,HIGH);
    digitalWrite(YELLOW,LOW);
    digitalWrite(GREEN,LOW);
    return;
  }
  
  updateState();
  updateLights();
  
}