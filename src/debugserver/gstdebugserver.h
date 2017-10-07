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

/**
 * GstDebugserverTracer:
 *
 * Opaque #GstDebugserverTracer data structure
 */
G_DECLARE_FINAL_TYPE(GstDebugserverTracer, gst_debugserver_tracer, GST, DEBUGSERVER_TRACER, GstTracer)

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


G_END_DECLS

#endif /* __GST_DEBUGSERVER_TRACER_H__ */
