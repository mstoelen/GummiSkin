// 17/02/2016
// Analog input definition
int sensorPin[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11}; // select the input pin for the potentiometer
//
// Variables that contain the reference value of the 12 sensoors
int sensorValueSetupUpRif[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
//
// Variables that contain the actual value of the sensors
int sensorValueSetupUp[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//
// Variables that contain the historical value of the sensors (of the "maxloop" values)
unsigned long sensorValueStor[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//
// Counter of the loops. This value change form 1 to maxloop
int loopcounter = 0;
int maxloop = 100;
// Counter that says us hoa many usuful loop have been without touches
int goodcounter = 0;
// Variable that is setting to 1 when the system captures a touch
int wakeup = 0;
// variable useful to light the second led that indicates:
// light = maxloop loops
// do not light = maxloop loops
int LuceRossa =0;
boolean boolvar = false;
// output when we have a touch
int ledPin = 7;      // select the pin for the LED
// output when we have maxloop loops
int ledPin1 = 13;
// Sensor number
int sens_numb = 12;

int i = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor and set these as referce values
  for (i = 0; i < sens_numb; i = i + 1) {
    sensorValueSetupUpRif[i] = analogRead(sensorPin[i]) + 2;
    delay(10);
  }

  /*
    Serial.println("Punto 0");
    Serial.println("Riferimenti 0");
  for (i = 0; i < sens_numb; i = i + 1) {
    Serial.println (sensorValueSetupUpRif[i]);
  }
  */
  
  delay(500);
  // Inizialize the store variables
  for (i = 0; i < sens_numb; i = i + 1) {
    sensorValueStor[i] = 0;
  }
  loopcounter = 0;
  LuceRossa = 0;
  digitalWrite(ledPin1, LOW);
    
  while (1) {
    
    if ( wakeup == 0) {
      loopcounter = loopcounter + 1;
    }
    else {
      if ( loopcounter == maxloop ) {
        loopcounter = maxloop;
      }
      else {
        loopcounter = loopcounter + 1; 
      }
    }
    
    // This part is used to evaluete the loop time 
    if (loopcounter == maxloop ) {
      if (LuceRossa == 0) {
        digitalWrite(ledPin1, HIGH);
        LuceRossa = 1;
      }
      else {
        digitalWrite(ledPin1, LOW);
        LuceRossa = 0;
      }
    } 
    
    
    // Reade the analog inputs of the sensors
    for (i = 0; i < sens_numb; i = i + 1) {
      sensorValueSetupUp[i] = analogRead(sensorPin[i]);
    }
    
    /*
    Serial.println("Punto A; loopcounter");
    Serial.println(loopcounter);
    Serial.println("Riferimenti");
    for (i = 0; i < sens_numb; i = i + 1) {
      Serial.println (sensorValueSetupUpRif[i]);
    }
    
    Serial.println("letture");
    for (i = 0; i < sens_numb; i = i + 1) {
      Serial.println (sensorValueSetupUp[i]);
    }
    delay(10);   
    */
    
    
    if ( wakeup == 0 ) {  // There is not touch
    
      /*
      Serial.println("Punto 1: wakeup=0");
      */
      
      // Controll the sensors
      for (i = 0; i < sens_numb; i = i + 1) {
        if (sensorValueSetupUp[i] > sensorValueSetupUpRif[i])
        digitalWrite(ledPin, HIGH);
        wakeup = 1;
        // To define the zone of the sensor
      }     
      
      /*
      Serial.println("Punto 2: wakeup");
      Serial.println(wakeup);
      */
    
      if (loopcounter != maxloop) {  // When the number of loop is less than maxloop
        
        /*
        Serial.println("Punto 3: loopcounter");
        Serial.println(loopcounter);
        Serial.println("goodcounter");
        Serial.println(goodcounter);
        */
      
        if ( wakeup == 1 ){ //Control if there is still a touch
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = 0;
          }
          goodcounter = 0;
          
          /*
          Serial.println("Punto 3B: sensorValueStor[1] e [2]");
          Serial.println(sensorValueStor[1]);
          Serial.println(sensorValueStor[2]);
          Serial.println("loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
        
        }
        else { // If there is not touch
          goodcounter = goodcounter +1;
          
          /*
          Serial.println("Punto 31: loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
          
          // Update the reference values
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = sensorValueStor[i] + sensorValueSetupUp[i];
          }
        }
      }
      else {  // When the number of loop is equal to the maxloop
        if ( wakeup == 1 ){  // If there is still a touch
          
          /*
          Serial.println("Punto 4: wakeup");
          Serial.println(wakeup);
          Serial.println("loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = 0;
          }
          goodcounter = 0;
        }
        else { // If there is not a touch
          goodcounter = goodcounter + 1;
          
          /*
          Serial.println("Punto B: loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          Serial.println("sensorValueStor 1 e 2");
          Serial.println(sensorValueStor1);
          Serial.println(sensorValueStor2);
          */
        
          // delay(500);          
          
          // Update the reference values
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueSetupUpRif[i] = ((sensorValueStor[i] + sensorValueSetupUp[i])/goodcounter) + 2;
          }
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = 0;
          }
          goodcounter = 0;
          loopcounter = 0;
          digitalWrite(ledPin, LOW);
          
          /*
          Serial.println("Punto 10: Nuovi Riferimenti");
          for (i = 0; i < sens_numb; i = i + 1) {
            Serial.println (sensorValueSetupUpRif[i]);
          }     
          */
        }            
      }
    }
    else { // If there is a touch
      digitalWrite(ledPin, HIGH);
      
      /*
      Serial.println("Punto 5: wakeup");
      Serial.println(wakeup);
      Serial.println("loopcounter");
      Serial.println(loopcounter);
      Serial.println("goodcounter");
      Serial.println(goodcounter);
      */
      
      // Controll il touch is still active
      boolvar = false;
      for (i = 0; i < sens_numb; i = i + 1) {
        if ( sensorValueSetupUp[i] > sensorValueSetupUpRif[i] ) {
          boolvar = true;
        }
      }   
      
      /*
      Serial.println("Punto 5A: boolvar");
      Serial.println(boolvar);
      */
      
      if ( boolvar == false ) {  // If the touch is not still active
        wakeup = 0;
        digitalWrite(ledPin, LOW);
        if (loopcounter != maxloop) {  // Controll if the number of loop != maxloop
          goodcounter = goodcounter +1;
          
          /*
          Serial.println("Punto 6: loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
          
          // Update the reference values
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = sensorValueStor[i] + sensorValueSetupUp[i];
          }
        }
        else {   // Controll if the number of loop == maxloop
          goodcounter = goodcounter + 1;
          
          /*
          Serial.println("Punto 61: loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
          
          // Update the reference values
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueSetupUpRif[i] = ((sensorValueStor[i] + sensorValueSetupUp[i])/goodcounter) + 2;
          }
          for (i = 0; i < sens_numb; i = i + 1) {
            sensorValueStor[i] = 0;
          }        
          goodcounter = 0;
          loopcounter = 0;  
          
          /*
          Serial.println("Punto 11: Nuovi Riferimenti");
          for (i = 0; i < sens_numb; i = i + 1) {
            Serial.println (sensorValueSetupUpRif[i]);
          } 
          Serial.println("loopcounter");
          Serial.println(loopcounter);
          Serial.println("goodcounter");
          Serial.println(goodcounter);
          */
          
        }     
      }
      else {  // We have still a touch (wakeup = 1)
        for (i = 0; i < sens_numb; i = i + 1) {
          sensorValueStor[i] = 0;
        }
        goodcounter = 0;
      }
    }
    // delay(1);
  }
}

