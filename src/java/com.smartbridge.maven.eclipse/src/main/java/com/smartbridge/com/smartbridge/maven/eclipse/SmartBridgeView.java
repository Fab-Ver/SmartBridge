package com.smartbridge.com.smartbridge.maven.eclipse;

public interface ApplicationView {
	/**
	 * Connect an observer to the application view.
	 * @param observer
	 */
	void setObserver(ApplicationViewObserver observer);
	
	/**
	 * Report to the ApplicationView the status of water level subsystem.
	 * @param msg subsystem situation.
	 * @param wl water level of the river.
	 */
	void writeFSMStatus(String msg, double wl);
	
	/**
	 * Report to the ApplicationView the status of smart light subsystem.
	 * @param msg smart light subsystem status.
	 */
	void writeLedStatus(String msg);
	
	/**
	 * Show the ApplicationView.
	 */
	void start();
}
