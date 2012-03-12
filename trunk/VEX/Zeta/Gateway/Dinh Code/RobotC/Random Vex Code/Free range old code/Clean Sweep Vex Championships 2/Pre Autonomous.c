int automode = 100;
int fieldside;

void pre_auton()
{
  //Turn backlight on
  bLCDBacklight = true;
  //Lift back of basket
  SensorValue[Basket] = 1;
  //Reset encoders
  resetencoders();

  //Select starting side of field
  ClearTimer(T1);
  displayLCDCenteredString(0, "Side of Field:");
  displayLCDCenteredString(1, "Left Centr Right");
  int buttons = 100;
    while (time1[T1] < 5000 && automode > 10)
  {
    buttons = nLCDButtons;
    switch (buttons)
    {
    case 1:
      fieldside = left;
      automode = 8;
      displayLCDCenteredString(0, "Left");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;

    case 2:
      fieldside = centre;
      automode = 3;
      displayLCDCenteredString(0, "Centre");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;

    case 4:
      fieldside = right;
      automode = 8;
      displayLCDCenteredString(0, "Right");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;
    }
  }

  //Select programme
  ClearTimer(T1);
  displayLCDCenteredString(0, "Autonomous:");
  displayLCDCenteredString(1, "None Auto1 Auto2");
  while (time1[T1] < 3000 && automode > 5)
  {
    buttons = nLCDButtons;
    switch (buttons)
    {
    case 1:
      automode = 0;
      displayLCDCenteredString(0, "None");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;

    case 2:
      automode = 1;
      displayLCDCenteredString(0, "Auto 1");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;

    case 4:
      automode = 2;
      displayLCDCenteredString(0, "Auto 2");
      displayLCDCenteredString(1, "Selected");
      wait1Msec(1000);
      break;
    }
  }
}
