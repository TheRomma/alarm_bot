int state = 0;

long timer = 0;
long last = 0;
long delta = 0;
long now = 0;
long until = 0;

const int LEFT = 6;
const int RIGHT = 3;
const int TRIG = 7;
const int ECHO = 10;
const int BUTTON = 12;
const int POTEN = A0;
const int BUZZER = 2;

void setup()
{
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  switch(state){
  	case 0:
        if(digitalRead(BUTTON)){
			state = 1;
          	now = millis();
          	until = analogRead(POTEN) * 42.187;//About 12h max.
          	timer = 0;
          	delay(1000);
        }
  	break;
    
    case 1:
        last = now;
        now = millis();
        delta = now - last;
       	timer += delta;
       	if(timer >= until){
       		state = 2;
          	timer = 0;
           	until = 0;
           	tone(BUZZER, 500);
           	delay(1000);
        }else if(digitalRead(BUTTON)){
         	state = 0;
          	timer = 0;
           	until = 0;
           	now = 0;
           	delay(1000);
        }
    	break;
    
    case 2:
        if(digitalRead(BUTTON)){
            state = 0;
            timer = 0;
            until = 0;
            analogWrite(LEFT, 0);
            analogWrite(RIGHT, 0);
            last = 0;
            noTone(BUZZER);
            delay(1000);
        }else{
            digitalWrite(TRIG, LOW);
            delayMicroseconds(2);
            digitalWrite(TRIG, HIGH);
            delayMicroseconds(10);
            digitalWrite(TRIG, LOW);
            int duration = pulseIn(ECHO, HIGH);
            int cm = duration / 29 / 2;
            if(cm < 50){
                analogWrite(LEFT, 255);
                analogWrite(RIGHT, 0);
            }else{
                analogWrite(LEFT, 255);
                analogWrite(RIGHT, 255);
            }
            delay(100);
        break;
    }
  }
}
