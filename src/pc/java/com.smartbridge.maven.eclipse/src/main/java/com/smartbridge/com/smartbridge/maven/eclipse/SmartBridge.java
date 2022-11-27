package com.smartbridge.com.smartbridge.maven.eclipse;

public class SmartBridge implements SmartBridgeObserver{
	
	private static final int CALIBRATION_TIME_SEC = 20;
	
	private SerialCommChannel channel;
	private final SmartBridgeView view;
	private final SmartBridgeModel model;
	
	public SmartBridge(String[] args) throws Exception {
		
		if(args.length > 1) {
			System.out.println("args: <CommPortName>");
			System.exit(1);
		} 
		
		String comPortName = args.length == 1 ? args[0] : "COM3";
		
		try {
			this.channel = new SerialCommChannel(comPortName,9600);
		} catch (Exception e) {
			System.out.println("Error: something went wrong during serial port initialization");
			System.exit(1);
		}
		
		System.out.print("Waiting Arduino for rebooting...");		
		for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
	        System.out.print(".");
	        Thread.sleep(1000);
	    }
		System.out.println("ready");
		
		this.model = new SmartBridgeModelImpl();
		this.view = new SmartBridgeViewImpl();
		this.view.setObserver(this);
		this.view.start();
	}

	public void run() throws Exception{
		while (true){
			if(channel.isMsgAvailable()) {
				String msg = channel.receiveMsg();
				String[] messages = msg.split(" ");
				if(messages.length == 1) {
					if(model.checkMessage(messages[0])) {
						view.writeLedStatus(messages[0]);
					}
				} else if (messages.length == 2) {
					if(model.checkMessage(messages[0]) && model.isNumeric(messages[1])) {
						view.writeSysStatus(messages[0], messages[1]);
					}
				}
			}
		}
	}

	@Override
	public void sendMessage(String msg) {
		if(model.isNumeric(msg) || model.checkMessage(msg))
		this.channel.sendMsg(msg);
	}
	
	public static void main(String[] args) throws Exception {
		SmartBridge sb = new SmartBridge(args);
		sb.run();
	}

}
