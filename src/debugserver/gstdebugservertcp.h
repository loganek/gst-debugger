/* GStreamer
 * Copyright (C) 2015 Marcin Kolny <marcin.kolny@gmail.com>
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

#ifndef __GST_DEBUGSERVER_TCP_H__
#define __GST_DEBUGSERVER_TCP_H__

#include "common/gstdebugger.pb-c.h"

#include <gio/gio.h>

G_BEGIN_DECLS

#define GST_TYPE_DEBUGSERVER_TCP \
  (gst_debugserver_tcp_get_type())
#define GST_DEBUGSERVER_TCP(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_DEBUGSERVER_TCP,GstDebugserverTcp))
#define GST_TYPE_DEBUGSERVER_TCP_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_DEBUGSERVER_TCP,GstDebugserverTcpClass))
#define GST_IS_DEBUGSERVER_TCP(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_DEBUGSERVER_TCP))
#define GST_IS_DEBUGSERVER_TCP_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_DEBUGSERVER_TCP))
#define GST_DEBUGSERVER_TCP_CAST(obj) ((GstDebugserverTcp *)(obj))

typedef struct _TcpClient {
  GSocketConnection * connection;
  GMutex mutex;
  GCancellable * cancel;
} TcpClient;

typedef void (*GstDebugserverTcpHandleCommandFunction)
    (GstDebugger__Command * command, gpointer user_data, TcpClient * client);

typedef void (*GstDebugserverTcpClientDisconnectedFunction)
    (TcpClient * client, gpointer user_data);

typedef struct _GstDebugserverTcp GstDebugserverTcp;
typedef struct _GstDebugserverTcpClass GstDebugserverTcpClass;

struct _GstDebugserverTcp {
  GObject parent_instance;
  gpointer owner;

  GstDebugserverTcpHandleCommandFunction command_handler;
  GstDebugserverTcpClientDisconnectedFunction client_disconnected_handler;

  /*< private >*/
  GSocketService * service;
  GSList * clients;
  GMutex clients_mutex;
  GCond client_removed_cond;
};

struct _GstDebugserverTcpClass
{
  GObjectClass parent_class;

  void (*command_received)     (gpointer *tracer, GstDebugger__Command *command);
};

GstDebugserverTcp * gst_debugserver_tcp_new (void);

gboolean gst_debugserver_tcp_start_server (GstDebugserverTcp * tcp, guint port);

gboolean gst_debugserver_tcp_send_packet (GstDebugserverTcp * tcp, TcpClient * client,
  GstDebugger__GStreamerData * gst_data);

G_GNUC_INTERNAL GType gst_debugserver_tcp_get_type (void);

G_END_DECLS

#endif /* __GST_DEBUGSERVER_TCP_H__ */
