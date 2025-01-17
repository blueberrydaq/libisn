/** \file
 *  \brief ISN Transport Layer
 *  \author Uros Platise <uros@isotel.org>
 *  \see https://www.isotel.org/isn/transport.html
 */
/**
 * \ingroup GR_ISN
 * \defgroup GR_ISN_Trans Transport Layer Driver
 * 
 * # Scope
 * 
 * Implements Device side of the [ISN Transport Protocol](https://www.isotel.org/isn/transport.html)
 * 
 * \note Specs are unaligned: tx counter is 16-bit and little endian
 * 
 * # Concept
 * 
 * This layer is in the development and only limited subset is implemented:
 * 
 * - single port
 * - long transport with tx counter stamping to allow ordering on host side
 */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * (c) Copyright 2019, Isotel, http://isotel.org
 */

#ifndef __ISN_TRANS_H__
#define __ISN_TRANS_H__

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
    isn_driver_t* parent;
    isn_driver_t* child;

    uint8_t port;
}
isn_trans_t;

/*----------------------------------------------------------------------*/
/* Public functions                                                     */
/*----------------------------------------------------------------------*/

/** Initialize Long Transport Layer
 * 
 * \param obj
 * \param child layer
 * \param parent protocol layer, which is typically a PHY, or FRAME
 * \param port (not implemented)
 */
void isn_translong_init(isn_trans_t *obj, isn_layer_t* child, isn_layer_t* parent, uint8_t port);

#ifdef __cplusplus
}
#endif

#endif
