#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "iot_gpio.h" 
#include <unistd.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

#include "wifi_hotspot.h"
#include "lwip/netifapi.h"
#include "wifi_device.h"

#include "lwip/api_shell.h"
#include "shared/netutils/netutils.h"

MP_STATIC int g_connected = 0;
MP_STATIC struct netif* iface;
MP_STATIC int netId = -1;


static ip4_addr_t host_ipAddr;
static ip4_addr_t host_netMask;
static ip4_addr_t host_gw;




MP_STATIC void PrintLinkedInfo(WifiLinkedInfo* info)
{
    if (!info) return;

    MP_STATIC char macAddress[32] = {0};
    unsigned char* mac = info->bssid;
    snprintf(macAddress, sizeof(macAddress), "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf("bssid: %s, rssi: %d, connState: %d, reason: %d, ssid: %s\r\n",
        macAddress, info->rssi, info->connState, info->disconnectedReason, info->ssid);
	
	
}


MP_STATIC void OnWifiConnectionChanged(int state, WifiLinkedInfo* info)
{
    if (!info) return;

    printf("%s %d, state = %d, info = \r\n", __FUNCTION__, __LINE__, state);
    PrintLinkedInfo(info);
	
    if (state == WIFI_STATE_AVALIABLE) {
        g_connected = 1;
		
    } else {
        g_connected = 0;
    }
}

MP_STATIC void OnWifiScanStateChanged(int state, int size)
{
    printf("%s %d, state = %X, size = %d\r\n", __FUNCTION__, __LINE__, state, size);
}
mp_obj_t mp_network_connectWifi(mp_obj_t wifissid, mp_obj_t wifipassword) {
    char *ssid = mp_obj_str_get_str(wifissid);
    char *password = mp_obj_str_get_str(wifipassword);
	int cnt = 0;
    WifiErrorCode errCode;
    WifiEvent eventListener = {
        .OnWifiConnectionChanged = OnWifiConnectionChanged,
        .OnWifiScanStateChanged = OnWifiScanStateChanged
    };
    WifiDeviceConfig apConfig = {};
    osDelay(10);
    errCode = RegisterWifiEvent(&eventListener);
    printf("RegisterWifiEvent: %d\r\n", errCode);

    // setup your AP params
    strcpy(apConfig.ssid, ssid);
    strcpy(apConfig.preSharedKey, password);
    apConfig.securityType = WIFI_SEC_TYPE_PSK;
    errCode = EnableWifi();
    printf("EnableWifi: %d\r\n", errCode);
    osDelay(10);

    errCode = AddDeviceConfig(&apConfig, &netId);
    printf("AddDeviceConfig: %d\r\n", errCode);

    g_connected = 0;
    errCode = ConnectTo(netId);
    printf("ConnectTo(%d): %d\r\n", netId, errCode);

    while (!g_connected && cnt<20) {
		cnt++;
        osDelay(50);
    }
    printf("g_connected: %d\r\n", g_connected);
    osDelay(50);
	if(cnt < 20){
    // 联网业务开始
	    iface = netifapi_netif_find("wlan0");
	    if (iface) {
	        err_t ret1 = netifapi_dhcp_start(iface);
	        printf("netifapi_dhcp_start: %d\r\n", ret1);

	        osDelay(200); // wait DHCP server give me IP
	        //err_t ret0 = netifapi_netif_common(iface, dhcp_clients_info_show, NULL);
			//err_t ret0 = netifapi_netif_common(iface, dhcp_clients_info_show, NULL);
	        //printf("netifapi_netif_common: %d\r\n", ret0);

			#if 0
			ip4_addr_t ip = {0};
	        ip4_addr_t netmask = {0};
	        ip4_addr_t gw = {0};
	        int get_ret = netifapi_netif_get_addr(iface, &ip, &netmask, &gw);
			printf("netifapi_netif_get_addr: %d\r\n", get_ret);
	        if (get_ret == ERR_OK) {
	            printf("ip = %s\r\n", ip4addr_ntoa(&ip));
	            printf("netmask = %s\r\n", ip4addr_ntoa(&netmask));
	            printf("gw = %s\r\n", ip4addr_ntoa(&gw));
	        }
	       	#endif
			

			#if 0
			StationInfo result[6]={0};
			unsigned int size = 6;
			int get_ret = GetStationList(&result, &size);
			printf("get_ret = %d, ip_size = %d\r\n",get_ret,size);
			if(get_ret == WIFI_SUCCESS){				
				for(int i=0; i<size ;i++){
					printf("mac<");
					for(int kk=0; kk<WIFI_MAC_LEN; kk++){
						printf("0x%02x,",result[i].macAddress[kk]);
					}
					printf(">\r\n");
					printf("ip<");
					printf("%d.",(((result[i].ipAddress)>>24)&0xff));
					printf("%d.",(((result[i].ipAddress)>>16)&0xff));
					printf("%d.",(((result[i].ipAddress)>>8)&0xff));
					printf("%d",(((result[i].ipAddress)>>0)&0xff));
					printf(">\r\n");
				}
				
			}
			#endif
			if(ret1 == 0){
				
				return mp_const_true;
			}else{
				netifapi_dhcp_stop(iface);
				iface = NULL;
			}
			
	    }
	}
	Disconnect();
	RemoveDevice(netId);
	DisableWifi();
	UnRegisterWifiEvent(&eventListener);
	g_connected = 0;
    // while (1) {
    //     errCode = EnableWifi();
    //     printf("EnableWifi: %d\r\n", errCode);
    //     osDelay(10);

    //     errCode = AddDeviceConfig(&apConfig, &netId);
    //     printf("AddDeviceConfig: %d\r\n", errCode);

    //     g_connected = 0;
    //     errCode = ConnectTo(netId);
    //     printf("ConnectTo(%d): %d\r\n", netId, errCode);

    //     while (!g_connected) {
    //         osDelay(10);
    //     }
    //     printf("g_connected: %d\r\n", g_connected);
    //     osDelay(50);

    //     // 联网业务开始
    //     iface = netifapi_netif_find("wlan0");
    //     if (iface) {
    //         err_t ret = netifapi_dhcp_start(iface);
    //         printf("netifapi_dhcp_start: %d\r\n", ret);

    //         osDelay(200); // wait DHCP server give me IP
    //         ret = netifapi_netif_common(iface, dhcp_clients_info_show, NULL);
    //         printf("netifapi_netif_common: %d\r\n", ret);
    //     }

    //     // 模拟一段时间的联网业务
    //     int timeout = 120;
    //     while (timeout--) {
    //         osDelay(100);
    //         printf("after %d seconds, I'll disconnect WiFi!\n", timeout);
    //     }

    //     // 联网业务结束
    //     err_t ret = netifapi_dhcp_stop(iface);
    //     printf("netifapi_dhcp_stop: %d\r\n", ret);

    //     Disconnect(); // disconnect with your AP

    //     RemoveDevice(netId); // remove AP config

    //     errCode = DisableWifi();
    //     printf("DisableWifi: %d\r\n", errCode);
    //     osDelay(200);
    // }
    return mp_const_false;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_network_connectWifi_obj, mp_network_connectWifi);

mp_obj_t mp_network_disconnectWifi(void) {
    WifiErrorCode errCode;
    // 联网业务结束
    err_t ret = netifapi_dhcp_stop(iface);
    printf("netifapi_dhcp_stop: %d\r\n", ret);

    Disconnect(); //disconnect with your AP

    RemoveDevice(netId); //remove AP config

    errCode = DisableWifi();
    printf("DisableWifi: %d\r\n", errCode);
    osDelay(200);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(mp_network_disconnectWifi_obj, mp_network_disconnectWifi);

static volatile int g_hotspotStarted = 0;

static void OnHotspotStateChanged(int state)
{
    printf("OnHotspotStateChanged: %d.\r\n", state);
    if (state == WIFI_HOTSPOT_ACTIVE) {
        g_hotspotStarted = 1;
    } else {
        g_hotspotStarted = 0;
    }
}

static volatile int g_joinedStations = 0;

static void PrintStationInfo(StationInfo* info)
{
    if (!info) return;
    static char macAddress[32] = {0};
    unsigned char* mac = info->macAddress;
    snprintf(macAddress, sizeof(macAddress), "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    printf(" PrintStationInfo: mac=%s, reason=%d.\r\n", macAddress, info->disconnectedReason);
}

static void OnHotspotStaJoin(StationInfo* info)
{
    g_joinedStations++;
    PrintStationInfo(info);
    printf("+OnHotspotStaJoin: active stations = %d.\r\n", g_joinedStations);
}

static void OnHotspotStaLeave(StationInfo* info)
{
    g_joinedStations--;
    PrintStationInfo(info);
    printf("-OnHotspotStaLeave: active stations = %d.\r\n", g_joinedStations);
}

WifiEvent g_defaultWifiEventListener = {
    .OnHotspotStaJoin = OnHotspotStaJoin,
    .OnHotspotStaLeave = OnHotspotStaLeave,
    .OnHotspotStateChanged = OnHotspotStateChanged,
};

static struct netif* g_iface = NULL;
mp_obj_t mp_network_startHotspot(mp_obj_t wifissid, mp_obj_t wifipassword) {
    char *ssid = mp_obj_str_get_str(wifissid);
    char *password = mp_obj_str_get_str(wifipassword);
    HotspotConfig config = {0};
    // 准备AP的配置参数
    strcpy(config.ssid, ssid);
    strcpy(config.preSharedKey, password);
    config.securityType = WIFI_SEC_TYPE_PSK;
    config.band = HOTSPOT_BAND_TYPE_2G;
    config.channelNum = 7;
    WifiErrorCode errCode = WIFI_SUCCESS;
    errCode = RegisterWifiEvent(&g_defaultWifiEventListener);
    printf("RegisterWifiEvent: %d\r\n", errCode);
    errCode = SetHotspotConfig(&config);
    printf("SetHotspotConfig: %d\r\n", errCode);
    g_hotspotStarted = 0;
    errCode = EnableHotspot();
    //printf("EnableHotspot: %d\r\n", errCode);
    while (!g_hotspotStarted) {
        osDelay(10);
    }
    //printf("g_hotspotStarted = %d.\r\n", g_hotspotStarted);
	/*
    g_iface = netifapi_netif_find("ap0");
    if (g_iface) {
        netifapi_netif_set_addr(g_iface, &host_ipAddr, &host_netMask, &host_gw);
		if (netifapi_dhcps_start(g_iface, 0, 0) != 0) {
	         mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("start host config ip failed"));
	        (void)hi_wifi_softap_stop();
	        return mp_const_none;
	    }else{
			
	    }
    }
	*/
	if(g_hotspotStarted){
		struct netif *netif = NULL;
	    netif = netif_find("ap0");
	    if (netif == NULL) {
	        mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("start host failed"));
	        return mp_const_none;
	    }
		/* 先停止dhcp */
		if(netifapi_dhcps_stop(netif)!=0){
			 mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("config ip failed"));
	        return mp_const_none;
		}
		
		netifapi_netif_set_addr(netif, &host_ipAddr, &host_netMask, &host_gw);
		/* 开启dhcp */
		if (netifapi_dhcps_start(netif, 0, 0) != 0) {
	         mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("start host config ip failed"));
	        (void)hi_wifi_softap_stop();
	        return mp_const_none;
	    }
	}
	
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_network_startHotspot_obj, mp_network_startHotspot);

mp_obj_t mp_network_stopHotspot(void) {
    if (g_iface) {
        err_t ret = netifapi_dhcps_stop(g_iface);  // 海思扩展的HDCP服务接口
        //printf("netifapi_dhcps_stop: %d\r\n", ret);
    }

    WifiErrorCode errCode = UnRegisterWifiEvent(&g_defaultWifiEventListener);
    //printf("UnRegisterWifiEvent: %d\r\n", errCode);

    errCode = DisableHotspot();
    //printf("EnableHotspot: %d\r\n", errCode);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_0(mp_network_stopHotspot_obj, mp_network_stopHotspot);



static mp_obj_t mp_network_is_activate(void){
	if(g_hotspotStarted){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}

MP_DEFINE_CONST_FUN_OBJ_0(mp_network_is_activate_obj, mp_network_is_activate);



static mp_obj_t mp_network_ifconfig(void){
		ip4_addr_t ip = {0};
        ip4_addr_t netmask = {0};
        ip4_addr_t gw = {0};
		if(iface!=NULL){
			int get_ret = netifapi_netif_get_addr(iface, &ip, &netmask, &gw);
			///printf("netifapi_netif_get_addr: %d\r\n", get_ret);
	        
		}
		if(g_iface!=NULL){
			int get_ret = netifapi_netif_get_addr(g_iface, &ip, &netmask, &gw);
		}
        mp_obj_t tuple[3] = {
            netutils_format_ipv4_addr((uint8_t *)&(ip.addr), NETUTILS_BIG),
            netutils_format_ipv4_addr((uint8_t *)&(netmask.addr), NETUTILS_BIG),
            netutils_format_ipv4_addr((uint8_t *)&(gw.addr), NETUTILS_BIG),
            //netutils_format_ipv4_addr((uint8_t *)&dns_info.ip, NETUTILS_BIG),
       	};
        return mp_obj_new_tuple(3, tuple);
}

MP_DEFINE_CONST_FUN_OBJ_0(mp_network_ifconfig_obj, mp_network_ifconfig);


static mp_obj_t mp_network_is_connect(void){
	if(g_connected){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}

MP_DEFINE_CONST_FUN_OBJ_0(mp_network_isconnect_obj, mp_network_is_connect);


#if 0
int IP_AP_ADDR0 = 192;
int IP_AP_ADDR1 = 168;
int IP_AP_ADDR2 = 5;
int IP_AP_ADDR3 = 1;
int GW_AP_ADDR0 = 192;
int GW_AP_ADDR1 = 168;
int GW_AP_ADDR2 = 5;
int GW_AP_ADDR3 = 1;
int NETMSK_ADDR0 = 255;
int NETMSK_ADDR1 = 255;
int NETMSK_ADDR2 = 255;
int NETMSK_ADDR3 = 0;
#endif

mp_obj_t mp_network_configHotspot(mp_obj_t _ip, mp_obj_t _netmask, mp_obj_t _gw) {
	if(g_hotspotStarted==0){
		#if 0
		char *temp_ip = mp_obj_str_get_str(_ip);
	    mp_obj_t ip_obj = mp_obj_new_str(temp_ip,strlen(temp_ip));
	    char *ip = mp_obj_str_get_str(ip_obj);
	    char *temp_netmask = mp_obj_str_get_str(_netmask);
	    mp_obj_t netmask_obj = mp_obj_new_str(temp_netmask,strlen(temp_netmask));
	    char *netmask = mp_obj_str_get_str(netmask_obj);
	    char *temp_gw = mp_obj_str_get_str(_gw);
	    mp_obj_t gw_obj = mp_obj_new_str(temp_gw,strlen(temp_gw));
	    char *gw = mp_obj_str_get_str(gw_obj);
	    char delims[] = ".";
	    char *result = NULL;
	    result = strtok(ip, delims);
		//printf("<%s>\r\n",result);
	    int index = 0;
	    while(result != NULL) {  
	        if(index == 0){
	            IP_AP_ADDR0 = atoi(result);
	            index++;
	        }else if(index == 1){
	            IP_AP_ADDR1 = atoi(result);
	            index++;
	        }else if(index == 2){
	            IP_AP_ADDR2 = atoi(result);
	            index++;
	        }else if(index == 3){
	            IP_AP_ADDR3 = atoi(result);
	            index++;
	        }
	        result = strtok( NULL, delims );  
	    }
	    index = 0;
	    result = strtok(netmask, delims);  
	    while(result != NULL) {  
	        if(index == 0){
	            NETMSK_ADDR0 = atoi(result);
	            index++;
	        }else if(index == 1){
	            NETMSK_ADDR1 = atoi(result);
	            index++;
	        }else if(index == 2){
	            NETMSK_ADDR2 = atoi(result);
	            index++;
	        }else if(index == 3){
	            NETMSK_ADDR3 = atoi(result);
	            index++;
	        }
	        result = strtok( NULL, delims );  
	    }
	    index = 0;
	    result = strtok(gw, delims);
	    while(result != NULL) {  
	        if(index == 0){
	            GW_AP_ADDR0 = atoi(result);
	            index++;
	        }else if(index == 1){
	            GW_AP_ADDR1 = atoi(result);
	            index++;
	        }else if(index == 2){
	            GW_AP_ADDR2 = atoi(result);
	            index++;
	        }else if(index == 3){
	            GW_AP_ADDR3 = atoi(result);
	            index++;
	        }
	        result = strtok( NULL, delims );  
	    }
		printf("IPAP<%d,%d,%d,%d>\r\n",IP_AP_ADDR0,IP_AP_ADDR1,IP_AP_ADDR2,IP_AP_ADDR3);
		printf("MASK<%d,%d,%d,%d>\r\n",NETMSK_ADDR0,NETMSK_ADDR1,NETMSK_ADDR2,NETMSK_ADDR3);
		printf("GW<%d,%d,%d,%d>\r\n",GW_AP_ADDR0,GW_AP_ADDR1,GW_AP_ADDR2,GW_AP_ADDR3);
		
	#else
		netutils_parse_ipv4_addr(_ip, (void *)&(host_ipAddr.addr), NETUTILS_BIG);
		netutils_parse_ipv4_addr(_netmask, (void *)&(host_ipAddr.addr), NETUTILS_BIG);
		netutils_parse_ipv4_addr(_gw, (void *)&(host_ipAddr.addr), NETUTILS_BIG);
		
	#endif
	}else{
		struct netif *netif = NULL;
		ip4_addr_t ipAddr;
		ip4_addr_t netMask;
	    ip4_addr_t gw;
	    netif = netif_find("ap0");
	    if (netif == NULL) {
	        mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("config ip failed"));
	        return mp_const_none;
	    }
		
		if(netifapi_dhcps_stop(netif)!=0){
			 mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("config ip failed"));
	        return mp_const_none;
		}
		netutils_parse_ipv4_addr(_ip, (void *)&(ipAddr.addr), NETUTILS_BIG);
		netutils_parse_ipv4_addr(_netmask, (void *)&(netMask.addr), NETUTILS_BIG);
		netutils_parse_ipv4_addr(_gw, (void *)&(gw.addr), NETUTILS_BIG);
		netifapi_netif_set_addr(netif, &ipAddr, &netMask, &gw);
		char *temp_gw = mp_obj_str_get_str(_gw);
		mp_obj_t gw_obj = mp_obj_new_str(temp_gw,strlen(temp_gw));
	    char *str = mp_obj_str_get_str(gw_obj);
		if (netifapi_dhcps_start(netif, str, 10) != 0) {
	        //printf("dhcps shell cmd excute fail!\r\n");
	         mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("config ip failed"));
	        (void)hi_wifi_softap_stop();
	        return mp_const_none;
	    }else{
	        printf("dhcps shell cmd excute success!\r\n");
	    }
	}
	return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_3(mp_network_configHotspot_obj, mp_network_configHotspot);

MP_STATIC const mp_rom_map_elem_t network_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_network) },
    { MP_ROM_QSTR(MP_QSTR_connectWifi), MP_ROM_PTR(&mp_network_connectWifi_obj) },
    { MP_ROM_QSTR(MP_QSTR_disconnectWifi), MP_ROM_PTR(&mp_network_disconnectWifi_obj) },
    { MP_ROM_QSTR(MP_QSTR_isconnected), MP_ROM_PTR(&mp_network_isconnect_obj) },
    { MP_ROM_QSTR(MP_QSTR_startHotspot), MP_ROM_PTR(&mp_network_startHotspot_obj) },
    { MP_ROM_QSTR(MP_QSTR_configHotspot), MP_ROM_PTR(&mp_network_configHotspot_obj) },
    { MP_ROM_QSTR(MP_QSTR_stopHotspot), MP_ROM_PTR(&mp_network_stopHotspot_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_activate), MP_ROM_PTR(&mp_network_is_activate_obj) },
    { MP_ROM_QSTR(MP_QSTR_ifconfig), MP_ROM_PTR(&mp_network_ifconfig_obj) },
	
};

MP_STATIC MP_DEFINE_CONST_DICT(network_module_globals, network_module_globals_table);

const mp_obj_module_t mp_module_network = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&network_module_globals,
};
