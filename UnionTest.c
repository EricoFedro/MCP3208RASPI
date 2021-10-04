#include <stdio.h>

struct SENSOR{
  union{
    int R;
    struct{
      unsigned sensor1:1;
      unsigned sensor2:1;
      unsigned sensor3:1;
      unsigned sensor4:1;
      unsigned sensor5:1;
    } B;
  } sen;
};

struct SENSOR testSensor;

int main(void)
{
  printf("Hello, World!\n");
  
  testSensor.sen.B.sensor1 = 1;
  testSensor.sen.B.sensor2 = 1;
  testSensor.sen.B.sensor3 = 1;
  testSensor.sen.B.sensor4 = 1;
  testSensor.sen.B.sensor5 = 1;
  
  printf("%d \n", sizeof(testSensor));
  printf("%d \n", 0b11);
  printf("%d \n:, testSensor.sen.R);
         
  return 0;
 }         
