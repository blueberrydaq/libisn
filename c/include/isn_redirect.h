/** \file
 *  \brief ISN Redirect Driver
 *  \author Uros Platise <uros@isotel.org>
 *  \see isn_redirect.c
 */
/**
 * \ingroup GR_ISN
 * \defgroup GR_ISN_Redirect Redirect Driver
 * 
 * # Scope
 * 
 * Implements the ISN Redirect Driver as a supporting element in building
 * more complex structures. It is fully transparent to the Protocol Structure, 
 * does not alter any data.
 * 
 * # Concept
 * 
 * It is a receiver only object, and loops back the received data to the target object.
 * 
 * Example below is a bi-directional bridge and re-framer between the UART and USBFS where:
 * 
 * - UART is carrying data packed with the CRC (ISN_FRAME_MODE_COMPACT),
 * - and USBFS encapsulated the same data into a SHORT FRAME without the CRC (ISN_FRAME_MODE_SHORT).
 * ~~~
 * isn_uart_init(&isn_uart, &isn_cframe);
 * isn_frame_init(&isn_cframe, ISN_FRAME_MODE_COMPACT, &isn_redirect_uartrx, NULL, &isn_uart, &counter_1kHz, 100);
 * isn_redirect_init(&isn_redirect_uartrx, &isn_sframe);
 * isn_frame_init(&isn_sframe, ISN_FRAME_MODE_SHORT, &isn_redirect_uarttx, NULL, &isn_usbfs, &counter_1kHz, 100);
 * isn_redirect_init(&isn_redirect_uarttx, &isn_cframe); 
 * isn_usbfs_init(&isn_usbfs, USBFS_DWR_POWER_OPERATION, &isn_sframe);
 * ~~~
 */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * (c) Copyright 2019, Isotel, http://isotel.org
 */

#ifndef __ISN_REDIRECT_H__
#define __ISN_REDIRECT_H__

#include "isn_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------*/
/* DEFINITIONS                                                        */
/*--------------------------------------------------------------------*/

typedef struct {
    /* ISN Abstract Class Driver */
    isn_driver_t drv;

    /* Private data */
    isn_driver_t* target;
    uint8_t en_fragment;    ///< Enable fragmention
}
isn_redirect_t;

/*----------------------------------------------------------------------*/
/* Public functions                                                     */
/*----------------------------------------------------------------------*/

/** Redirect
 * 
 * \param obj
 * \param target layer where data received should be copied to; if target is
 *    NULL it redirects back to the caller; see isn_loopback_init()
 */
void isn_redirect_init(isn_redirect_t *obj, isn_layer_t* target);

/** Loopback - Redirect Back to the Caller
 * 
 * It is a special case of the redirect behaviour in which case data is 
 * returned back to the caller.
 * 
 * \param obj
 */
inline static void isn_loopback_init(isn_redirect_t *obj) { isn_redirect_init(obj, NULL); }

/** Enable Fragmentation
 * 
 * Means that a driver checks will forward data even if target has less than required
 * amount of buffer available. This is works for streaming data and is only possible if 
 * there are no other packet oriented
 * protocols in the loop.
 * 
 * \param obj
 * \param state set to non-zero value to enable fragmentation
 */
inline static void isn_redirect_setfragmentation(isn_redirect_t *obj, uint8_t state) {obj->en_fragment = state;}

#ifdef __cplusplus
}
#endif

#endif
