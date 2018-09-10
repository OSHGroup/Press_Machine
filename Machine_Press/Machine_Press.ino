/*************************************************************
   Machine Press Safety Gate

   Close safety gate in front of Press Machine so worker
   cannot put hands in dangerous spot.


   Circuit:

   Servo Motor connected to Pin 9
   Blue LED connected to Pin 13
   Red LED connected to PIN 7
   Green LED connected to PIN 8
   Piezo Buzzer connect to PIN 5


**************************************************************/

/********* Libraries to include *****************************/

/* Servo motor control library for gate mechanism */
#include <Servo.h>

/* Timer library to simulate inputs from machine press */
#include <MsTimer2.h>

/********* Constants for hardware pins *********************/
const byte SIM_PRESS_MACHINE_OUTPUT = 13; //Also add Blue LED here
const byte PRESS_MACHINE_INPUT = 12;
const byte SAFETY_GATE_SERVO = 9;
const byte PIEZO_BUZZER = 3;
const byte GATE_OPEN_LED = 7; //Green LED
const byte GATE_CLOSED_LED = 8; // Red LED

/********* Globals *****************************************/

/* Initialize Servo object*/
Servo Safety_Gate;


/********* Functions ***************************************/


/* Initialize Simulated Press OUTPUT */
void init_Sim_Press_Machine(void) {

  /* Set pinMode for output pin */
  pinMode(SIM_PRESS_MACHINE_OUTPUT, OUTPUT);

  /* Set interval of output */
  MsTimer2::set(10000, Sim_Press_Machine_Output);
  MsTimer2::start();

}

/* Initialize the Safety Gate and Indicator LEDs*/
void init_Safety_Gate_Hardware(void) {

  /* Set pins to appropriate modes */
  pinMode(PRESS_MACHINE_INPUT, INPUT_PULLUP);
  pinMode(GATE_OPEN_LED, OUTPUT);
  pinMode(GATE_CLOSED_LED, OUTPUT);

  /* Initialize Servo object*/
  Safety_Gate.attach(9);

}

/* ****************************************************
    Simulate output from the Press Machine by turning
    pin HIGH and LOW at set interval.
 ******************************************************/
void Sim_Press_Machine_Output(void) {

  static boolean output = HIGH; //static variables only get initialized once.

  digitalWrite(SIM_PRESS_MACHINE_OUTPUT, output);
  output = !output; //Toggle the state of the output

}

/* ****************************************************
    Open the safety gate, and turn ON the Green "Safe"
    LED, and turn OFF the Red "danger" LED
 ******************************************************/
void Safety_Gate_Open_Routine(void) {

  /* Open the safety gate */
  Safety_Gate.write(90);

  /* Turn Green LED Indicator ON */
  digitalWrite(GATE_OPEN_LED, HIGH);

  /* Turn Red LED Indicator OFF */
  digitalWrite(GATE_CLOSED_LED, LOW);

}


/* ****************************************************
    Close the safety gate, and turn OFF the Green "Safe"
    LED, and turn ON the Red "danger" LED
 ******************************************************/
void Safety_Gate_Close_Routine(void) {

  /* close the safety gate */
  Safety_Gate.write(0);

  /* Turn Green LED Indicator OFF */
  digitalWrite(GATE_OPEN_LED, LOW);

  /* Turn Red LED Indicator ON */
  digitalWrite(GATE_CLOSED_LED, HIGH);

}

/******************************************************
   SETUP FUNCTION -> ONLY RUNS ONCE
 ******************************************************/
void setup() {

  init_Sim_Press_Machine();  /* Initialize the Press Machine Output */

  init_Safety_Gate_Hardware();  /* Initialize the Safety Gate Hardware*/

  Serial.begin(9600);  /* Set up Serial Communication*/

}

/******************************************************
 * LOOP FUNCTION -> RUNS OVER AND OVER
 ******************************************************/
void loop() {

  /* Read the state of the machine press */
  boolean Machine_Press_State = digitalRead(PRESS_MACHINE_INPUT);

  /* Check if the state is LOW */
  if (Machine_Press_State == LOW ) {

    Safety_Gate_Open_Routine();

  }
  else {

    Safety_Gate_Close_Routine();

  }

}
