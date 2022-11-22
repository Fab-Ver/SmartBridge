package com.smartbridge.com.smartbridge.maven.eclipse;

public interface ApplicationViewObserver {
	
	/**
	 * Run the smart bridge system.
	 * @throws Exception
	 */
	void run() throws Exception;
	
	/**
	 * Send the status message on the serial port.
	 * @param msg 
	 */
	void sendMsg(String msg);
	
	/**
	 * Send the valve angle on the serial port. 
	 * @param angle
	 */
	void sendAngle(int angle);
}
