
#include <Servo.h>
#include <math.h>
#define PI 3.141592653589793

const int num_samples = 512; // can't be changed. What does this do?

int sine_samples[num_samples]; // initialize int space
int ramp_samples[num_samples];
int count = 1;
int inByte = '0';


Servo v;
Servo h;

int pos = 45;  

void setup() {
  
  v.attach(A0); 
  h.attach(A1);
  pinMode(A14, OUTPUT); 

  Serial.begin(9600);
  while(Serial == 0); 
  for (int i = 0; i < num_samples; i++)
  {
    ramp_samples[i] = 0;
    sine_samples[i] = 2048 + 2048*(sin(2.0*PI*i/(1.0*num_samples))); // what does this do?
    //Serial.println(sine_samples[i]);
  }
  int j;
  for (j = 0; j < num_samples/2; j++)
  {
    ramp_samples[j] = j*8 + 2048;
  }
  for (; j < num_samples; j++)
  {
    ramp_samples[j] = j*8 - 2048;
  }


  analogWriteResolution(12);

  
}

void loop() {



  for (pos = 60; pos <= 70; pos += 1) {
    v.write(pos);    
    h.write(pos);  
    puff();        
    delay(25); 
  }
  for (pos = 60; pos >= 20; pos -= 1) {
    v.write(pos);
    h.write(pos);
    puff();
    delay(25); 
  }
}

void play_data(int value)
{
  analogWrite(A14, value);
  //Serial.println(value);
}


void puff() {

  int i = 0;
  int sample_rate = 100;

  
    for (i = 0; i < num_samples; i++)
  {
    play_data(sine_samples[i]);
    //play_data(ramp_samples[i]);
    //i = (i + 1)%num_samples;
    if (i < 1*num_samples/4)
    {
      delayMicroseconds(100); //20*sample_rate originally
    }
    else
    {
      if (i == 1*num_samples/4)
      {
        delay(35); //15 originally
      }
      else
      {
        if (i < 3*num_samples/4)
        {
          delayMicroseconds(4); //sample_rate originally. Now 1 or 4 or 7
        }
        else
        {
          if (i == 3*num_samples/4)
          {
            delay(75); //50 originally
            Serial.print('*');
          }
          else
          {
            delayMicroseconds(50); //10*sample_rate originally
          }
        }
      } 
    }    
  }
  
}

