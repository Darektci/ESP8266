/*
 ============================================================================
 Name        : dht_esp01.c
 Author      : Przemyslaw Zygmunt przemek@supla.org
 Copyright   : GPLv2
 ============================================================================
*/

#define B_CFG_PORT          3
#define B_RELAY1_PORT       0  
//#define B_SENSOR_PORT1      3


void ICACHE_FLASH_ATTR supla_esp_board_set_device_name(char *buffer, uint8 buffer_size) {
    #ifdef __BOARD_dht11_esp01
	ets_snprintf(buffer, buffer_size, "SUPLA-DM-DHT11-ESP01");
	#elif defined(__BOARD_dht22_esp01)
	ets_snprintf(buffer, buffer_size, "SUPLA-DM-DHT22-ESP01");
	#elif defined(__BOARD_am2302_esp01)
	ets_snprintf(buffer, buffer_size, "SUPLA-DM-AM2302-ESP01");
	#endif
}

	
void supla_esp_board_gpio_init(void) {
		
		
	supla_input_cfg[0].type = supla_esp_cfg.CfgButtonType == BTN_TYPE_SWITCH ? INPUT_TYPE_SWITCH : INPUT_TYPE_BUTTON;
	supla_input_cfg[0].gpio_id = B_CFG_PORT;
	supla_input_cfg[0].flags = INPUT_FLAG_PULLUP | INPUT_FLAG_CFG_BTN;

		// ---------------------------------------
		// ---------------------------------------

    supla_relay_cfg[0].gpio_id = B_RELAY1_PORT;
	supla_relay_cfg[0].flags = RELAY_FLAG_RESET;
	supla_relay_cfg[0].channel = 1;
	
	//supla_input_cfg[1].type = INPUT_TYPE_SENSOR;
	//supla_input_cfg[1].gpio_id = B_SENSOR_PORT1;
	//supla_input_cfg[1].channel = 2;

}

void supla_esp_board_set_channels(TDS_SuplaRegisterDevice_B *srd) {

	srd->channel_count = 2;
	
	
	srd->channels[1].Number = 1;
	srd->channels[1].Type = SUPLA_CHANNELTYPE_RELAY;
	//srd->channels[1].FuncList =  SUPLA_BIT_RELAYFUNC_CONTROLLINGTHEGATEWAYLOCK \
									| SUPLA_BIT_RELAYFUNC_CONTROLLINGTHEGATE \
									| SUPLA_BIT_RELAYFUNC_CONTROLLINGTHEGARAGEDOOR \
									| SUPLA_BIT_RELAYFUNC_CONTROLLINGTHEDOORLOCK;
				
	srd->channels[1].FuncList = SUPLA_BIT_RELAYFUNC_LIGHTSWITCH \
								 | SUPLA_BIT_RELAYFUNC_POWERSWITCH;
	srd->channels[1].Default = SUPLA_CHANNELFNC_POWERSWITCH;
	srd->channels[1].value[0] = supla_esp_gpio_relay_on(B_RELAY1_PORT);
	
	
	srd->channels[0].Number = 0;
	#ifdef __BOARD_dht11_esp01
	  srd->channels[0].Type = SUPLA_CHANNELTYPE_DHT11;
	#elif defined(__BOARD_dht22_esp01)
	  srd->channels[0].Type = SUPLA_CHANNELTYPE_DHT22;
	#elif defined(__BOARD_am2302_esp01)
	  srd->channels[0].Type = SUPLA_CHANNELTYPE_AM2302;
	#endif

	srd->channels[0].FuncList = 0;
	srd->channels[0].Default = 0;

	supla_get_temp_and_humidity(srd->channels[0].value);
	

	//srd->channels[2].Number = 2;
	//srd->channels[2].Type = SUPLA_CHANNELTYPE_SENSORNO;
	//srd->channels[2].FuncList = 0;
	//srd->channels[2].Default = 0;
	//srd->channels[2].value[0] = 0;
	

}

void supla_esp_board_send_channel_values_with_delay(void *srpc) {
	//supla_esp_channel_value_changed(2, gpio__input_get(B_SENSOR_PORT1));
}
