#include "vex.h"

using namespace vex;

const int kP = 6;
const int kD = 8;
const int kI = 20;
const float MIN_VELOCITY = 1;

void Reset() {
  L.resetRotation();
  R.resetRotation();
}

double Constrain(double inputValue, double max, double min) {
  if (inputValue >= max) {
    return max;
  }
  if (inputValue <= min) {
    return min;
  }
  return inputValue;
}

void Move(float leftSetPoint, float rightSetPoint, float maxVelocity) {
  //Reset the motors rotation value
  Reset();

  // Initialize the previous velocities of the motors to later measure change in velocity
  float previousLeft = maxVelocity;
  float previousRight = maxVelocity;

  // Initialize the change in velocity of each side to prevent overshooting.
  float leftChange = 0;
  float rightChange = 0;
  
  // Prevent steady state error by adding in the total accumulated error
  float totalRight = 0;
  float totalLeft = 0;
    
  while(1) {
    //Assign the current rotations of each motor to separate variables
    float leftRotation = L.rotation(degrees);
    float rightRotation = R.rotation(degrees);
    
    //Calculate the difference between the desired destination and the current rotation
    float rightError = rightSetPoint - rightRotation;
    float leftError = leftSetPoint - leftRotation;
    
    //The error is now used as the velocity, as error decreases, velocity decreases
    //The accumulated error is added in to make sure the robot is not going too slow
    //The change in error is subtracted to make sure the robot is not going too fast
    float rightVelocity = rightError/kP + totalRight/kI - rightChange/kD;
    float leftVelocity = leftError/kP + totalLeft/kI - leftChange/kD;
    
    //Constrains the velocity of the motors to the specified maximum velocity
    rightVelocity = Constrain(rightVelocity, maxVelocity, -maxVelocity);
    leftVelocity = Constrain(leftVelocity, maxVelocity, -maxVelocity);
    
    //Calculate a new change in velocity
    leftChange = previousLeft - leftVelocity;
    rightChange = previousRight - rightVelocity;
    
    // Reset the previous velocity before going to the next loop
    previousLeft = leftVelocity;
    previousRight = rightVelocity;
    
    //Recalculate the total accumulated error
    totalLeft += leftError;
    totalRight += rightError;
    
    //Spin motors
    L.spin(forward, leftVelocity, percent);
    R.spin(forward, rightVelocity, percent);
    
    //Stop the robot if the velocity of each side is between min velocity and its depressed cousin
    if(leftVelocity <= MIN_VELOCITY && leftVelocity >= -MIN_VELOCITY && 
      rightVelocity <= MIN_VELOCITY && leftVelocity >= -MIN_VELOCITY ) {
      return;
    }else {
      task::sleep(10);
    }
  }
}