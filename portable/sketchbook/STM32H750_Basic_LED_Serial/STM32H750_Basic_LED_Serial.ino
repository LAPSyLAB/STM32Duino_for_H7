      int i;
      //                      RX    TX
      HardwareSerial Serial3(PB_11, PB_10);
      void setup() {
        // put your setup code here, to run once:
        // initialize digital pins PI13,PJ2 as outputs.
        pinMode(PI_13, OUTPUT);
        pinMode(PJ_2, OUTPUT);
        Serial3.begin(115200); 
      
      }
      void loop() {
        // put your main code here, to run repeatedly:
        digitalWrite(PI_13, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(PJ_2, LOW);    // turn the LED off by making the voltage LOW
      
        delay(1000);              // wait for a second
        
        i++;
        digitalWrite(PI_13, LOW);    // turn the LED off by making the voltage LOW
        digitalWrite(PJ_2, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);              // wait for a second
      
        Serial3.print("Hello World: ");
        Serial3.println(i);
      }
