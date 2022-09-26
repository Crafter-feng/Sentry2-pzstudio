/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */

#ifndef MICROPY_INCLUDED_ESP32_MODNETWORK_H
#define MICROPY_INCLUDED_ESP32_MODNETWORK_H

enum { PHY_LAN8720, PHY_IP101, PHY_RTL8201, PHY_DP83848, PHY_KSZ8041 };
enum { ETH_INITIALIZED, ETH_STARTED, ETH_STOPPED, ETH_CONNECTED, ETH_DISCONNECTED, ETH_GOT_IP };

MP_DECLARE_CONST_FUN_OBJ_KW(get_lan_obj);
MP_DECLARE_CONST_FUN_OBJ_1(ppp_make_new_obj);
MP_DECLARE_CONST_FUN_OBJ_VAR_BETWEEN(esp_ifconfig_obj);
MP_DECLARE_CONST_FUN_OBJ_KW(esp_config_obj);

void usocket_events_deinit(void);

#endif
