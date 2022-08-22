/*
 * vehicle_control.c
 *
 *  	Created on: Aug 19, 2022
 *      Author: Mohamed Karam Fouad
 *
 */
# include<stdio.h>

# define WITH_ENGINE_TEMP_CONTROLLER 1

void Display_state();
void Engine_temperature( int engine_temperature );
void room_temperature( int temperature );
void vehicle_speed(char traffic_light);
void Sensors_set_menu();
char System_Menu();

typedef enum{ ON, OFF}  switchstate;

typedef struct{
	switchstate state;
	#if (WITH_ENGINE_TEMP_CONTROLLER)
	switchstate TEMP_CONTROLLER;
	int temp;
	#endif
}vehicle_state;
typedef struct {
	switchstate state;
	int temp;
}engine_ac;

engine_ac ac={OFF,20} ;					// Global variable
vehicle_state engine={OFF,OFF,125};     // Global variable
int speed =0;							// Global variable
void Display_state(){
	printf("Engine: ");
	if (engine.state == ON){
		printf("ON\n");
	}else printf("OFF\n");
	printf("AC: ");
	if (ac.state == ON){
		printf("ON\n");
	}else printf("OFF\n");
	printf("Vehicle Speed: %d\n", speed);
	printf("Room Temperature: %d\n", ac.temp);
	#if(WITH_ENGINE_TEMP_CONTROLLER)
	printf("Engine Temperature Controller State: ");
	if (engine.TEMP_CONTROLLER == ON){
		printf("ON\n");
	}else printf("OFF\n");
	printf("Engine Temperature: %d\n", engine.temp);
	#endif
	printf("\n");
}
#if (WITH_ENGINE_TEMP_CONTROLLER)
void Engine_temperature( int engine_temperature ){
	if (engine_temperature<100){
		engine.TEMP_CONTROLLER=ON;
		engine.temp=125;
	}else if (engine_temperature>150){
		engine.TEMP_CONTROLLER=ON;
		engine.temp=125;
	}else {
		engine.TEMP_CONTROLLER=OFF;
	}
	Display_state();
}
#endif

void room_temperature( int temperature ){
	if (temperature < 10){
		ac.state=ON;
		ac.temp=20;
	}else if (temperature > 30){
		ac.state=ON;
		ac.temp=20;
	}else{
		ac.state=OFF;
	}
	Display_state();
}
void vehicle_speed(char traffic_light){
	if (traffic_light=='G'){
		speed =100;
	}else if(traffic_light=='O'){
		speed =30;
		ac.state=ON;
		ac.temp= ac.temp*((float)5/4) + 1;
	#if (WITH_ENGINE_TEMP_CONTROLLER)
		engine.TEMP_CONTROLLER=ON;
		engine.temp=engine.temp*((float)5/4) + 1;
	#endif
	}else if (traffic_light=='R'){
		speed =0;
	}
	Display_state();
}
char System_Menu(){
	char input;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf(" %c",&input);
	if(input=='a'){
		engine.state=ON;
	}
	else if(input=='b'){
		engine.state=OFF;
	}
	else if(input=='c'){
		return 1 ;
	}
	return 0;
}
void Sensors_set_menu(){  //  menu that simulates the vehicle sensors readings.
	char input;
	char traffic_light;
	int temperature;
	int engine_temperature;
	printf("a. Turn off engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	#if(WITH_ENGINE_TEMP_CONTROLLER)
	printf("d .Set the engine temperature\n");
	#endif
	scanf(" %c",&input);
	if(input=='a'){
		engine.state=OFF;
	}
	else if(input=='b'){
		printf("c. Set the traffic light between (G , O, R )\n");
		scanf(" %c",&traffic_light);
		vehicle_speed(traffic_light);
	}
	else if(input=='c'){
		printf("c. Set the room temperature\n");
		scanf("%d",&temperature);
		room_temperature(temperature);
	}
	#if (WITH_ENGINE_TEMP_CONTROLLER)
	else if(input=='d'){
		printf("d .Set the engine temperature\n");
		scanf("%d",&engine_temperature);
		Engine_temperature( engine_temperature );
	}
	#endif
}
int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    while(1){							  // we used while(1) to make sure that menu is always displayed and waits for answer
    	if(engine.state==OFF){
    		if (System_Menu())break;      // here if the the condition (return equals 1) is true , then quit the program
    	}else if(engine.state==ON){
    		Sensors_set_menu();  //If chose to “Turn on the vehicle engine”, display “Sensors set menu”
    	}
    }
}

