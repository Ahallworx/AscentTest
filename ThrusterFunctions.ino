void setupThruster()
{
  //set up esc and send stop signal
  servo.attach(ESC_RC_PW); //attach ESC pin to servo
  servo.writeMicroseconds(STOP_SIGNAL); // send 'stop' signal
  delay(SETUP_DELAY); // delay to allow theESC to recognize stop signal
  //radio.println(F("Thruster setup"));
}

void checkThruster()
{
  if(!servo.attached())
  {
    radio.println(F("Unable to confirm ESC connection!"));
    missionReady = false;
    return;
  }
  radio.println(F("ESC connection confirmed."));  
}

void ascend()
{
  servo.writeMicroseconds(upSignal); //if we just rely on pos buoy to surface
  /*//or if we want to ascend with thruster help
  servo.writeMicroseconds(1250); could be any number between 1100 and 1500
  can do the math to optimize*/
}

void sendPIDSignal()
{
  int signalESC;
  // convert thrust to PWM signal
  signalESC = (T_GAIN*thrust)+ MIN_PWM;
  signalESC = round(signalESC);
  // account for outliers
  if(signalESC < MIN_PWM)
    signalESC = STOP_SIGNAL;
  if(signalESC > MAX_PWM)
    signalESC = MAX_PWM;
  servo.writeMicroseconds(signalESC);
}

