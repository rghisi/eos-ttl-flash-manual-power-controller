# eos-ttl-flash-manual-power-controller
Software and Hardware to control the power of old Canon EOS TTL flash/speedlite.

##Rationale

Digital EOS cameras uses E-TTL/E-TTLII flash system which requires compatible E-TTL/E-TTLII flashes also known as speedlites in Canon world.

Film EOS cameras uses older TTL/A-TTL flash system with requires TTL/A-TTL compatible speedlites.

Newer E-TTL speedlites, with model ending in "EX", are backwards compatible - with a few exceptions - with A-TTL film cameras. Older A-TTL speedlites are only usable in digital EOS in manual power, with no automated TTL metering/exposure.

Few film-era speedlites does not have dedicated user interface to control flash power, as is the case of Canon Macrolite ML- 3, firing always in full power with non-TTL cameras and rendering the unit pratically useless in real situations without workarounds such as the use of ND filters on flash head as shown in ["Adapting a Canon ML3 Ringflash for Digital"](http://www.pmstudios.co.uk/tutorials/tutorial-pdf/Adapting-ML3-ringflash-for-digital.pdf).

This project aims to build a small and simple power controller for EOS TTL speedlites.

##The Concept

Canon A-TTL/E-TTL/E-TTLII speedlites have a hotshoe pin called "quench" that shutdowns the flash light before full flash duration is reached. This mechanism provides a way to control the amount of flash power iluminating the scene as shown in ["Adding manual power control to the Canon 200E"](http://rudys-rants.blogspot.com.br/2010/06/glass-garden-mosaics.html) (Rudy's Rants blog).

The general idea of this project is to control the quench time to generate the right amount of flash duration corresponding to a user selectable power.

Long story short, we need to detect the flash trigger signal (comming from the camera) and react (almost) instantly by controlling the quench pin as a real EOS film camera would do in TTL mode.

##Proof of Concept

A simple test using Arduino UNO was made as a proof of concept and after a few tweaks the following code arised:

    int newPotValue = 0;
    int potValue = 0;        // value read from the pot
    int flashDelayTime = 0;
    
    void setup() {
      Serial.begin(9600); 
      pinMode(2, INPUT_PULLUP);
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      attachInterrupt(0, flash, FALLING); //external push-down button to trig the flash
      digitalWrite(8, 1);
      digitalWrite(9, 1);
    }

    void loop() {
      //simple loop to calculate new delay time when pot value changes and to print it on serial
      newPotValue = analogRead(A0); // Analog input pin that the potentiometer is attached to
      if (newPotValue != potValue) {
        potValue = newPotValue;
        flashDelayTime = potValue * 10;
        Serial.println(flashDelayTime);
      }
      delay(100);                     
    }

    void flash() {
      noInterrupts();
      digitalWrite(9, 0); //quench pin start (active-low)
      digitalWrite(8, 0); //trigger pin start (active-low)
      delayMicroseconds(flashDelayTime); //flash duration delay
      digitalWrite(9, 1); //quench pin end
      digitalWrite(8, 1); //trigger pin end
      interrupts();
      Serial.println("Flash"); 
    }



##The Prototype
