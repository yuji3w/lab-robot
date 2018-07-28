int speed = 50;

void setSpeed();
void displayOptions();
void executeOption();
void buttonUpFxn();
void buttonLeftFxn();
void buttonRightFxn();
void buttonDownFxn();
void setCustom();

task main()
{
	setSpeed();
	sleep(500);
	displayOptions();
	sleep(500);
	resetMotorEncoder(motorA);
	resetMotorEncoder(motorD);
	executeOption();
}

void setSpeed()
{
	eraseDisplay();
	displayString(0, "Up/down buttons vary speed.");//Might be line 0, might have to make 2 lines.
	displayString(1, "Enter button confirms.");//Might be line 1, might be 2 lines.
	while(!getButtonPress(buttonEnter))
	{
		displayTextLine(2, "%03d", speed);//might be line 3
		if(getButtonPress(buttonUp))
		{
			speed++;
		}
		else if(getButtonPress(buttonDown))
		{
			speed--;
		}
		sleep(100);
	}
}

void displayOptions()//Must exist equal newline to options
{
	eraseDisplay();
	displayString(0, "Press the desired direction.");
	displayString(2, "Press enter button to confirm.");
	displayString(1, "Only press enter for custom.");
}

void executeOption()
{
	int buttonValue = -1;
	while(!getButtonPress(buttonEnter))
	{
		if(getButtonPress(buttonUp))
		{
			buttonValue = buttonUp;
		}else if(getButtonPress(buttonLeft))
		{
			buttonValue = buttonLeft;
		}else if(getButtonPress(buttonRight))
		{
			buttonValue = buttonRight;
		}else if(getButtonPress(buttonDown))
		{
			buttonValue = buttonDown;
		}
	}
	switch(buttonValue)
	{
	case buttonUp:
		buttonUpFxn();
	case buttonLeft:
		buttonLeftFxn();
	case buttonRight:
		buttonRightFxn();
	case buttonDown:
		buttonDownFxn();
	case -1:
		setCustom();
	default:
		playSound(soundBeepBeep);
	}
}

void buttonUpFxn()
{
	setMotorSpeed(motorA,speed);
	while(abs(getMotorEncoder(motorA))<600)
	{
	}
	setMotorSpeed(motorA,0);
}

void buttonLeftFxn()
{
	setMotorSpeed(motorD,-speed);
	while(abs(getMotorEncoder(motorD))<450)
	{
	}
	setMotorSpeed(motorD,0);
}

void buttonRightFxn()
{
	setMotorSpeed(motorD,speed);
	while(abs(getMotorEncoder(motorD))<450)
	{
	}
	setMotorSpeed(motorD,0);
}

void buttonDownFxn()
{
	setMotorSpeed(motorA,-speed);
	while(abs(getMotorEncoder(motorA))<600)
	{
	}
	setMotorSpeed(motorA,speed);
}

void setCustom()
{
	setMotorBrakeMode(motorA, motorCoast);
	setMotorBrakeMode(motorD, motorCoast);
	eraseDisplay();
	sleep(1000);
	displayString(0, "Press enter at end position.");
	while(!getButtonPress(buttonEnter))
	{
	}
	resetMotorEncoder(motorA);
	resetMotorEncoder(motorD);
	sleep(1000);
	eraseDisplay();
	displayString(0, "Press enter at start position.");
	while(!getButtonPress(buttonEnter))
	{
	}
	float tempA = getMotorEncoder(motorA);
	float tempD = getMotorEncoder(motorD);
	float max = (tempA > tempD) ? tempA : tempD;
	tempA = tempA / max * speed;
	tempD = tempD / max * speed;
	setMotorSpeed(motorA, -tempA);
	setMotorSpeed(motorD, -tempD);
	while(abs(getMotorEncoder(motorA))>5 && abs(getMotorEncoder(motorD))>5)
	{
	}
}
