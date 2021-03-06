/*
 * common.h
 *
 *  Created on: Jul 14, 2015
 *      Author: loganek
 */

#ifndef SRC_PROTOCOL_COMMON_H_
#define SRC_PROTOCOL_COMMON_H_

#include <glib.h>

G_BEGIN_DECLS

typedef enum _InternalGType
{
  INTERNAL_GTYPE_FUNDAMENTAL = 0,
  INTERNAL_GTYPE_ENUM = 1,
  INTERNAL_GTYPE_FLAGS = 2,
  INTERNAL_GTYPE_CAPS = 3,
  INTERNAL_GTYPE_GST_OBJECT = 4,
  INTERNAL_GTYPE_UNKNOWN = 5,
} InternalGType;

G_END_DECLS

#endif /* SRC_PROTOCOL_COMMON_H_ */
