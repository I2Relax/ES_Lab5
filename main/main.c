#include <stdio.h>
// Libraries needed for FreeRTOS usage.
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Needed to configure various options for scheduling.
#include "FreeRTOSConfig.h"
#include "freertos/timers.h"
#include <unistd.h>
#include "esp_system.h"
#include "rom/gpio.h"
// Needed for GPIO function.
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

#define TimerHandle_t xTimer_1;
#define TimerHandle_t xTimer_2;
#define uint8_t counter_timer_1=0;
#define uint8_t counter_timer_2=0;
#define TickType_t xTimeNow;

//void callback_func(TimerHandle_t xTimer)
void callback_func() {
	xTimeNow = (xTaskGetTickCount() -1)/100;
	const uint8_t *timer_id = pvTimerGetTimerID(xTimer);
	if (timer_id == 111) {
		printf("ahihi --------- %d\r\n", xTimeNow);
		counter_timer_1++;
		if (counter_timer_1 == 10) {
			printf("============================================================\n");
			printf("After 10 times printing, the first timer has been stopped \r\n");
			printf("============================================================\n");
			printf("Exit program! \r\n");
			xTimeStop(xTimer,0);
		}
	}
	else if (timer_id ==222) {
		printf("----- ihaha ------ %d\r\n", xTimeNow);
		counter_timer_2++;
		if (counter_timer_2 == 5) {
			printf("============================================================\n");
			printf("After 5 times printing, the second timer has been stopped \r\n");
			printf("============================================================\n");
			printf("Exit program! \r\n");
			xTimeStop(xTimer,0);
		}
	}
}
void app_main(void)
{
    xTimer_1 = xTimerCreate("Timer 1", pdMS_TO_TICKS(2000), pdTRUE, (void*)111, callback_func);
    xTimer_2 = xTimerCreate("Timer 2", pdMS_TO_TICKS(3000), pdTRUE, (void*)222, callback_func);
    if (xTimer_1 != NULL && xTimer_2 != NULL) {
    	printf("============================================================\n");
		printf("Start counting timer \r\n");
		printf("============================================================\n");
		xTimeStart(xTimer_1,0);
		xTimeStart(xTimer_2,0);
    }
    else printf("One of any timer is not created successfully \r\n");
}
