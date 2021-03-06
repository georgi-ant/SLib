/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package slib.platform.android.camera;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;

import slib.platform.android.Logger;
import slib.platform.android.SlibActivity;
import slib.platform.android.ui.UiThread;

public class TakePhoto {

	static Uri currentPhotoPath = null;

	public static void takePhoto(final Activity context, final String outputFilePath) {

		if (!(UiThread.isUiThread())) {
			UiThread.post(new Runnable() {
				public void run() {
					takePhoto(context, outputFilePath);
				}
			});
			return;
		}

		try {

			if (outputFilePath == null || outputFilePath.isEmpty()) {

				String path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).getPath();
				String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
				String fileName = "Photo_" + timeStamp;
				File file = File.createTempFile(
						fileName,
						".jpg",
						new File(path)
				);
				if (file == null) {
					onFailure();
					return;
				}
				file.deleteOnExit();
				currentPhotoPath = Uri.fromFile(file);
			} else {
				String path;
				if (outputFilePath.charAt(0) == '/') {
					path = outputFilePath;
				} else {
					path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).getPath() + "/" + outputFilePath;
				}
				int index = path.lastIndexOf('/');
				if (index < 0) {
					onFailure();
					return;
				}
				String dirPath = path.substring(0, index);
				File dir = new File(dirPath);
				if (!dir.exists() || !dir.isDirectory()) {
					onFailure();
					return;
				}
				currentPhotoPath = Uri.fromFile(new File(path));
			}

			Intent takePhotoIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
			if (takePhotoIntent.resolveActivity(context.getPackageManager()) != null) {
				takePhotoIntent.putExtra(MediaStore.EXTRA_OUTPUT, currentPhotoPath);
				context.startActivityForResult(takePhotoIntent, SlibActivity.REQUEST_IMAGE_CAPTURE);
			} else {
				onFailure();
			}

		} catch (Exception e) {
			Logger.exception(e);
			onFailure();
		}
	}

	public static void onResult(Activity activity, int resultCode, Intent data) {
		if (resultCode == SlibActivity.RESULT_OK && currentPhotoPath != null) {
			final String path = currentPhotoPath.getPath();
			new Thread(new Runnable() {
				public void run() {
					try {
						int orientation = 0;
						int i = 0;
						for (i = 0; i < 500; i++) {
							if (new File(path).exists()) {
								break;
							}
							try {
								Thread.sleep(10);
							} catch (Exception e) {
							}
						}
						if (i == 300) {
							onFailure();
							return;
						}
						onSuccess(path);
					} catch (Exception e) {
						onFailure();
						Logger.exception(e);
					}
				}
			}).start();
		} else if (resultCode == SlibActivity.RESULT_CANCELED) {
			onCanceled();
		}
	}

	private static native void onSuccess(String path);
	private static native void onFailure();
	private static native void onCanceled();

}