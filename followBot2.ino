#include <AFMotor.h>

AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

AF_DCMotor motorLeft (3, MOTOR12_64KHZ);



int left_sensor = 110;                                             //variable for left sensor
int right_sensor = 110;                                            //variable for right sensor
int cent_sensor = 110;
int value;                                                       //variable for temporary value
int corner;                                                     // state variable for corner situation  
bool getInput = true;
int testLoop = 0;
bool reStart = true;
bool firstTry = true;


void setup()
{
  pinMode(5, OUTPUT);                                         //setting the digital pins to output mode for 
  pinMode(4, OUTPUT);                                          //contorlling the motor  driver 
  pinMode(3, OUTPUT);    
  pinMode(2, OUTPUT);  
  Serial.begin(9600);
  motor.setSpeed(150);     // set the speed to 200/255
  motorLeft.setSpeed (150);
}

void loop()
{

if (firstTry == true)
{
  shutDown();
while (firstTry == true)
{

  Serial.print ("FIRST TRY ");
  
value = analogRead(4);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(2);
  right_sensor = map(value, 4, 429, 0, 255);
  value = analogRead(3);
  cent_sensor = map(value, 4, 429, 0, 255);

if (left_sensor < 100 || (right_sensor < 100 || cent_sensor < 100))
{


  firstTry = false;
  break;
}

}

  
  firstTry = false;
}


  
  value = analogRead(4);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(2);
  right_sensor = map(value, 4, 429, 0, 255);
  value = analogRead(3);
  cent_sensor = map(value, 4, 429, 0, 255);

getInput = true;
testLoop = 0;
reStart = true;


if((left_sensor > 100 && right_sensor > 100) && cent_sensor > 100)
{
  getInput = false;

forward();


while (getInput == false)
{


  value = analogRead(4);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(2);
  right_sensor = map(value, 4, 429, 0, 255);
  value = analogRead(3);
  cent_sensor = map(value, 4, 429, 0, 255);

        if (left_sensor < 100 || (right_sensor < 100 || cent_sensor < 100))
        {
          getInput = true;
          break;
        }

        else
        {testLoop ++;
         delay (10);
         
        }


if (testLoop > 100)
{shutDown();
reStart = false;
break;
}
  
}
}


while (reStart == false)
{

  value = analogRead(4);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(2);
  right_sensor = map(value, 4, 429, 0, 255);
  value = analogRead(3);
  cent_sensor = map(value, 4, 429, 0, 255);

if (left_sensor < 100 || (right_sensor < 100 || cent_sensor < 100))
{


  reStart = true;
  break;
}

delay (20);

}

  
  Serial.print(" Sensor Left  = ");                       // printing the values of both sensor into 
  Serial.print(left_sensor);                              // serial monitor for inspection     
  Serial.print(" Sensor Right = ");      
  Serial.print(right_sensor);
  Serial.print ("Center = ");
  Serial.println (cent_sensor);





if (reStart == true)
{

value = analogRead(4);                                    // reading the values returned from sensor                                                             
  left_sensor = map(value, 4, 437, 0, 255);                 //     mapping it into a desirable range 
  value = analogRead(2);
  right_sensor = map(value, 4, 429, 0, 255);
  value = analogRead(3);
  cent_sensor = map(value, 4, 429, 0, 255);

  
if(left_sensor<100 && (right_sensor>100 && cent_sensor > 100))
//if(left_sensor<100 && right_sensor<100 || cent_sensor < 100)
      
      left();
 
      else if((left_sensor>100 && cent_sensor > 100) && right_sensor<100)
      right();


      else if (cent_sensor < 100 && (left_sensor>100 && right_sensor>100))
      forward();

      else if (left_sensor>100 && (right_sensor<100 && cent_sensor < 100))
          rightCent();
          
      else if (left_sensor<100 && (right_sensor>100 && cent_sensor < 100))
      leftCent();
      
      else
      {forward();}
      
      
      delay(20);

}
}





// function for moving both motors forward


void forward(){

    Serial.println ("FORWARD_______________ ");
  
  motor.setSpeed(150);     // set the speed to 200/255
  motorLeft.setSpeed (150);

  motor.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);
}



// function for moving left motor forward and right motor backwards for turning the robot to right side

void right(){
    Serial.println ("RIGHT_______________ ");
motor.setSpeed(90);     // set the speed to 200/255
  motorLeft.setSpeed (150);

  motor.run(BACKWARD);      // turn it on going forward
  motorLeft.run(FORWARD);
  
        delay(1000);
}


// function for moving right motor forward and left motor backwards for turning the robot to left side

void left(){

    Serial.println ("LEFT_______________ ");
motor.setSpeed(150);     // set the speed to 200/255
  motorLeft.setSpeed (90);

  motor.run(FORWARD);      // turn it on going forward
  motorLeft.run(BACKWARD);
  
        delay(1000);
}

void shutDown ()
{
motor.run (RELEASE);
motorLeft.run (RELEASE);
delay (20);
}


void leftCent ()
{

Serial.println ("LEFTCENT_______________ ");

motor.setSpeed(150);     // set the speed to 200/255
motorLeft.setSpeed (20);

  motor.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);
  
        delay(20);
  
}

void rightCent ()
{

Serial.println ("RIGHT__CENT_________________");
  
motor.setSpeed(20);     // set the speed to 200/255
motorLeft.setSpeed (150);

  motor.run(FORWARD);      // turn it on going forward
  motorLeft.run(FORWARD);
  
        delay(20);
  
}


