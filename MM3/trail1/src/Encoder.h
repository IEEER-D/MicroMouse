/* *
 * Created: 3/20/2020 10:42:39 PM
 *  Author: R&D IEEE-HTI
 */

void INT_init(void);
float Calculte_Distance(uint16_t Slots);
int Distance_to_slots(float distance);

volatile uint16_t Left_Counter;  // volatile: Because we gonna use it in another functions but the main.
volatile uint16_t Right_Counter; // so we don't need the optimizer to delete it so we make it volatile.

