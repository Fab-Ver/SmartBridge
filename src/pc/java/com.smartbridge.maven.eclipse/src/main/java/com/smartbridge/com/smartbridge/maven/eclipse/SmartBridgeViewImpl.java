package com.smartbridge.com.smartbridge.maven.eclipse;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowListener;

public class SmartBridgeViewImpl implements SmartBridgeView {

	private static final Dimension WINDOW_DIMENSION = new Dimension(1024, 768);
	private static final double MIN_VALUE = 0.0;
	private static final double MAX_VALUE = 4.0;

	private final JFrame frame = new JFrame("Smart Bridge");
	private final JToggleButton manual = new JToggleButton("MANUAL");
	private final JTextField bridgeStatus = new JTextField();
	private final JTextField waterLevel = new JTextField();
	private final JTextField ledStatus = new JTextField();
	private final JSlider anglePicker = new JSlider();
	private final JPanel graphPanel = new JPanel();

	private boolean remoteControl = false;
	private SmartBridgeObserver observer;
	private final TimeSeries series;

	public SmartBridgeViewImpl() {
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
		anglePicker.setValue(0);
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
				if (bridgeStatus.getText().equals("ALARM") || remoteControl) {
					if (manual.isSelected()) {
						observer.sendMessage("MANUAL_ON");
						anglePicker.setEnabled(true);
						remoteControl = true;
					} else {
						observer.sendMessage("MANUAL_OFF");
						anglePicker.setEnabled(false);
						manual.setEnabled(false);
						remoteControl = false;
					}
				}
			}
		});

		anglePicker.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				JSlider source = (JSlider) e.getSource();
				if (!source.getValueIsAdjusting()) {
					if (remoteControl) {
						observer.sendMessage(Integer.toString(source.getValue()));
					}
				}
			}
		});
		
		frame.
		
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
	public void writeSysStatus(String msg, String wl) {
		if (!remoteControl) {
			manual.setEnabled(msg.equals("ALARM"));
		}
		bridgeStatus.setText(msg);
		waterLevel.setText(wl);
		this.addData(wl);
	}

	@Override
	public void start() {
		frame.setVisible(true);
	}

	@Override
	public void setObserver(SmartBridgeObserver observer) {
		this.observer = observer;
	}

	private void addData(String data) {
		double waterLevel = MAX_VALUE - Double.valueOf(data);
		this.series.addOrUpdate(new Millisecond(), waterLevel);
	}

	private JFreeChart createChart(final XYDataset dataset) {
		final JFreeChart result = ChartFactory.createTimeSeriesChart("Water Level Trend", "Time", "Water Level",
				dataset, true, true, false);

		final XYPlot plot = result.getXYPlot();

		plot.setBackgroundPaint(new Color(0xffffe0));
		plot.setDomainGridlinesVisible(true);
		plot.setDomainGridlinePaint(Color.lightGray);
		plot.setRangeGridlinesVisible(true);
		plot.setRangeGridlinePaint(Color.lightGray);

		ValueAxis xaxis = plot.getDomainAxis();
		xaxis.setAutoRange(true);

		// Domain axis would show data of 3 minutes for a time
		xaxis.setFixedAutoRange(120000.0);
		xaxis.setVerticalTickLabels(true);
		xaxis.setAutoRangeMinimumSize(0.01);

		ValueAxis yaxis = plot.getRangeAxis();
		yaxis.setRange(0.00, 4.50);
		yaxis.setAutoRangeMinimumSize(0.01);

		return result;
	}
}
