package com.smartbridge.com.smartbridge.maven.eclipse;

import java.util.List;

public class SmartBridgeModelImpl implements SmartBridgeModel {
	
	private final List<String> allowedMessages;
	
	public SmartBridgeModelImpl() {
		this.allowedMessages = List.of("MANUAL","PRE-ALARM","ALARM","NORMAL","LED_ON","LED_OFF","SYS_OFF","MANUAL_ON","MANUAL_OFF");
	}
	
	public boolean checkMessage(String message) {
		if(message == null) {
			return false;
		}
		return allowedMessages.stream().anyMatch(e -> e.equals(message));
	}

	@Override
	public boolean isNumeric(String message) {
		try {
			Float.parseFloat(message);
		} catch (NullPointerException e) {
			return false;
		} catch (NumberFormatException e) {
			return false;
		}
		return true;
	}
	
}
