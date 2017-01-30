int leftR = 3;
int leftB = 4;
int rightR = 5;
int rightB = 6;
int rightButton = 9; //Change
int leftButton = 8; //Change

int randomizeBeacon = 0;
int waitForPress = 1;
boolean redBlue = true;
int counter = 0;

int curState = randomizeBeacon;


void setup() {
  // put your setup code here, to run once:
  pinMode(leftR, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(rightR, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(rightButton, INPUT);
  digitalWrite(rightButton, HIGH);
  pinMode(leftButton, INPUT);
  digitalWrite(leftButton, HIGH);
  pinMode(13, OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  Serial.println("Hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  /*if (rightState == HIGH) {
    rightState = LOW;
  } else {
    rightState = HIGH;
  }
  if (leftState == HIGH) {
    leftState = LOW;
  } else {
    leftState = HIGH;
  }*/
  rightState = !rightState;
  leftState = !leftState;
  if (curState == randomizeBeacon) {
    Serial.println("Randomizing Beacon");
    digitalWrite(leftR, HIGH);
    digitalWrite(leftB, LOW);
    digitalWrite(rightB, HIGH);
    digitalWrite(rightR, LOW);
    int numTimes = random(11,15);
    int oldDelay = 10;
    for (int i = 0; i < numTimes; i++) {
      switchColors();
      oldDelay += (numTimes);
      delay(oldDelay);
    }
    curState = waitForPress;
  }
  if (curState == waitForPress) {

    if (rightState == HIGH || leftState == HIGH) {
      Serial.println("Rightstate");
      Serial.println(rightState);
      Serial.println("LeftState");
      Serial.println(leftState);
     
      
        String lightState = getColors();
        Serial.println(lightState);
        if (lightState == "All Blue") {
        setColors("All Red");
        delay(5000);
        } else if (lightState == "All Red") {
        setColors("All Blue");
        delay(5000);
        } else {
        if (rightState == HIGH && leftState == LOW) {
          if (lightState == "Red Blue") {
            setColors("All Blue");
            delay(5000);
          } else if (lightState == "Blue Red") {
            setColors("All Red");
            delay(5000);
          }
        } else if (rightState == LOW && leftState == HIGH) {
          if (lightState == "Red Blue") {
            setColors("All Red");
            delay(5000);
          } else if (lightState == "Blue Red") {
            setColors("All Blue");
            delay(5000);
          }
        }
        }
      
    }
  }
}

void setColors(String order) { //Left to right
  Serial.println("Called SetColors()");
  if (order == "All Red") {
    digitalWrite(leftR, HIGH);
    digitalWrite(leftB, LOW);
    digitalWrite(rightR, HIGH);
    digitalWrite(rightB, LOW);
    Blink(true);
  } else if (order == "All Blue") {
    digitalWrite(leftR, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightR, LOW);
    digitalWrite(rightB, HIGH);
    Blink(false);
  } else if (order == "Blue Red") { //I later realize this is useless....
    digitalWrite(leftR, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightR, HIGH);
    digitalWrite(rightB, LOW);
  } else if (order == "Red Blue") { //Same goes to you m8 ^
    digitalWrite(leftR, HIGH);
    digitalWrite(leftB, LOW);
    digitalWrite(rightR, LOW);
    digitalWrite(rightB, HIGH);
  }
}


int Blink(boolean red) {
  int blinkdel = 30 + (counter*30);
  if (counter < 3) {
    if (red) {
      digitalWrite(leftR, HIGH);
      digitalWrite(leftB, LOW);
      digitalWrite(rightR, HIGH);
      digitalWrite(rightB, LOW);
      delay(blinkdel);
      digitalWrite(leftR, LOW);
      digitalWrite(leftB, LOW);
      digitalWrite(rightR, LOW);
      digitalWrite(rightB, LOW);
      delay(blinkdel);
      digitalWrite(leftR, HIGH);
      digitalWrite(leftB, LOW);
      digitalWrite(rightR, HIGH);
      digitalWrite(rightB, LOW);
      delay(blinkdel);
      counter++;
      Blink(true);
    } else {
      digitalWrite(leftR, LOW);
      digitalWrite(leftB, HIGH);
      digitalWrite(rightR, LOW);
      digitalWrite(rightB, HIGH);
      delay(blinkdel);
      digitalWrite(leftR, LOW);
      digitalWrite(leftB, LOW);
      digitalWrite(rightR, LOW);
      digitalWrite(rightB, LOW);
      delay(blinkdel);
      digitalWrite(leftR, LOW);
      digitalWrite(leftB, HIGH);
      digitalWrite(rightR, LOW);
      digitalWrite(rightB, HIGH);
      delay(blinkdel);
      counter++;
      Blink(false);
    }
  } else {
    counter = 0;
    return 0;
  }
}

void setState(boolean rB) { //Left to right
  if (rB) {
    redBlue = true;
    digitalWrite(leftR, HIGH);
    digitalWrite(leftB, LOW);
    digitalWrite(rightB, HIGH);
    digitalWrite(rightR, LOW);
  } else {
    redBlue = false;
    digitalWrite(leftR, LOW);
    digitalWrite(leftB, HIGH);
    digitalWrite(rightB, LOW);
    digitalWrite(rightR, HIGH);
  }
}

String getColors() { //Left to right
  int rightR2 = digitalRead(rightR);
  int leftR2 = digitalRead(leftR);
  int rightB2 = digitalRead(rightB);
  int leftB2 = digitalRead(leftB);
  if (rightR2 == LOW && rightB2 == HIGH) {
    if (leftR2 == LOW && leftB2 == HIGH) {
      return "All Blue";
    } else {
      if (leftR2 == HIGH && leftB2 == LOW) {
        return "Red Blue";
      }
    }
  } else {
    if (rightR2 == HIGH && rightB2 == LOW) {
      if (leftR2 == HIGH && leftB2 == LOW) {
        return "All Red";
      } else {
        if (leftR2 == LOW && leftB2 == HIGH) {
          return "Blue Red";
        }
      }
    }
  }
  return "wot";
}

void switchColors() {
  setState(!redBlue);
}
