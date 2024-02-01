/*
 * Time.h
 *
 *  Created on: Jan 23, 2023
 *      Author: mo_n1
 */

#ifndef INC_TIMERTC_H_
#define INC_TIMERTC_H_
#include "main.h"
extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef mytime = { 0 };
RTC_DateTypeDef mydate = { 0 };

void initRtc(){
		mytime.Hours = 15;
		mytime.Minutes = 20;
		mytime.Seconds = 10;
		mytime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		mytime.StoreOperation = RTC_STOREOPERATION_RESET;
		mydate.WeekDay = RTC_WEEKDAY_MONDAY;
		mydate.Month = RTC_MONTH_DECEMBER;
		mydate.Date = 23;
		mydate.Year = 22;
		HAL_RTC_SetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
		HAL_RTC_SetDate(&hrtc, &mydate, RTC_FORMAT_BIN);
}
void updateTime(){

	HAL_RTC_GetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &mydate, RTC_FORMAT_BIN);
}
#endif /* INC_TIMERTC_H_ */
