#include "Interface.h"
#include "Measurement.h"
#include "Communication.h"


// Method to handle operation
void operation(){
  pressure_used = getPressureUsed();
  lcdPrint("Pressure meter", "Used: " + String(pressure_used) + " psi");
}
