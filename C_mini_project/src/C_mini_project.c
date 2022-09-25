/*
 ============================================================================
 Name        : C_mini_project.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define WITH_ENGINE_TEMP_CONTROLLER  1

#define on 1
#define off 0

/*structure for vehicle state menu*/

struct vehicle_state {
	char engine_state;
	char AC;
	int Vehicle_Speed;
	int Room_Temperature;
	char Engine_Temperature_Controller_State;
	int Engine_Temperature;

} state, *state_ptr;

/*function prototypes*/
void start_window(void);
void Sensors_set_menu(void);
void light_color(void);
void Temperature_Sensor(void);
void engine_temp(void);
void current_vehicle_state(void);

int main(void) {

	state_ptr = &state;
	start_window(); /*calling a start_window function*/

	return 0;
}

void start_window(void) {
	char input;
	printf("a. Turn on the vehicle engine \n"
			"b. Turn off the vehicle engine\n"
			"c. Quit the system ");
	scanf(" %c", &input); /*take the input from the user*/

	switch (input) { /*check the input */
	case 'a':
		state_ptr->engine_state = on; /*set member engine state on*/
		Sensors_set_menu(); /*calling Sensors_set_menu fun to take the user to another menu*/
		break;

	case 'b':
		state_ptr->engine_state = off; /*set member engine state off*/

		start_window(); /*calling start_window fun*/
		break;
	case 'c':
		printf("Quit the system");
		break;
		exit(0); /*STOP the program*/
	default: {
		printf("ERROR\n");
		start_window(); /*calling the same fun again*/
	}
	}

}

void Sensors_set_menu(void) {
	char input;
	printf("a. Turn off the engine \n"
			"b. Set the traffic light color. \n"
			"c. Set the room temperature (Temperature Sensor) \n");

#if  WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("d. Set the engine temperature (Engine Temperature Sensor)");
#endif

	scanf(" %c", &input);

	switch (input) { /*check the input*/
	case 'a':
		state_ptr->engine_state = off; /*set the engine state off*/
		start_window(); /*call the start_window fun*/
		break;

	case 'b':
		light_color(); /*call the light_color fun to take the user to another menu*/

		break;
	case 'c':
		Temperature_Sensor(); /*call the Temperature_Sensor fun to take the user to another menu*/

		break;
	case 'd':
		engine_temp(); /*call the engine_temp fun to take the user to another menu*/
		break;
	default: {
		printf("ERROR");
		Sensors_set_menu();/*calling the same fun again*/
	}
	}

}

void light_color(void) {
	char input;
	printf("Enter the required color ");
	scanf(" %c", &input);

	switch (input) { /*check the input*/
	case 'g':
		state_ptr->Vehicle_Speed = 100; /*set the cehicle_speed member in the struct = 100*/
		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/
		break;

	case 'o':
		/*
		 If vehicle speed is 30 km/hr
		 i. Turn ON AC if it was OFF and set room temperature to:current
		 temperature * (5/4) + 1
		 ii. Turn ON “Engine Temperature Controller” if it was OFF and set engine
		 temperature to: current temperature * (5/4) + 1
		 */

		state_ptr->Vehicle_Speed = 30;
		state_ptr->AC = on;
		state_ptr->Room_Temperature *= (5 / 4) + 1;
		state_ptr->Engine_Temperature_Controller_State = on;
		state_ptr->Engine_Temperature *= (5 / 4) + 1;
		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/

		Sensors_set_menu(); /*calling sensors_set_menu fun*/
		break;

	case 'r':
		state_ptr->Vehicle_Speed = 0; /*set vehicle_speed member = 0*/
		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/
		break;

	default: {
		printf("ERROR");
		light_color(); /*call the same fun again*/
	}
	}

}
void Temperature_Sensor(void) {
	int input;
	printf("Enter the required room temp ");
	scanf(" %d", &input);

	if (input < 10) {
		state_ptr->AC = on; /*set the AC member on*/
		state_ptr->Room_Temperature = 20; /*set the Room_Temperature member = 20*/

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/

	} else if (input > 30) {
		state_ptr->AC = on; /*set the AC member on*/
		state_ptr->Room_Temperature = 20; /*set the Room_Temperature member = 20*/

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/

	} else {
		state_ptr->AC = off; /*set the AC member off*/

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/
	}
}

void engine_temp(void) {
	int input;
	printf("Enter the required engine temp ");
	scanf(" %d", &input);

	if (input < 100) {

		/*Engine Temperature Controller” ON and set temperature to 125*/
		state_ptr->Engine_Temperature_Controller_State = on;
		state_ptr->Engine_Temperature = 125;

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/

	} else if (input > 150) {

		/*Engine Temperature Controller” ON and set temperature to 125*/
		state_ptr->Engine_Temperature_Controller_State = on;
		state_ptr->Engine_Temperature = 125;

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/

	} else {
		/*set the Engine_Temperature_Controller_State=off member off*/
		state_ptr->Engine_Temperature_Controller_State = off;

		current_vehicle_state(); /*calling the current_vehicle_state fun that print state of the vehicle*/
		Sensors_set_menu(); /*calling sensors_set_menu fun*/
	}
}

void current_vehicle_state(void) {
	switch (state_ptr->engine_state) { /*check engine_state*/

	case on:
		printf("Engine state: ON\n");
		break;

	case off:
		printf("Engine state: OFF\n");
		break;
	}

	switch (state_ptr->AC) { /*check the AC state*/

	case on:
		printf("AC: ON\n");
		break;

	case off:
		printf("AC: OFF\n");
		break;
	}

	printf("Vehicle Speed: %d Km/Hr\n", state_ptr->Vehicle_Speed);

	printf("Room Temperature: %d C\n", state_ptr->Room_Temperature);

#if  WITH_ENGINE_TEMP_CONTROLLER == 1
	switch (state_ptr->Engine_Temperature_Controller_State) {

	case on:
		printf("Engine Temperature Controller State: ON\n");
		break;

	case off:
		printf("Engine Temperature Controller State: OFF\n");
		break;
	}

	printf("Engine Temperature: %d C\n", state_ptr->Engine_Temperature);
#endif
}

