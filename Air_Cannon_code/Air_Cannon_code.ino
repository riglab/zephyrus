
#include <math.h>
#define PI 3.141592653589793

const int num_samples = 512; // can't be changed. What does this do?

int sine_samples[num_samples]; // initialize int space
int ramp_samples[num_samples];
int count = 1;
int sample_rate = 1;

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  while(Serial == 0); // what does this do? Wait for Serial to boot
  for (int i = 0; i < num_samples; i++)
  {
    ramp_samples[i] = 0;
    sine_samples[i] = 2048 + 2048*(sin(2.0*PI*i/(1.0*num_samples))); // what does this do?
    Serial.println(sine_samples[i]);
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

  pinMode(A14, OUTPUT);
  analogWriteResolution(12);
}

void play_data(int value)
{
  analogWrite(A14, value);
  //Serial.println(value);
}

void loop()
{
  int i = 0;
  //int sample_rate = analogRead(A0)/4;
  for (i = 0; i < num_samples; i++)
  {
    play_data(sine_samples[i]);
    //play_data(ramp_samples[i]);
    //i = (i + 1)%num_samples;
    if (i < 1*num_samples/4)
    {
      delayMicroseconds(20*sample_rate);
    }
    else
    {
      if (i == 1*num_samples/4)
      {
        delay(15);
      }
      else
      {
        if (i < 3*num_samples/4)
        {
          delayMicroseconds(sample_rate);
        }
        else
        {
          if (i == 3*num_samples/4)
          {
            delay(50);
            Serial.print('*');
          }
          else
          {
            delayMicroseconds(10*sample_rate);      
          }
        }
      } 
    }    
  }
  //while(Serial.available() == 0);
  //Serial.read();
  Serial.println(sample_rate);
  Serial.println(count);
  count++;
  delay(2500); // what should this be?
}
