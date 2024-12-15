const int potPin = A7;       
const int photoPin = A5;    
const int buttonPin = 5;    
const int redLEDPin = 9;     
const int blueLEDPin = 7;   

int potTargetMin = 190;     
int potTargetMax = 210;  
int photoMin = 0;           
int photoMax = 40;          

bool potStepDone = false;
bool photoStepDone = false;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);

  Serial.println("System initialized. Begin sequence...");
}

void loop() {
  int potValue = analogRead(potPin);
  Serial.print("Potentiometer value: ");
  Serial.println(potValue);
  if (potValue >= potTargetMin && potValue <= potTargetMax) {
    Serial.println("Potentiometer value correct!");
    digitalWrite(blueLEDPin, HIGH);
    digitalWrite(blueLEDPin, LOW);
  } else {
    Serial.println("Potentiometer value incorrect.");
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  }

  // Step 2: Photoresistor Check
  if (!photoStepDone) {
    int photoValue = analogRead(photoPin);
    Serial.print("Photoresistor value: ");
    Serial.println(photoValue);
    if (photoValue >= photoMin && photoValue <= photoMax) {
      Serial.println("Photoresistor value correct!");
      photoStepDone = true;
      digitalWrite(blueLEDPin, HIGH);
      delay(100);
      digitalWrite(blueLEDPin, LOW);
    } else {
      Serial.println("Photoresistor value incorrect.");
      digitalWrite(redLEDPin, HIGH);
      delay(100);
      digitalWrite(redLEDPin, LOW);
    }
    return; 
  }

  if (photoStepDone && potStepDone) {
    Serial.println("Awaiting button press...");
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("Button pressed! Sequence complete!");
      digitalWrite(blueLEDPin, HIGH); 
      delay(3000);
      digitalWrite(blueLEDPin, LOW);
      resetSystem();
    } else {
      Serial.println("Button not pressed yet.");
      delay(200); 
    }
  }
}

void resetSystem() {
  potStepDone = false;
  photoStepDone = false;
  digitalWrite(redLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
  Serial.println("System reset. Ready for a new attempt.");
}
