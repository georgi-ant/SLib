/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package slib.platform.android.ui.view;

import slib.platform.android.Logger;
import slib.platform.android.ui.Graphics;
import slib.platform.android.ui.UiThread;
import slib.platform.android.ui.window.UiWindow;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;
import android.os.Build;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.AbsoluteLayout;
import android.widget.Button;
import android.widget.FrameLayout;

@SuppressWarnings("deprecation")
public class UiView {
	
	private UiView() {
	}

	public static Context getContext(View view)
	{
		return view.getContext();
	}
	
	public static void setInstance(View view, long instance) {
		if (view instanceof IView) {
			((IView)view).setInstance(instance);
		}
	}
	
	public static void freeView(View view) {
		try {
			setInstance(view, 0);
			if (view instanceof UiGLView) {
				UiGLView.removeView(view);
			}
		} catch (Exception e) {
			Logger.exception(e);
		}
	}

	public static View createGeneric(Context context) {
		try {
			UiGenericView view = new UiGenericView(context);
			return view;
		} catch (Exception e) {
			Logger.exception(e);
		}
		return null;
	}
	
	public static View createGroup(Context context) {
		try {
			UiGroupView view = new UiGroupView(context);
			return view;
		} catch (Exception e) {
			Logger.exception(e);
		}
		return null;
	}
	
	public static void setFocus(final View view) {
		try {
			if (!(UiThread.isUiThread())) {
				view.post(new Runnable() {
					public void run() {
						setFocus(view);
					}
				});
			} else {
				view.setFocusable(true);
				view.setFocusableInTouchMode(true);
				view.requestFocus();
			}
		} catch (Exception e) {
			Logger.exception(e);
		}
	}

	public static void invalidate(View view) {
		if (UiThread.isUiThread()) {
			view.invalidate();
		} else {
			view.postInvalidate();			
		}
	}
	
	public static void invalidateRect(View view, int left, int top, int right, int bottom) {
		if (UiThread.isUiThread()) {
			view.invalidate(left, top, right, bottom);			
		} else {
			view.postInvalidate(left, top, right, bottom);			
		}
	}
	
	public static Rect getFrame(View view)
	{
		if (view instanceof IView) {
			return ((IView)view).getUIFrame();
		} else {
			Rect ret = new Rect();
			ret.left = view.getLeft();
			ret.top = view.getTop();
			ret.right = view.getRight();
			ret.bottom = view.getBottom();
			return ret;
		}
	}

	public static boolean setFrame(final View view, int left, int top, int right, int bottom) {

		if (view instanceof UiWindow) {
			return true;
		}

		if (!(UiThread.isUiThread())) {
			final int l = left;
			final int r = right;
			final int t = top;
			final int b = bottom;
			view.post(new Runnable() {
				public void run() {
					setFrame(view, l, t, r, b);
				}
			});
			return true;
		}

		if (right < left) {
			right = left;
		}
		if (bottom < top) {
			bottom = top;
		}
		if (view instanceof Button) {
			top -= 5;
			bottom += 5;
		}
		int width = right - left;
		int height = bottom - top;

		try {
			if (view instanceof IView) {
				((IView)view).setUIFrame(left, top, right, bottom);
			}
			ViewGroup.LayoutParams _params = view.getLayoutParams();
			if (_params != null) {
				if (_params instanceof FrameLayout.LayoutParams) {
					FrameLayout.LayoutParams params = (FrameLayout.LayoutParams)_params;
					params.leftMargin = left;
					params.topMargin = top;
					params.width = width;
					params.height = height;
					view.setLayoutParams(params);
				} else if (_params instanceof AbsoluteLayout.LayoutParams) {
					AbsoluteLayout.LayoutParams params = (AbsoluteLayout.LayoutParams)_params;
					params.x = left;
					params.y = top;
					params.width = width;
					params.height = height;
					view.setLayoutParams(params);
				}
				if (UiThread.isUiThread()) {
					view.layout(left, top, right, bottom);
				}
			}
			return true;
		} catch (Exception e) {
			Logger.exception(e);
		}
		return false;
	}

	static final float EPSILON = 0.000001f;
	public static void setTransform(final View view, final float _tx, final float _ty, final float rotate, final float sx, final float sy, final float ax, final float ay) {
		if (UiThread.isUiThread()) {
			float r = (float)(rotate * 180 / Math.PI);
			if (Math.abs(r - view.getRotation()) > EPSILON) {
				view.setRotation(r);
			}
			if (Math.abs(sx - view.getScaleX()) > EPSILON) {
				view.setScaleX(sx);
			}
			if (Math.abs(sy - view.getScaleY()) > EPSILON) {
				view.setScaleY(sy);
			}
			float tx = _tx;
			float ty = _ty;
			if (Math.abs(ax) > EPSILON || Math.abs(ay) > EPSILON) {
				double cr = Math.cos(rotate);
				double sr = Math.sin(rotate);
				tx = (float)((- ax * cr + ay * sr) * sx + tx + ax);
				ty = (float)((- ax * sr - ay * cr) * sy + ty + ay);
			}
			if (Math.abs(tx - view.getTranslationX()) > EPSILON) {
				view.setTranslationX(tx);
			}
			if (Math.abs(ty - view.getTranslationY()) > EPSILON) {
				view.setTranslationY(ty);
			}
		} else {
			view.post(new Runnable() {
				public void run() {
					setTransform(view, _tx, _ty, rotate, sx, sy, ax, ay);
				}
			});
		}
	}
	
	public static boolean isVisible(View view) {
		return view.getVisibility() == View.VISIBLE;
	}
	
	public static void setVisible(final View view, final boolean flag) {
		if (UiThread.isUiThread()) {
			if (flag) {
				view.setVisibility(View.VISIBLE);
			} else {
				view.setVisibility(View.INVISIBLE);
			}
		} else {
			view.post(new Runnable() {
				public void run() {
					setVisible(view, flag);
				}
			});
		}
	}
	
	public static boolean isEnabled(View view) {
		return view.isEnabled();
	}
	
	public static void setEnabled(final View view, final boolean flag) {
		if (UiThread.isUiThread()) {
			view.setEnabled(flag);
		} else {
			view.post(new Runnable() {
				public void run() {
					view.setEnabled(flag);
				}
			});
		}		
	}

	public static void setAlpha(final View view, final float alpha) {
		if (UiThread.isUiThread()) {
			view.setAlpha(alpha);
		} else {
			view.post(new Runnable() {
				public void run() {
					view.setAlpha(alpha);
				}
			});
		}
	}

	public static void setClipping(final View view, final boolean flag) {
		if (view instanceof ViewGroup) {
			if (UiThread.isUiThread()) {
				((ViewGroup)view).setClipChildren(flag);
			} else {
				view.post(new Runnable() {
					public void run() {
						((ViewGroup)view).setClipChildren(flag);
					}
				});
			}			
		}
	}

	public static void setDrawing(final View view, final boolean flag) {
		if (UiThread.isUiThread()) {
			view.setWillNotDraw(!flag);
		} else {
			view.post(new Runnable() {
				public void run() {
					view.setWillNotDraw(!flag);
				}
			});
		}			
	}
	
	public static void setLayered(final View view) {
		try {
			view.setLayerType(View.LAYER_TYPE_HARDWARE, null);			
		} catch (Exception e) {
			Logger.exception(e);
		}
	}
	
	public static Point convertCoordinateFromScreenToView(View view, int x, int y) {
		Point ret = new Point();
		int[] location = new int[2];
		view.getLocationOnScreen(location);
		ret.x = x - location[0];
		ret.y = y - location[1];
		return ret;
	}
	
	public static Point convertCoordinateFromViewToScreen(View view, int x, int y) {
		Point ret = new Point();
		int[] location = new int[2];
		view.getLocationOnScreen(location);
		ret.x = location[0] + x;
		ret.y = location[1] + y;
		return ret;
	}
	
	public static void addChild(View _group, View view) {
		try {
			if (_group instanceof ViewGroup) {
				ViewGroup group = (ViewGroup)_group;
				ViewParent parent = view.getParent();
				if (parent == group) {
					return;
				}
				if (parent != null) {
					if (parent instanceof ViewGroup) {
						((ViewGroup)parent).removeView(view);
					} else {
						return;
					}
				}
				if (view instanceof IView) {
					ViewGroup.LayoutParams params = view.getLayoutParams();
					if (params == null) {
						Rect rc = ((IView)view).getUIFrame();
						if (_group instanceof AbsoluteLayout) {
							params = new AbsoluteLayout.LayoutParams(rc.width(), rc.height(), rc.left, rc.top);
						} else if (_group instanceof FrameLayout) {
							FrameLayout.LayoutParams fl = new FrameLayout.LayoutParams(rc.width(), rc.height());
							fl.leftMargin = rc.left;
							fl.topMargin = rc.top;
							params = fl;
						}
						if (params != null) {
							view.setLayoutParams(params);
						}
					}
				}
				group.addView(view);
			}
		} catch (Throwable e) {
			Logger.exception(e);
		}
	}

	public static void removeChild(View _group, View view) {
		try {
			if (_group instanceof ViewGroup) {
				ViewGroup group = (ViewGroup)_group;
				ViewParent parent = view.getParent();
				if (parent == group) {
					group.removeView(view);
				}
			}
		} catch (Throwable e) {
			Logger.exception(e);
		}
	}
	
	public static void bringToFront(final View view) {
		if (!(UiThread.isUiThread())) {
			view.post(new Runnable() {
				public void run() {
					bringToFront(view);
				}
			});
			return;
		}
		try {
			ViewParent parent = view.getParent();
			parent.bringChildToFront(view);
			view.invalidate();
		} catch (Throwable e) {
			Logger.exception(e);
		}
	}

	public static int resolveMeasure(int size, int measureSpec) {
		final int specMode = View.MeasureSpec.getMode(measureSpec);
		final int specSize = View.MeasureSpec.getSize(measureSpec);
		final int result;
		switch (specMode) {
			case View.MeasureSpec.AT_MOST:
				result = size;
				break;
			case View.MeasureSpec.EXACTLY:
				result = specSize;
				break;
			case View.MeasureSpec.UNSPECIFIED:
			default:
				result = size;
		}
		return result;
	}

	static class ViewGestureListener implements UiGestureDetector.GestureListener {

		IView view;

		ViewGestureListener(IView view) {
			this.view = view;
		}

		public void onSwipe(int direction, float posBegin) {
			UiView.onSwipe(view, direction);
		}

		public void onDoubleTap() {
		}
	}

	public static void enableGesture(View view) {
		if (view instanceof IView) {
			if (view instanceof UiGenericView) {
				if (((UiGenericView)view).gestureDetector == null) {
					((UiGenericView)view).gestureDetector = new UiGestureDetector(view.getContext(), new ViewGestureListener((IView)view));
				}
			} else if (view instanceof UiGLView) {
				if (((UiGLView)view).gestureDetector == null) {
					((UiGLView)view).gestureDetector = new UiGestureDetector(view.getContext(), new ViewGestureListener((IView)view));
				}
			} else if (view instanceof UiGroupView) {
				if (((UiGroupView)view).gestureDetector == null) {
					((UiGroupView)view).gestureDetector = new UiGestureDetector(view.getContext(), new ViewGestureListener((IView)view));
				}
			}
		}
	}
	
	// events
	private static native void nativeOnDraw(long instance, Graphics graphics);
	public static void onEventDraw(IView view, Canvas canvas) {
		long instance = view.getInstance();
		if (instance != 0) {
			Graphics graphics = new Graphics(canvas);
			nativeOnDraw(instance, graphics);
		}
	}
	
	private static native boolean nativeOnKeyEvent(long instance, boolean flagDown, int vkey
			, boolean flagControl, boolean flagShift, boolean flagAlt, boolean flagWin, long time);
	@TargetApi(Build.VERSION_CODES.HONEYCOMB)
	public static boolean onEventKey(IView view, boolean flagDown, int keycode, KeyEvent event) {
		long instance = view.getInstance();
		if (instance != 0) {
			boolean ret;
			if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
				ret = nativeOnKeyEvent(
						instance,
						flagDown, keycode,
						event.isCtrlPressed(),
						event.isShiftPressed(),
						event.isAltPressed(),
						event.isMetaPressed(),
						event.getEventTime()
				);
			} else {
				ret = nativeOnKeyEvent(
						instance,
						flagDown,
						keycode,
						false,
						event.isShiftPressed(),
						event.isAltPressed(),
						false,
						event.getEventTime()
				);
			}
			return ret;
		}
		return true;
	}
	
	private static native boolean nativeOnTouchEvent(long instance, int action, UiTouchPoint[] pts, long time);
	
	public static boolean onEventTouch(IView view, MotionEvent event) {
		long instance = view.getInstance();
		if (instance != 0) {
			int action = 0;
			int _action = event.getActionMasked();
			switch (_action) {
			case MotionEvent.ACTION_DOWN:
				action = 0x0301;
				break;
			case MotionEvent.ACTION_MOVE:
			case MotionEvent.ACTION_POINTER_DOWN:
			case MotionEvent.ACTION_POINTER_UP:
				action = 0x0302;
				break;
			case MotionEvent.ACTION_UP:
				action = 0x0303;
				break;
			case MotionEvent.ACTION_CANCEL:
				action = 0x0304;
				break;
			default:
				return false;
			}
			int n = event.getPointerCount();
			if (n > 0) {
				int actionIndex = event.getActionIndex();
				UiTouchPoint[] pts = new UiTouchPoint[n];
				for (int i = 0; i < n; i++) {
					UiTouchPoint pt = new UiTouchPoint();
					pt.x = event.getX(i);
					pt.y = event.getY(i);
					pt.pressure = event.getPressure(i);
					if (_action == MotionEvent.ACTION_DOWN) {
						pt.phase = 1;
					} else if (_action == MotionEvent.ACTION_UP) {
						pt.phase = 2;
					} else if (_action == MotionEvent.ACTION_CANCEL) {
						pt.phase = 3;
					} else {
						if (actionIndex == i) {
							if (_action == MotionEvent.ACTION_POINTER_DOWN) {
								pt.phase = 1;
							} else if (_action == MotionEvent.ACTION_POINTER_UP) {
								pt.phase = 2;
							} else {
								pt.phase = 0;
							}
						} else {
							pt.phase = 0;
						}
					}
					pts[i] = pt;
				}
				return nativeOnTouchEvent(instance, action, pts, event.getEventTime());
			}
		}
		return false;
	}
	
	private static native void nativeOnClick(long instance);
	public static void onEventClick(IView view) {
		long instance = view.getInstance();
		if (instance != 0) {
			nativeOnClick(instance);
		}
	}

	private static native boolean nativeHitTestTouchEvent(long instance, int x, int y);
	public static boolean onHitTestTouchEvent(IView view, int x, int y) {
		long instance = view.getInstance();
		if (instance != 0) {
			return nativeHitTestTouchEvent(instance, x, y);
		}
		return false;
	}

	private static native void nativeOnSwipe(long instance, int type);
	public static void onSwipe(IView view, int type) {
		long instance = view.getInstance();
		if (instance != 0) {
			nativeOnSwipe(instance, type);
		}
	}

}
