package com.rjj.controller;

import android.text.TextUtils;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
 

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.ref.WeakReference;
import java.net.InetSocketAddress;
import java.net.Socket;

import android.app.Activity;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class FullscreenActivity extends Activity implements OnClickListener {

	private EditText ipEditText;
	private EditText portEditText;
	private Button led1Button;
	private Button led2Button;
	private Button led3Button;
	private Button relay1Button;
	private Button relay2Button;
	private Button relay3Button;
	private TextView receiveTv;
	private Button connectButton;
	
	private boolean isRun = true;
	private boolean isOpenLed1 = false;
	private boolean isOpenLed2 = false;
	private boolean isOpenLed3 = false;
	private boolean isOpenRelay1 = false;
	private boolean isOpenRelay2 = false;
	private boolean isOpenRelay3 = false;
	
	private Socket clientSocket;
	private Handler mHandler;
	private InputStream is;
	private OutputStream os;
	private StringBuilder receiveAllStr;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_fullscreen);
	    this.mHandler = new MyHandler(this);
	    this.clientSocket = new Socket();
	    this.receiveAllStr = new StringBuilder();
		initView();
	}
	
	protected void onDestroy()
	  {
	    super.onDestroy();
	    this.isRun = false;
	    try
	    {
	      closeRes();
	      return;
	    }
	    catch (IOException localIOException)
	    {
	      localIOException.printStackTrace();
	    }
	  }

	  protected void onPause()
	  {
	    super.onPause();
	    this.isRun = false;
	  }

	  protected void onResume()
	  {
	    super.onResume();
	    this.isRun = true;
	  }
	 private void changeConnectState(int paramInt)
	  {
		  runOnUiThread(new Runnable()
	    {
	      public void run()
	      {
	    	if((connectButton.getText().toString())==(FullscreenActivity.this.getText(R.string.disconnect)))
	    		FullscreenActivity.this.connectButton.setText(FullscreenActivity.this.getText(R.string.connect));
	    	else {
	    		FullscreenActivity.this.connectButton.setText(FullscreenActivity.this.getText(R.string.disconnect));
			}
	    	FullscreenActivity.this.connectButton.setTextColor(-1);
	    	FullscreenActivity.this.connectButton.setTextSize(15.0F);
	      }
	    });
	  }

	 private void closeRes()
	    throws IOException{
	    if (this.os != null){
	      this.os.close();
	      this.os = null;
	    }
	    if (this.is != null){
	      this.is.close();
	      this.is = null;
	    }
	    if (this.clientSocket == null)
	      return;
	    this.clientSocket.close();
	    this.clientSocket = null;
	  }
	
	  private Drawable getDrawableFromResId(int paramInt)
	  {
	    return getResources().getDrawable(paramInt);
	  }
	  
	  private void setLedBtnCloseBackground(Button paramButton)
	  {
	    paramButton.setBackground(getResources().getDrawable(R.drawable.led_dark));
	  }

	  private void setLedBtnOpenBackground(Button paramButton, int paramInt)
	  {
	    paramButton.setBackground(getResources().getDrawable(paramInt));
	  }
	  
	  private void initView()
	  {
	    this.connectButton = (Button)findViewById(R.id.connectBtn);
	    this.ipEditText = (EditText)findViewById(R.id.ip_et);
	    this.portEditText = (EditText)findViewById(R.id.port_et);
	    this.led1Button = ((Button)this.findViewById(R.id.led1_button));
	    this.led2Button = ((Button)this.findViewById(R.id.led2_button));
	    this.led3Button = ((Button)this.findViewById(R.id.led3_button));
	    this.relay1Button = ((Button)this.findViewById(R.id.relay1_button));
	    this.relay2Button = ((Button)this.findViewById(R.id.relay2_button));
	    this.relay3Button = ((Button)this.findViewById(R.id.relay3_button));
	    this.receiveTv = (TextView)findViewById(R.id.receiveTextView);
	    
	    this.connectButton.setOnClickListener(this);
	    this.led1Button.setOnClickListener(this);
	    this.led2Button.setOnClickListener(this);
	    this.led3Button.setOnClickListener(this);
	    this.relay1Button.setOnClickListener(this);
	    this.relay2Button.setOnClickListener(this);
	    this.relay3Button.setOnClickListener(this);
	    
	    this.ipEditText.setText("192.168.4.1");
	    this.portEditText.setText("5000");
	    
	    receiveTv.setMovementMethod(ScrollingMovementMethod.getInstance());  
	  
	  }

	  private void requestRemoteServer(String paramString, int paramInt)
	  {
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				try
		        {
 			  
		          FullscreenActivity.this.clientSocket.connect(new InetSocketAddress(
		        		 ipEditText.getText().toString(),
		        		  Integer.parseInt(portEditText.getText().toString())));
		          FullscreenActivity.this.os = FullscreenActivity.this.clientSocket.getOutputStream();
		          FullscreenActivity.this.is = FullscreenActivity.this.clientSocket.getInputStream();
		          FullscreenActivity.this.changeConnectState(R.string.disconnect);
		          new FullscreenActivity.ReceiveMsgThread().start();
		          return;
		        }
		        catch (IOException localIOException)
		        {
		          localIOException.printStackTrace();
		          FullscreenActivity.this.clientSocket = null;
		          Message localMessage = Message.obtain();
		          localMessage.what = 2;
		          FullscreenActivity.this.mHandler.sendMessage(localMessage);
		        }
		      }
		    }).start(); 
				
	  }
	  
	  private byte[] transformDataToByteArray(String paramString)
			    throws IOException
	  {
	    ByteArrayOutputStream localByteArrayOutputStream = new ByteArrayOutputStream();
	    new DataOutputStream(localByteArrayOutputStream).writeBytes(paramString);
	    return localByteArrayOutputStream.toByteArray();
	  }

	  public boolean isConnected()
	  {
	    return ((this.clientSocket != null) && (this.clientSocket.isConnected()));
	  }
	@Override
	public void onClick(View paramView) {
		switch (paramView.getId())
	    {
	    case R.id.connectBtn:
		    String str1 = this.ipEditText.getText().toString().trim();
		    String str2 = this.portEditText.getText().toString().trim();
		    if ((TextUtils.isEmpty(str1)) || (TextUtils.isEmpty(str2)))
		    {
		      AppUtils.showToast(this, "请输入ip或端口号！");
		      return;
		    }
		    if (!(TextUtils.isDigitsOnly(str2)))
		    {
		      AppUtils.showToast(this, "请输入正确的端口号！");
		      return;
		    }
		    int i = Integer.valueOf(str2).intValue();
		    if (isConnected())
		    {
		      this.isRun = false;
		      changeConnectState(R.string.disconnect);
		      try
		      {
		        this.clientSocket.close();
		        this.clientSocket = null;
		        return;
		      }
		      catch (IOException localIOException)
		      {
		        localIOException.printStackTrace();
		        return;
		      }
		    }
		    this.isRun = true;
		    if (this.clientSocket == null)
		      this.clientSocket = new Socket();
		   requestRemoteServer(str1, i);
	       break;
	    case R.id.led1_button:
    	  if (this.isOpenLed1)
	      {
    		 
	        //this.sendMsg("ESPGLED1");	    		 
	        this.isOpenLed1 = false;
	        setLedBtnCloseBackground(this.led1Button);
	        return;
	      }
	      this.sendMsg("ESPKLED1");
	      this.isOpenLed1 = true;
	      setLedBtnOpenBackground(this.led1Button, R.drawable.led_red);
	      break;
	    case R.id.led2_button:
	      if (this.isOpenLed2)
	      {
	        this.sendMsg("ESPGLED2");
	        this.isOpenLed2 = false;
	        setLedBtnCloseBackground(this.led2Button);
	        return;
	      }
	      this.sendMsg("ESPKLED2");
	      this.isOpenLed2 = true;
	      setLedBtnOpenBackground(this.led2Button, R.drawable.led_green);
	      break;
	    case R.id.led3_button:
	      if (this.isOpenLed3)
	      {
	        this.sendMsg("ESPGLED3");
	        this.isOpenLed3 = false;
	        setLedBtnCloseBackground(this.led3Button);
	        return;
	      }
	      this.sendMsg("ESPKLED3");
	      this.isOpenLed3 = true;
	      setLedBtnOpenBackground(this.led3Button, R.drawable.led_yellow);
	      break;
	    case R.id.relay1_button:
	    	if (this.isOpenRelay1)
		      {
		        this.sendMsg("ESPGJDQ1");
		        this.isOpenRelay1 = false;
		        setLedBtnOpenBackground(this.relay1Button, R.drawable.relayclose);
		        return;
		      }
		      this.sendMsg("ESPKJDQ1");
		      this.isOpenRelay1 = true;
		      setLedBtnOpenBackground(this.relay1Button, R.drawable.relayopen);
		      break;
	    case R.id.relay2_button:
	    	if (this.isOpenRelay2)
		      {
		        this.sendMsg("ESPGJDQ2");
		        this.isOpenRelay2 = false;
		        setLedBtnOpenBackground(this.relay2Button, R.drawable.relayclose);
		        return;
		      }
		      this.sendMsg("ESPKJDQ2");
		      this.isOpenRelay2 = true;
		      setLedBtnOpenBackground(this.relay2Button, R.drawable.relayopen);
		      break;
	    case R.id.relay3_button:
	    	if (this.isOpenRelay3)
		      {
		        this.sendMsg("ESPGJDQ3");
		        this.isOpenRelay3 = false;
		        setLedBtnOpenBackground(this.relay3Button, R.drawable.relayclose);
		        return;
		      }
		      this.sendMsg("ESPKJDQ3");
		      this.isOpenRelay3 = true;
		      setLedBtnOpenBackground(this.relay3Button, R.drawable.relayopen);
		      break;
        default:
            break;
    }
}
	
	

	  @SuppressWarnings("null")
	public void sendMsg(String paramString)
	  {
	    if (FullscreenActivity.this.os == null)
	      return;	  
	    try {
	    	FullscreenActivity.this.os.write(transformDataToByteArray(paramString));
	    	this.os.flush();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}		   	 	 
	    return;
	    
	  }

	  private static class MyHandler extends Handler
	  {
	    private final WeakReference<FullscreenActivity> dCActivityWReference;

	    public MyHandler(FullscreenActivity paramDeviceControlActivity)
	    {
	      this.dCActivityWReference = new WeakReference(paramDeviceControlActivity);
	    }

	    public void handleMessage(Message paramMessage)
	    {
	      super.handleMessage(paramMessage);
	      FullscreenActivity localDeviceControlActivity = (FullscreenActivity)this.dCActivityWReference.get();
	      String str = null;
	      if (paramMessage.what == 1)
	      {
	        str = (String)paramMessage.obj;
	        if (!str.isEmpty()) {
	    		localDeviceControlActivity.receiveAllStr.append(str + "\n");       
	   	        localDeviceControlActivity.receiveTv.setText(localDeviceControlActivity.receiveAllStr.toString());	
	    	  } 
	      }
	      else {
			return;
		}
 
	  }
	  }

	  class ReceiveMsgThread extends Thread
	  {
	    public void run()
	    {
	      while (true)
	      {
	        if (!(FullscreenActivity.this.isRun))
	          return;
	        try
	        {
	          if ((FullscreenActivity.this.is != null) && (FullscreenActivity.this.isConnected()));
	          ByteArrayOutputStream localByteArrayOutputStream = new ByteArrayOutputStream();
	          byte[] arrayOfByte = new byte[20];
	          int i = FullscreenActivity.this.is.read(arrayOfByte);
	          if (i != -1)
	            localByteArrayOutputStream.write(arrayOfByte, 0, i);
	          localByteArrayOutputStream.flush();
	          if ((FullscreenActivity.this.clientSocket == null) || (!(FullscreenActivity.this.clientSocket.isClosed())));
	          String str = localByteArrayOutputStream.toString();
	          if (!(TextUtils.isEmpty(str)));
	          Message localMessage = Message.obtain();
	          localMessage.what = 1;
	          localMessage.obj = str;
	          FullscreenActivity.this.mHandler.sendMessage(localMessage);
	        }
	        catch (IOException localIOException)
	        {
	          localIOException.printStackTrace();
	        }
	      }
	    }
	  }

}
