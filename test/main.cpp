#include <mbed.h>

DigitalOut LEDPIN(PC_13);
int main() {

  // put your setup code here, to run once:

  while(1) {
    // put your main code here, to run repeatedly:
    LEDPIN != LEDPIN;
    wait(2);
  }
}