 int duty = 0;

      int i;
      HardwareSerial Serial3(PB_11, PB_10);


      
void setup() {
        // put your setup code here, to run once:
        // initialize digital pins PI13,PJ2 as outputs.
        pinMode(PA_3, OUTPUT);

        pinMode(PD_12, OUTPUT);
        pinMode(PD_13, OUTPUT);

        Serial3.begin(115200); 

        analogWriteFrequency(1000); // Set PMW period to ms
        
        analogWrite(PA_3, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
        analogWrite(PD_12, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
        analogWrite(PD_13, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle

     
}

void loop() {
      
          
          duty = duty + 25;

          if (duty > 255) {
               duty = 0;
          } 

          analogWrite(PA_3, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_12, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_13, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle

          Serial3.print("   PWM Duty:");
          Serial3.print(100*duty/255);
          Serial3.println("%");
          
          delay(1000);

        
}
