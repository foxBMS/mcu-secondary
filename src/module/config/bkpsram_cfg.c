/**
 *
 * @copyright &copy; 2010 - 2017, Fraunhofer-Gesellschaft zur Foerderung der angewandten Forschung e.V. All rights reserved.
 *
 * BSD 3-Clause License
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * 1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * We kindly request you to use one or more of the following phrases to refer to foxBMS in your hardware, software, documentation or advertising materials:
 *
 * &Prime;This product uses parts of foxBMS&reg;&Prime;
 *
 * &Prime;This product includes parts of foxBMS&reg;&Prime;
 *
 * &Prime;This product is derived from foxBMS&reg;&Prime;
 *
 */

/**
 * @file    bkpsram_cfg.c
 * @author  foxBMS Team
 * @date    02.03.2016 (date of creation)
 * @ingroup DRIVERS_CONF
 * @prefix  BKP
 *
 * @brief   Configuration for static backup RAM
 *
 */

/*================== Includes =============================================*/
/* recommended include order of header files:
 * 
 * 1.    include general.h
 * 2.    include module's own header
 * 3...  other headers
 *
 */
#include "general.h"
#include "bkpsram_cfg.h"

#include "mcu.h"

/*================== Macros and Definitions ===============================*/


/*================== Constant and Variable Definitions ====================*/
BKPSRAM_CH_NVSOC_s MEM_BKP_SRAM bkpsram_nvsoc;
BKPSRAM_CH_CONT_COUNT_s MEM_BKP_SRAM bkpsram_contactors_count;
BKPSRAM_CH_OP_HOURS_s MEM_BKP_SRAM bkpsram_operating_hours;
MAIN_STATUS_s MEM_BKP_SRAM main_state;
BKPSRAM_OPERATING_HOURS_s MEM_BKP_SRAM bkpsram_op_hours;


const BKPSRAM_CH_NVSOC_s default_nvsoc = {
    .data.max            = 50.0,
    .data.min            = 50.0,
    .data.mean           = 50.0
};

const BKPSRAM_CH_CONT_COUNT_s default_contactors_count = {
    .data.cont_switch_closed = {0,0,0},
    .data.cont_switch_opened = {0,0,0},
    .data.cont_switch_opened = {0,0,0}

};

const BKPSRAM_CH_OP_HOURS_s default_operating_hours = {
    .data = { 0,0,0,0,0,0,0 }

};

/*================== Function Prototypes ==================================*/

/*================== Function Implementations =============================*/

void BKPSRAM_Set_contactorcnt(DIAG_CONTACTOR_s *ptr) {
    uint32_t interrupt_status = 0;

    /* Disable interrupts */
    interrupt_status = MCU_DisableINT();

    /* update bkpsram values */
    bkpsram_contactors_count.data = *ptr;

    /* calculate checksum*/
    //bkpsram_ch_1.checksum = EEPR_CalcChecksum((uint8_t *)(&bkpsram_ch_1),sizeof(bkpsram_ch_1)-4);

    /* Enable interrupts */
    MCU_RestoreINT(interrupt_status);
}


void BKPSRAM_Get_contactorcnt(DIAG_CONTACTOR_s *ptr) {
    *ptr = bkpsram_contactors_count.data;

}


