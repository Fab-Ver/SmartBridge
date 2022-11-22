package com.smartbridge.com.smartbridge.maven.eclipse;

public class SmartBridge implements ApplicationViewObserver{
	
	private final SerialCommChannel channel;
	private final ApplicationView view;
	
	public SmartBridge(String[] args) throws Exception {
		String comPortName = "";
		
		if(args.length > 1) {
			System.out.println("args: <CommPortName>");
			System.exit(1);
		} else if (args.length == 1) {
			comPortName = args[0];
		} else {
			comPortName = "/";
		}
		
		this.channel = new SerialCommChannel(comPortName,9600);
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		this.view = new ApplicationViewImpl();
		this.view.setObserver(this);
		this.view.start();
	}

	public static void main(String[] args) throws Exception {
		SmartBridge sb = new SmartBridge(args);
		sb.run();
	}
	
	public void run() throws Exception{
		while (true){
			if(channel.isMsgAvailable()) {
				String msg = channel.receiveMsg();
				String[] messages = msg.split(" ");
				if(messages.length == 1) {
					view.writeLedStatus(messages[0]);
				} else if (messages.length == 2 ) {
					view.writeFSMStatus(messages[0],Float.valueOf(messages[1]));
				}
			}
		}
	}

	@Override
	public void sendMsg(String msg) {
		this.channel.sendMsg(msg);
	}

	@Override
	public void sendAngle(int angle) {
		this.channel.sendMsg(Integer.toString(angle));
	}

}
