package com.smartbridge.com.smartbridge.maven.eclipse;

public interface SmartBridgeModel {
	
	/**
	 * Check if the message is correct
	 * @param message the message to be checked 
	 * @return true if it is correct, false otherwise. 
	 */
	boolean checkMessage(String message);
	
	/**
	 * Check if the message is a numeric string
	 * @param message
	 * @return	true if the string is numeric, false otherwise. 
	 */
	boolean isNumeric(String message);
}
