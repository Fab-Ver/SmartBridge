package com.smartbridge.com.smartbridge.maven.eclipse;

public interface SmartBridgeObserver {
	
	/**
	 * Run the smart bridge system.
	 * @throws Exception
	 */
	void run() throws Exception;
	
	/**
	 * Send the message on the serial port.
	 * @param msg 
	 */
	void sendMessage(String msg);
	
}
