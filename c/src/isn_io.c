/** \file
 *  \brief ISN Protocol I/O
 *  \author Uros Platise <uros@isotel.org>
 *  \see isn_io.h
 */
/**
 * \ingroup GR_ISN
 * \cond Implementation
 * \addtogroup GR_ISN_IO
 */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * (c) Copyright 2019, Isotel, http://isotel.org
 */

#include <string.h>
#include "isn_io.h"

/**\{ */

int isn_write_atleast(isn_layer_t *layer, const void *src, size_t size, size_t minsize) {
    if (size) {
        void *buf;
        isn_driver_t *drv = (isn_driver_t *)layer;
        int avail = drv->getsendbuf(drv, &buf, size, drv);
        if (buf) {
            if (avail >= (int)minsize) {
                memcpy(buf, src, avail);
                return drv->send(drv, buf, avail);
            }
            drv->free(drv, buf);
        }
    }
    return 0;
}

/** \} \endcond */
