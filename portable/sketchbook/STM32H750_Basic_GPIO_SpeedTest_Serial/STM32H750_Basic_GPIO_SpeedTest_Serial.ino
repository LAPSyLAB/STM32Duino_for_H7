// #include "stm32h750.h"

int i,ms,RegisterCMs,RegisterASMMs,WriteFastMs,WriteMs;
int j = 1;

//                      RX    TX
HardwareSerial Serial3(PB_11, PB_10);


      
void setup() {
        // put your setup code here, to run once:
        pinMode(PD_12, OUTPUT);
        pinMode(PD_13, OUTPUT);

        pinMode(PI_13, OUTPUT);
        pinMode(PJ_2, OUTPUT);

        Serial3.begin(115200); 
}

      
void loop() {
        // put your main code here, to run repeatedly:

        Serial3.print("--------- New series of tests : ");
        Serial3.println(j);


        // 1. test - I/O access through Arduino library API
        i=0;
        Serial3.print("digitalWrite [ms]:");
        ms=millis();
        while (i<1000000) {
          // statement(s)
                digitalWrite(PD_12, HIGH);   
                digitalWrite(PD_13, LOW);    
                digitalWrite(PI_13, HIGH);   
                digitalWrite(PJ_2, LOW);    
                
                digitalWrite(PD_12, LOW);   
                digitalWrite(PD_13, HIGH);  
                digitalWrite(PI_13, LOW);   
                digitalWrite(PJ_2, HIGH);  
                i++;  
        }
        WriteMs = millis()-ms;
        Serial3.println(WriteMs);

        digitalWriteFast(PI_13, HIGH);   
        digitalWriteFast(PJ_2, HIGH);    
        delay (500);

        // 2. test  - I/O access through faster library API
        i=0;
        Serial3.print("digitalWriteFast [ms]:");
        ms=millis();
        while (i<1000000) {
          // statement(s)
                digitalWriteFast(PD_12, HIGH);   
                digitalWriteFast(PD_13, LOW);    
                digitalWriteFast(PI_13, HIGH);   
                digitalWriteFast(PJ_2, LOW);    
                
                digitalWriteFast(PD_12, LOW);   
                digitalWriteFast(PD_13, HIGH);  
                digitalWriteFast(PI_13, LOW);   
                digitalWriteFast(PJ_2, HIGH);  
                i++;  
        }
        WriteFastMs = millis()-ms;
        Serial3.println(WriteFastMs);

        digitalWriteFast(PI_13, HIGH);   
        digitalWriteFast(PJ_2, HIGH);    
        delay (500);

        // 3. test - Baremetal I/O register access on high level code
        i=0;
        Serial3.print("Registers-C [ms]:");
        ms=millis();
        while (i<1000000) {
          // statement(s)
                //digitalWriteFast(PD_12, HIGH);  
                //digitalWriteFast(PD_13, LOW);    
                //Set D12 (HIGH)
                GPIOD->BSRR = 0b0001000000000000 << 16; //move to upper 16 bits
                //Set D13 (LOW)
                GPIOD->BSRR = 0b0010000000000000 ; 
                //Set I13 (HIGH)
                GPIOI->BSRR = 0b0010000000000000 << 16; //move to upper 16 bits
                //Set J2 (LOW)
                GPIOJ->BSRR = 0b0000000000000100 ; 
 
                
                //digitalWriteFast(PD_12, LOW);   
                //digitalWriteFast(PD_13, HIGH);  
                //Set D12 (LOW)
                GPIOD->BSRR = 0b0001000000000000; //move to upper 16 bits
                //Set D13 (HIGH)
                GPIOD->BSRR = 0b0010000000000000  << 16; 
                //Set I13 (LOW)
                GPIOI->BSRR = 0b0010000000000000 ; 
                //Set J2 (LOW)
                GPIOJ->BSRR = 0b0000000000000100 << 16; //move to upper 16 bits
                i++;  
        }
        RegisterCMs = millis()-ms;
        Serial3.println(RegisterCMs);

        digitalWriteFast(PI_13, HIGH);   
        digitalWriteFast(PJ_2, HIGH);    
        delay (500);

        // 4. test - Baremetal I/O register access on assembly level
        i=0;
        Serial3.print("Registers-ASM [ms]:");
        ms=millis();
        while (i<1000000) {
               asm (

                      "  ldr.w r0, = 0x58020C18                \n" // GPIOD->BSRR =   (0x58020C00 + 0x18 ) SetReset Register
                      
                      "  ldr r3,   = 0b0001000000000000 << 16  \n" // Bit 12
                      "  str r3, [r0]                           \n" // Set port high
                      "  ldr r3,   = 0b0010000000000000        \n" // Bit 13
                      "  str r3, [r0]                           \n" // Set port low

                      "  ldr.w r0, = 0x58022018                \n" // GPIOI->BSRR =   (0x58022000 + 0x18 ) SetReset Register
                      "  ldr r3,   = 0b0010000000000000 << 16  \n" // Bit 13
                      "  str r3, [r0]                           \n" // Set port high
                      "  ldr.w r0, = 0x58022418                \n" // GPIOJ->BSRR =   (0x58022400 + 0x18 ) SetReset Register
                      "  ldr r3,   = 0b0000000000000100        \n" // Bit 2
                      "  str r3, [r0]                           \n" // Set port low



                      "  ldr r3,   = 0b0001000000000000        \n" // Bit 12
                      "  str r3, [r0]                           \n" // Set port low
                      "  ldr r3,   = 0b0010000000000000 << 16  \n" // Bit 13
                      "  str r3, [r0]                           \n" // Set port high

                      "  ldr.w r0, = 0x58022018                \n" // GPIOI->BSRR =   (0x58022000 + 0x18 ) SetReset Register
                      "  ldr r3,   = 0b0010000000000000         \n" // Bit 13
                      "  str r3, [r0]                           \n" // Set port low
                      "  ldr.w r0, = 0x58022418                \n" // GPIOJ->BSRR =   (0x58022400 + 0x18 ) SetReset Register
                      "  ldr r3,   = 0b0000000000000100 << 16  \n" // Bit 2
                      "  str r3, [r0]                           \n" // Set port high

               : : : "r0", "r3");
// asm(“code” : output operand list : input operand list : clobber list);

               i++;  
        }
        RegisterASMMs = millis()-ms;
        Serial3.println(RegisterASMMs);


//      Increment variable j in inline assembler 
        asm (
                      "add %0,%1,#1 \n" 
                      : "=r" (j) : "r" (j) : 
        );

        digitalWriteFast(PI_13, HIGH);   
        digitalWriteFast(PJ_2, HIGH);    
        delay (2000);

}



 

 
