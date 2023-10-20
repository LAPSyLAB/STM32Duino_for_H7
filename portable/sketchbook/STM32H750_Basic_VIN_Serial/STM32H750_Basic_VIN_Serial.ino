// Circuit : Breadboard with PA3(LED), PA4(ADC), PH10(Key), PD12,13 (PWM outputs), PI13:PJ2 LED (buildin)
      
      int i;
      int key;
      int adcvalue;
      //                      RX    TX
      HardwareSerial Serial3(PB_11, PB_10);
      void setup() {
        // put your setup code here, to run once:
        // initialize pins 
        pinMode(PA_3, OUTPUT);
        pinMode(PH_10, INPUT);
        pinMode(PA_4, INPUT);

        pinMode(PD_12, OUTPUT);
        pinMode(PD_13, OUTPUT);

        
        pinMode(PI_13, OUTPUT);
        pinMode(PJ_2, OUTPUT);
        
        Serial3.begin(115200); 

     
      }
      void loop() {

        
        // put your main code here, to run repeatedly:
        digitalWrite(PI_13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(PJ_2, LOW);    // turn the LED off by making the voltage LOW
        
        //digitalWrite(PA_3, LOW);    // turn the LED off by making the voltage LOW
        analogWriteFrequency(500); // Set PMW period to Note Hz

        analogWrite(PA_3, 250); // PWM output for PA0, shines more
       
        analogWrite(PD_12, 250); // PWM output 
        analogWrite(PD_13, 250); // PWM output 

      
        delay(1000);              // wait for a second
        
        i++;
        digitalWrite(PI_13, LOW);    // turn the LED on by making the voltage LOW
        digitalWrite(PJ_2, HIGH);   // turn the LED off (HIGH is the voltage level)

        // digitalWrite(PA_3, HIGH);   // turn the LED off (HIGH is the voltage level)
        analogWriteFrequency(2000); // Set PMW period to Note Hz
        analogWrite(PA_3, 50); // PWM output for PA0, shines less

        analogWrite(PD_12, 50); // PWM output
        analogWrite(PD_13, 50); // PWM output

        delay(1000);              // wait for a second


        key = digitalRead(PH_10); // Read Key state
        adcvalue = analogRead(PA_4); // Read analog input
        
        Serial3.print("Hello World[");
        Serial3.print(i);
        Serial3.print("]: Key:");
        Serial3.print(key);
        Serial3.print(" , ADC:");
        Serial3.println(adcvalue);
        
      }
