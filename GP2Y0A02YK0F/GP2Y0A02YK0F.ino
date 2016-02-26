/******** start code ********/
/*
 *  created   2013-07-26
 *  by    lisper (leyapin@gmail.com)
 *  function  test gp2y0a02yk, read value from A1
 *
 */

//connect gp2y0a02 to A1
#define pin A2

void setup () {
        Serial.begin (9600);
        pinMode (pin, INPUT);
}

void loop () {
        uint16_t value = analogRead (pin);
        uint16_t range = get_gp2y0a02 (value);
        Serial.println (value);
        Serial.print (range);
        Serial.println (" cm");
        Serial.println ();
        delay (500);
}

//return distance (cm)
uint16_t get_gp2y0a02 (uint16_t value) {
        if (value < 70)  value = 70;
        return 12777.3/value-1.1;        //(cm)
        //return (62.5/(value/1023.0*5)-1.1);        //(cm)
        //return ((67870.0 / (value - 3.0)) - 40.0); //gp2d12 (mm)
}

/******** end code ********/
