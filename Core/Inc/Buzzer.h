/*
 * Buzzer.h
 *
 *  Created on: Jan 29, 2023
 *      Author: mo_n1
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_
#include "main.h"


typedef struct
{
    uint16_t frequency;
    uint16_t duration;
} Tone;

//#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

TIM_HandleTypeDef *pwm_timer ;	// Point to PWM Timer configured in CubeMX
uint32_t pwm_channel ;   // Select configured PWM channel number
const Tone *volatile melody_ptr;
volatile uint16_t melody_tone_count;
volatile uint16_t current_tone_number;
volatile uint32_t current_tone_end;
volatile uint16_t volume;
int repeatOn;;          // (0 - 1000)
//Tone super_mario_bros [] ;
void PWM_Start();
void PWM_Change_Tone(uint16_t pwm_freq, uint16_t volume) ;
void Change_Melody(const Tone *melody, uint16_t tone_count);
void Update_Melody();
void Start_Melody();
void Pause_Melody();
void Hit_Sound(int a);
void Boss_melody();
#endif /* INC_BUZZER_H_ */
