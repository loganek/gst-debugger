/* GStreamer
 * Copyright (C) 2015 Marcin Kolny <marcin.kolny@gmail.com>
 *
 * gstdebugserver.c: tracing module that sends serialized data to
 * an user.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_DEBUGSERVER_TRACER_H__
#define __GST_DEBUGSERVER_TRACER_H__

#include "gstdebugservertcp.h"
#include "gstdebugserverlog.h"
#include "gstdebugservermessage.h"
#include "gstdebugserverqe.h"
#include "gstdebugserverbuffer.h"

#include <gst/gst.h>

#define GST_USE_UNSTABLE_API
#include <gst/gsttracer.h>

G_BEGIN_DECLS

#define GST_TYPE_DEBUGSERVER_TRACER \
  (gst_debugserver_tracer_get_type())
#define GST_DEBUGSERVER_TRACER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_DEBUGSERVER_TRACER,GstDebugserverTracer))
#define GST_DEBUGSERVER_TRACER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_DEBUGSERVER_TRACER,GstDebugserverTracerClass))
#define GST_IS_DEBUGSERVER_TRACER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_DEBUGSERVER_TRACER))
#define GST_IS_DEBUGSERVER_TRACER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_DEBUGSERVER_TRACER))
#define GST_DEBUGSERVER_TRACER_CAST(obj) ((GstDebugserverTracer *)(obj))

typedef struct _GstDebugserverTracer GstDebugserverTracer;
typedef struct _GstDebugserverTracerClass GstDebugserverTracerClass;

/**
 * GstDebugserverTracer:
 *
 * Opaque #GstDebugserverTracer data structure
 */
struct _GstDebugserverTracer {
  GstTracer 	 parent;

  /*< private >*/
  GstPipeline *pipeline;
  gint port;
  gint max_connections;
  GstDebugserverTcp *tcp_server;
  GstDebugserverLog *log;
  GstDebugserverMessage *message;
  GstDebugserverQE *event;
  GstDebugserverQE *query;
  GstDebugserverBuffer *buffer;
};

struct _GstDebugserverTracerClass {
  GstTracerClass parent_class;

  /* signals */
};

G_GNUC_INTERNAL GType gst_debugserver_tracer_get_type (void);

G_END_DECLS

#endif /* __GST_DEBUGSERVER_TRACER_H__ */
