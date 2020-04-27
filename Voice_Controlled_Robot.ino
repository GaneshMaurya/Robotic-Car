char readvoice;
char readvoic[70];
String directn;
int dist;
int i=0;
char wrd[3][25];
int sensor=11;
void setup() 
{
    Serial.begin(9600);
    pinMode(2,OUTPUT);  //left front wheel 
    pinMode(3,OUTPUT);  //left back wheel 
    pinMode(4,OUTPUT);  //right front wheel 
    pinMode(5,OUTPUT);  //right back wheel 
    pinMode(sensor,INPUT_PULLUP);  //LM 393
}

int calctime(int sens,int distance)    // This function calculates and rerotates the time needed for the motors to run for the robot to traverse the specified distance. 
{
  int start_time=0;
  int end_time=0;
  int steps=0;
  int steps_old=0;
  int temp;
  int rps;
  start_time=millis();
  end_time=start_time+1000;
  while(millis()<end_time)
   {
      if(digitalRead(sens))
      {
          steps=steps+1; 
          while(digitalRead(sens));
       }  
   }
    temp=steps-steps_old;
    steps_old=steps;
    rps=(temp/20);
    int time1; 
    time1=(distance/(rps*44))*1000;
    return time1; 
}

void getwords(char sentence[70], char words[3][25] )    //This function will be called to separate the the voice command given as input into two parts(direction and disance) {eg:"forward 10" meaning to move forward by 10 cm
{
  int a = 0;
  int i = 0;
  int index = 0;
  while (sentence[a] != '\0')
      {
        if (sentence[a] == ' ') { words[index][i] = '\0'; i=0; a++; index++; } // SPACE detected
 
        words[index][i++] = sentence[a++];
      }
      words[index][i] = '\0';
}

void loop() 
{
    while (Serial.available())
    {
        delay(3);
        readvoice=Serial.read();
        readvoic[i]=readvoice;
        i++;
        getwords(readvoic,wrd);
        directn=wrd[0];  //direction 
        dist=int(wrd[1]); //distance
        
    if(directn.length() > 0)
    {
        Serial.println(directn);

    if(directn == "forward")
    {
        digitalWrite(2, HIGH);    //robot moves forward
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        delay(calctime(sensor,dist)); //delays forward motion for time required for the robot to traverse the required distance
        digitalWrite(2, LOW);     //robot comes to a stop 
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    }
    
    if(directn == "backward")
    {
        digitalWrite(2, LOW);   //robot moves backword
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        delay(calctime(sensor,dist)); 
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    }
    if(directn == "left")
    {
        digitalWrite(2, LOW);   //robot rotates left 
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        delay(1000);    //for one second
        digitalWrite(2, HIGH);  //robot moves forward for required distance
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        delay(calctime(sensor,dist));
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    }
     if(directn == "right")
    {
        digitalWrite(2, HIGH);   //robot rotates right 
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        delay(1000);    
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        delay(calctime(sensor,dist));
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    }
  }
}
}
