/*************************************************
 * Frequency (Hz) macros for sound output.
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

/* set I/O pins from schematic */
int switch_pin = 2; /* circuit switch */
int echo_pin = 4; /* SONAR signal input */
int trigger_pin = 5; /* PWM SONAR signal output */
int sound_pin = 8; /* pin that connects to speaker */

/* tolerance given to door's movement */
/* distance (cm) from computer to door */
float delta_d = 10;
float d_sub_not = -1; /* -1: unset */

/* 2D array of NOTE, DURATION data */
const int alarm[][2] =
{
    {NOTE_D7, 4},
    {NOTE_A6, 4},
    {NOTE_BLANK, 4}
};

/*
 * setup - Enables internal 100ohm pull-up resistor.
 * 
 * Returns: None
 */
void setup()
{
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP);
}
 
/*
 * emit_alarm - Emits a frequency for a duration of time (ms)
 * 
 * Returns: None
 */
void emit_alarm()
{
   int note, note_duration = 0;
   int qty_notes = sizeof(alarm) / sizeof(alarm[0])

   while (note < qty_notes)
   {
     beat = alarm[note][0];
     duration = alarm[note][1];

     /* convert duration to milliseconds */
     normalized_duration = 1000 / duration;
     pause = normalized_duration * 1.30;

     /* emit a sound */
     tone(sound_pin, beat, normalized_duration);
     delay(pause);
   }
}

/*
 * get_distance - Calcualtes the distance from SONAR sensor
 * to an object. See README for more technical specs.
 * 
 * Returns: Distance (cm) from SONAR sensor to object.
 */
float normalized_distance()
{
   float distance;
   int pulse;

   /* bit-bang the trigger pin to find depth of SONAR vision */
   digitalWrite(trigger_pin, LOW);
   delayMicroseconds(20);
   digitalWrite(trigger_pin, HIGH);
   delayMicroseconds(100);
   digitalWrite(trigger_pin, LOW);

   /* distance = pulse(cm) / speed of sound / 2 (periods) */
   pulse = pulseIn(echo_pin, HIGH);
   distance = pulse / 29.387 / 2;

   return distance;
 }

 
