#include "main.h"
#include <cstdint>
#include <cstdio>
#include <stdint.h>
#include "pros/rtos.hpp"
#include "v5gdb.h"

[[gnu::noinline]]
int fib(uint64_t n) {
	__asm__ __volatile__("" ::: "memory");

	uint64_t a = 0;
	uint64_t b = 1;

	for (uint64_t i = 0; i < n; i++) {
		uint64_t tmp = a + b;
		a = b;
		b = tmp;
	}

	return a;
}

v5gdb::StdioTransport transport;
void initialize() {
	printf("Installing v5gdb\n");

	pros::delay(100);
	v5gdb::install(transport);

	pros::delay(100);

	printf("Done\n");

	v5gdb::breakpoint();

	pros::delay(100);
	printf("Okay, starting loop\n");

	while (true) {
		v5gdb::breakpoint();

		int number = fib(3);
		printf("Number: %d!\n", number);
		pros::delay(1000);
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// pros::Controller master(pros::E_CONTROLLER_MASTER);
	// pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	// pros::MotorGroup right_mg({-4, 5, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


	// while (true) {
	// 	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

	// 	// Arcade control scheme
	// 	int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
	// 	int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
	// 	left_mg.move(dir - turn);                      // Sets left motor voltage
	// 	right_mg.move(dir + turn);                     // Sets right motor voltage
	// 	pros::delay(20);                               // Run for 20 ms then update
	// }
}
