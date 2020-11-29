#include "mgos.h"
#include "mgos_mqtt.h"
#include "mgos_zthing.h"
#include "mgos_zthing_mqtt.h"


bool mg_zthing_mqtt_birth_message_pub() {  
  int msg_id = false;
  const char *will_topic = mgos_sys_config_get_mqtt_will_topic();
  const char *birth_message = mgos_sys_config_get_zthing_mqtt_birth_message();
  if (will_topic != NULL && birth_message != NULL) {
    msg_id = mgos_zthing_mqtt_pub(will_topic, birth_message, false);
    if (msg_id <= 0) {
      LOG(LL_ERROR, ("Error publishing MQTT birth message"));
    }
  }
  return (msg_id > 0);
}

static void mg_zthing_mqtt_on_event(struct mg_connection *nc,
                                     int ev,
                                     void *ev_data,
                                     void *user_data) {  
  if (ev == MG_EV_MQTT_CONNACK) {
    // Publish the 'birth' message 
    mg_zthing_mqtt_birth_message_pub();
    mgos_event_trigger(MGOS_EV_ZTHING_UPDATE_STATE, NULL);
  } else if (ev == MG_EV_MQTT_DISCONNECT) {
  }
  (void) ev_data;
  (void) nc;
  (void) user_data;
}

int mgos_zthing_mqtt_pub(const char *topic, const char *msg, bool retain) {
  return mgos_mqtt_pub(topic, msg, (msg == NULL ? 0 : strlen(msg)),
      mgos_sys_config_get_zthing_mqtt_qos(), retain);
}

int mgos_zthing_mqtt_pubf(const char *topic, bool retain, const char *json_fmt, ...) {
  va_list ap;
  va_start(ap, json_fmt);
  int r = mgos_zthing_mqtt_pubv(topic, retain, json_fmt, ap);
  va_end(ap);
  return r;
}

int mgos_zthing_mqtt_pubv(const char *topic, bool retain, const char *json_fmt, va_list ap) {
  return mgos_mqtt_pubv(topic, mgos_sys_config_get_zthing_mqtt_qos(), retain, json_fmt, ap);
}

bool mgos_zthing_mqtt_init() {

  // replace $device_id placehoder/s in will_topic 
  const char *will_topic = mgos_sys_config_get_mqtt_will_topic();
  if (will_topic != NULL) {
    char *nwt = NULL;
    if (mgos_zthing_sreplace(will_topic, MGOS_ZTHING_ENV_DEVICEID,
        mgos_sys_config_get_device_id(), &nwt)) {
      LOG(LL_DEBUG, ("MQTT will topic updated to %s", nwt));
      mgos_sys_config_set_mqtt_will_topic(nwt);
      free(nwt);
    }
  }

  mgos_mqtt_add_global_handler(mg_zthing_mqtt_on_event, NULL);

  return true;
} 
