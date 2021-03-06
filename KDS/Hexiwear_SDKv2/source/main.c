/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include <string.h>

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
/*#include "fsl_debug_console.h"*/
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "RGBR.h"
#include "RGBG.h"
#include "RGBB.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "RTT1.h"
#include "fsl_port.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

static void AppTask(void* param) {
  (void)param; /* avoid compiler warning */
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
    LED2_Neg();
    WAIT1_Waitms(500);
    LED3_Neg();
    WAIT1_Waitms(500);
    CLS1_SendStr((uint8_t*)"hello world!\r\n", CLS1_GetStdio()->stdOut);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

/*!
 * @brief Application entry point.
 */
int main(void) {
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  /* initialize components */
  LED1_Init();
  LED2_Init();
  LED3_Init();
  RGBR_Init();
  RGBG_Init();
  RGBB_Init();
  CLS1_Init();
  RTT1_Init();
  /* create RTOS task(s) */
  if (xTaskCreate(AppTask, "App", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error case only, stay here! */
  }

  for(;;) {
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();

    RGBR_On();
    WAIT1_Waitms(500);
    RGBR_Off();

    RGBG_On();
    WAIT1_Waitms(500);
    RGBG_Off();

    RGBB_On();
    WAIT1_Waitms(500);
    RGBB_Off();
    WAIT1_Waitms(500);
  }

  vTaskStartScheduler(); /* start the RTOS, create the IDLE task and run my tasks (if any) */

  for(;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP"); /* something to use as a breakpoint stop while looping */
  }
}



