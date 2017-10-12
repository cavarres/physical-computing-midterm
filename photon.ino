

Servo myservo;  // servo control object
const int ALARM_PIN = D2;  // alarm pin
int value;
double angle;
int button1 = 6; //button pin, connect to ground to move servo
int press1 = 0; 

void setup()
{

  Serial.begin(9600);
  myservo.attach(3);
  Particle.subscribe("rob-camila", lowMoisture); // set up function to connect to Rob
  pinMode(ALARM_PIN, OUTPUT);
  

}

//Interaction with Rob: Rob message triggers event in Camila's device.
// function makes an alarm sound whenever Rob sends the "hour" message
void lowMoisture(const char *event, const char *data){
    String message = data;
    if (message == "hour"){
        tone(ALARM_PIN, 523, 2000);}

}


int position = 90; // start servo in the middle
int countsec = 0; // countsec will keep track of consecutive seconds in which the "eye" button is pressed

void loop() {
  
  // return hand to 90 degrees when it has reached the limit. 
  if (position >= 160 | position == 0){
     position = 90;
     myservo.write(position);
     delay(1000);
  }
  
 
  press1 = digitalRead(button1);
  
  
  if(press1 == LOW){ // when button not pressed, move clockwise
    position += 2;
    myservo.write(position);                 
    delay(1000);
    Serial.println(position);
    Serial.print("LOW");
    countsec == 0; // reset counsec to 0
  } 
    
  else { // when button  pressed, move counter-clockwise
  	position -= 2; 
    myservo.write(position);                 
    delay(1000);
    Serial.println(position);
    Serial.print("HIGH");
    countsec += 1; //start counting seconds since button was pressed
  }
  
  Serial.println(countsec);
  
  //Interaction with Rob: Camila's message triggers event in Rob's device.
  if (countsec == 20){ // if button has been pressed for 20 seconds, publish that it's been a great day. 
      Particle.publish("rob-camila", "Great Day!");
      countsec == 0;
  }
  

}