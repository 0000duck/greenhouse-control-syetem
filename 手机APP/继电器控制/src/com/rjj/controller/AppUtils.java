package com.rjj.controller;

import android.content.Context;
import android.widget.Toast;

public class AppUtils {

	public static void showToast(Context paramContext, String paramString) {
		Toast.makeText(paramContext, paramString, 1).show();	
	}
	
	public static void showToast(Context paramContext, int paramInt) {
		Toast.makeText(paramContext, paramInt, 1).show();	
	}

}
