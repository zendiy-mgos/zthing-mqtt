/*
 * Copyright (c) 2020 ZenDIY
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MGOS_ZTHING_MQTT_H_
#define MGOS_ZTHING_MQTT_H_

#include<stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int mgos_zthing_mqtt_pub(const char *topic, const char *msg, bool retain);
int mgos_zthing_mqtt_pubf(const char *topic, bool retain, const char *json_fmt, ...);
int mgos_zthing_mqtt_pubv(const char *topic, bool retain, const char *json_fmt, va_list ap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_ZTHING_MQTT_H_ */
