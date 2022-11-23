package com.smartbridge.com.smartbridge.maven.eclipse;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.text.AttributeSet.ColorAttribute;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ApplicationViewImpl implements ApplicationView {
	
	private static final Dimension WINDOW_DIMENSION = new Dimension(1024, 768);
	
	private final JFrame frame = new JFrame("Smart Bridge");
	
	private final JToggleButton manual = new JToggleButton("MANUAL");
	private final JTextField bridgeStatus = new JTextField();
	private final JTextField waterLevel = new JTextField();
	private final JTextField ledStatus = new JTextField();
	private final JSlider anglePicker = new JSlider();
	private final JPanel graphPanel = new JPanel();
	
	private ApplicationViewObserver observer;
	
	private TimeSeries series;
	
	public ApplicationViewImpl() {
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setSize(WINDOW_DIMENSION);
		
		JPanel mainPanel = new JPanel();
		frame.getContentPane().add(mainPanel, BorderLayout.CENTER);
		mainPanel.setLayout(null);
		
		JLabel lightLabel = new JLabel("SMART LIGHT: ");
		lightLabel.setFont(new Font("Tahoma", Font.BOLD, 18));
		lightLabel.setBounds(476, 607, 149, 31);
		mainPanel.add(lightLabel);
		
		JLabel waterLabel = new JLabel("WATER LEVEL:");
		waterLabel.setFont(new Font("Tahoma", Font.BOLD, 18));
		waterLabel.setBounds(10, 649, 134, 31);
		mainPanel.add(waterLabel);
		
		JLabel bridgeLabel = new JLabel("BRIDGE STATUS:");
		bridgeLabel.setFont(new Font("Tahoma", Font.BOLD, 18));
		bridgeLabel.setBounds(10, 607, 163, 31);
		mainPanel.add(bridgeLabel);
		 
		bridgeStatus.setEditable(false);
		bridgeStatus.setBounds(168, 610, 149, 31);
		bridgeStatus.setColumns(10);
		mainPanel.add(bridgeStatus);
		
		waterLevel.setEditable(false);
		waterLevel.setColumns(10);
		waterLevel.setBounds(168, 649, 149, 31);
		mainPanel.add(waterLevel);
		
		ledStatus.setEditable(false);
		ledStatus.setColumns(10);
		ledStatus.setBounds(619, 607, 149, 31);
		mainPanel.add(ledStatus);
		
		manual.setFont(new Font("Tahoma", Font.BOLD, 14));
		manual.setSelected(false);
		manual.setBounds(836, 505, 142, 45);
		manual.setEnabled(false);
		mainPanel.add(manual);
		
		anglePicker.setPaintTicks(true);
		anglePicker.setPaintLabels(true);
		anglePicker.setOrientation(SwingConstants.VERTICAL);
		anglePicker.setMajorTickSpacing(45);
		anglePicker.setMaximum(180);
		anglePicker.setEnabled(false);
		anglePicker.setBounds(836, 149, 142, 343);
		mainPanel.add(anglePicker);
		
		JLabel angleLabel = new JLabel("VALVE ANGLE:");
		angleLabel.setHorizontalAlignment(SwingConstants.CENTER);
		angleLabel.setFont(new Font("Tahoma", Font.BOLD, 18));
		angleLabel.setBounds(836, 101, 142, 37);
		mainPanel.add(angleLabel);
		
		
		graphPanel.setBounds(10, 50, 800, 500);
		
		
		manual.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				if(bridgeStatus.getText().equals("ALARM") || bridgeStatus.getText().equals("MANUAL_ALARM")) {
					if(manual.isSelected()) {
						observer.sendMsg("MANUAL_ON");
					} else {
						observer.sendMsg("MANUAL_OFF");
						manual.setEnabled(false);
						anglePicker.setEnabled(false);
					}
				}
			}
		});
		
		anglePicker.addChangeListener(new ChangeListener() {
			
			@Override
			public void stateChanged(ChangeEvent e) {
				if(bridgeStatus.getText().equals("ALARM") || bridgeStatus.getText().equals("MANUAL_ALARM")) {
					System.out.println(anglePicker.getValue());
					observer.sendAngle(anglePicker.getValue());
				}
			}
		});
		
		this.series = new TimeSeries("WaterLevel");
		final TimeSeriesCollection dataset = new TimeSeriesCollection(this.series);
		final JFreeChart chart = createChart(dataset);
		chart.setBackgroundPaint(Color.WHITE);
		final ChartPanel chartPanel = new ChartPanel(chart);
		graphPanel.add(chartPanel);
		chartPanel.setPreferredSize(new java.awt.Dimension(800, 500));
		mainPanel.add(graphPanel);
	}
	
	@Override
	public void writeLedStatus(String msg) {
		ledStatus.setText(msg);
	}

	@Override
	public void writeFSMStatus(String msg, float wl) {
		manual.setEnabled(msg.equals("ALARM") || msg.equals("MANUAL_ALARM"));
		anglePicker.setEnabled(msg.equals("ALARM") || msg.equals("MANUAL_ALARM"));
		bridgeStatus.setText(msg);
		waterLevel.setText(Float.toString(wl));
		
        this.series.add(new Millisecond().previous(), wl);
	}

	@Override
	public void start() {
		frame.setVisible(true);
	}

	@Override
	public void setObserver(ApplicationViewObserver observer) {
		this.observer = observer;
	}
	
	private JFreeChart createChart(final XYDataset dataset) {
        final JFreeChart result = ChartFactory.createTimeSeriesChart(
            "Water Level Trend",
            "Time",
            "Water Level",
            dataset,
            true,
            true,
            false
        );

        final XYPlot plot = result.getXYPlot();

        plot.setBackgroundPaint(new Color(0xffffe0));
        plot.setDomainGridlinesVisible(true);
        plot.setDomainGridlinePaint(Color.lightGray);
        plot.setRangeGridlinesVisible(true);
        plot.setRangeGridlinePaint(Color.lightGray);

        ValueAxis xaxis = plot.getDomainAxis();
        xaxis.setAutoRange(true);

        //Domain axis would show data of 60 seconds for a time
        xaxis.setFixedAutoRange(120000.0);  // 60 seconds
        xaxis.setVerticalTickLabels(true);

        ValueAxis yaxis = plot.getRangeAxis();
        yaxis.setRange(0.0, 300.0);

        return result;
    }
}
