package com.smartbridge.com.smartbridge.maven.eclipse;

public interface SmartBridgeView {

	/**
	 * Connect an observer to the application view.
	 * 
	 * @param observer
	 */
	void setObserver(SmartBridgeObserver observer);

	/**
	 * Report to the view the status of water level subsystem.
	 * 
	 * @param msg subsystem situation.
	 * @param wl  water level of the river.
	 */
	void writeSysStatus(String msg, String wl);

	/**
	 * Report to the view the status of smart light subsystem.
	 * 
	 * @param msg smart light subsystem status.
	 */
	void writeLedStatus(String msg);

	/**
	 * Show the smart bridge application.
	 */
	void start();
}
