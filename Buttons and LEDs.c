#include <msp430.h> 
#include <stdbool.h>




void Peripherals (){

    //BUTTON P4.1
    P4DIR &= ~BIT1; //sets P4.1 as input 0
    P4REN |= BIT1; //Enables P4.1 pull up resistor
    P4OUT |= BIT1; //sets bit 1 as high to configure pull-up

    //RED LED P1.0
    P1DIR |= BIT0; // sets P1.0 as an output
    P1OUT |= BIT0; // P1 output 0000 0001

    //GREEN LED P6.6
    P6DIR |= BIT6; //sets P6.6 as an output
    P6OUT |= BIT6; //P6 output 0100 0000
}

// Setting LEDs

//RED LED
void RedLED(bool led){
    if (led){
        P1OUT |= BIT0;
    }
    else {
        P1OUT &= ~BIT0;
    }
}

//GREEN LED
void GreenLED(bool led){
    if (led){
        P6OUT |= BIT6;
    }
    else {
        P6OUT &= ~BIT6;
    }
}

//BOTH LED
void BothLED(bool led){
    if (led){
        P1OUT |= BIT0;
        P6OUT |= BIT6;
    }
    else {
        P1OUT &= ~BIT0;
        P6OUT &= ~BIT6;
    }
}

//Button Pressed Function
bool buttonPressed(){
  if  ((P4IN & BIT1) == 0x00){
      return true;

  }else{
      return false;
  }

}


int main(void)
{
    Peripherals();
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;


int pos = 0;

while(1){
    if (buttonPressed()){
        __delay_cycles(100000);
        if(buttonPressed()){
            pos++;
            if(pos >=3){
                pos = 0;
                     }
       }
    }
    if (buttonPressed()){
        switch(pos){
        case 0:
                BothLED(false);
                RedLED(true);
                GreenLED(false);
                break;
        case 1:
                BothLED(false);
                RedLED(false);
                GreenLED(true);
                break;
        case 2:
                RedLED(true);
                GreenLED(true);
                BothLED(true);
                break;
        default:
                break;
    }
}
    }
}






