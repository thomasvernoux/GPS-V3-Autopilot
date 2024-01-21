
// Include the AccelStepper library:
#include <AccelStepper.h>

#include <QMC5883LCompass.h>  // Compas library

#include <stdio.h>


typedef struct {
    double alpha;
    double y_prev; // Variable statique pour stocker la sortie précédente
} LowPassFilter;


// Initialisation du filtre passe-bas
void initLowPassFilter(LowPassFilter* filter, double alpha) {
    filter->alpha = alpha;
    filter->y_prev = 0.0;
}


// Filtrage passe-bas
double lowPassFilter(LowPassFilter* filter, double x) {
    double y = filter->alpha * x + (1 - filter->alpha) * filter->y_prev;
    filter->y_prev = y;
    return y;
}




// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

QMC5883LCompass compass;
double rtp; // rudder_target_position;

LowPassFilter filter;





void setup() {

  // Compas 
  Serial.begin(9600);
  compass.init();
  compass.setCalibrationOffsets(716.00, 571.00, -345.00);
  compass.setCalibrationScales(1.08, 1.06, 0.89);

  // Motor
  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(20000);
  stepper.setAcceleration(10000);


  
  initLowPassFilter(&filter, 0.1); // Choisir une valeur appropriée pour alpha
}

void loop() {

  // Compas 
  int a;
  
  // Read compass values
  compass.read();

  // Return Azimuth reading
  a = compass.getAzimuth();
  
  //Serial.print("A: ");
  //Serial.print(a);
  //Serial.println();

  rtp = 10000 * (a + 180);
  Serial.print(rtp);
  Serial.print("   ");
  //double rtp2 = lowPassFilter(&filter, (double)rtp);
  Serial.println(rtp);

  stepper.moveTo(rtp);
  stepper.runToPosition();

  delay(1000);


  



}







