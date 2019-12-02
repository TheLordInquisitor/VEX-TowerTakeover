/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       imperium                                                  */
/*    Created:      Mon Nov 11 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         1               
// R1                   motor         2               
// Controller1          controller                    
// L2                   motor         3               
// R2                   motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor_group Left(L1, L2);
motor_group Right(R1, R2);


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(1) {
    float leftAxis = Controller1.Axis3.position(percent);
    Left.spin(forward, leftAxis, percent);
        
  }
  
}
