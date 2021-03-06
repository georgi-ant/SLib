/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_UI_RESOURCE
#define CHECKHEADER_SLIB_UI_RESOURCE

#include "definition.h"

#include "../core/resource.h"

#include "menu.h"
#include "event.h"
#include "view.h"
#include "window.h"
#include "mobile_app.h"

namespace slib
{

	class UIResource
	{
	public:
		static sl_ui_len getScreenWidth();
		
		static void setScreenWidth(sl_ui_len width);
		
		static sl_ui_len getScreenHeight();
		
		static void setScreenHeight(sl_ui_len height);
		
		static sl_ui_len getScreenMinimum();
		
		static sl_ui_len getScreenMaximum();
		
		static void updateDefaultScreenSize();
		
	};
	
#define SLIB_DECLARE_MENU_BEGIN(NAME) \
	class NAME : public slib::Referable { \
	public: \
		static const NAME* get(); \
		NAME(); \
		slib::Ref<slib::Menu> root; \
		slib::Ref<slib::Menu> root_menu;
	
#define SLIB_DECLARE_SUBMENU(NAME) \
	slib::Ref<slib::Menu> NAME##_menu; \
	slib::Ref<slib::MenuItem> NAME;
	
#define SLIB_DECLARE_MENU_ITEM(NAME) \
		slib::Ref<slib::MenuItem> NAME;
	
#define SLIB_DECLARE_MENU_SEPARATOR(NAME) \
		slib::Ref<slib::MenuItem> NAME;
	
#define SLIB_DECLARE_MENU_END };
	
	
#define SLIB_DEFINE_MENU_BEGIN(NAME) \
	const NAME* NAME::get() { \
		SLIB_SAFE_STATIC(NAME, ret); \
		if (SLIB_SAFE_STATIC_CHECK_FREED(ret)) { \
			return sl_null; \
		} \
		return &ret; \
	} \
	NAME::NAME() { \
		root = root_menu = slib::Menu::create(); \
		if (root.isNull()) return;
	
#define SLIB_DEFINE_SUBMENU(PARENT, NAME, ...) \
	NAME##_menu = slib::Menu::create(); \
	if (NAME##_menu.isNull()) return; \
	NAME = PARENT##_menu->addSubmenu(NAME##_menu, __VA_ARGS__);
	
#define SLIB_DEFINE_MENU_ITEM(PARENT, NAME, ...) \
	NAME = PARENT##_menu->addMenuItem(__VA_ARGS__);
	
#define SLIB_DEFINE_MENU_SEPARATOR(PARENT, NAME) \
	NAME = PARENT##_menu->addSeparator();
	
#define SLIB_DEFINE_MENU_SEPARATOR_NONAME(PARENT) \
	PARENT##_menu->addSeparator();
	
#define SLIB_DEFINE_MENU_END }
	
#define SLIB_DECLARE_UILAYOUT_BEGIN(NAME, BASE_CLASS) \
	class NAME : public BASE_CLASS \
	{ \
		SLIB_DECLARE_OBJECT \
	public: \
		NAME(sl_real sp = 1); \
	protected: \
		void initialize(); \
		void layoutViews(sl_ui_len width, sl_ui_len height) override; \
	public:
	
#define SLIB_DECLARE_UILAYOUT_END \
	};
	
#define SLIB_DEFINE_UILAYOUT(NAME, BASE_CLASS) \
	SLIB_DEFINE_OBJECT(NAME, BASE_CLASS) \
	NAME::NAME(sl_real sp): BASE_CLASS(sp) \
	{ \
		SLIB_REFERABLE_CONSTRUCTOR \
		initialize(); \
		setInitialized(); \
		slib::UISize size = getContentSize(); \
		if (size.x > 0 && size.y > 0) { \
			layoutViews(size.x, size.y); \
		} \
	}
	
	class UILayoutResource
	{
	public:
		UILayoutResource(sl_real sp = 1);
		
		virtual ~UILayoutResource();

	public:
		Ref<View> getContent();
		
		sl_real getScaledPixel();
		
		void setScaledPixel(sl_real sp);
		
	protected:
		virtual void layoutViews(sl_ui_len width, sl_ui_len height) = 0;
		
	protected:
		void _layoutViews_safe(sl_ui_len width, sl_ui_len height);
		
		sl_bool isInitialized();
		
		void setInitialized();
		
	protected:
		View* m_contentView;
		Ref<View> m_contentViewRef;
		
		sl_real m_sp;
		
		sl_int32 m_countRecursiveLayout;
		sl_bool m_flagInitialized;
		
	};
	
#define SLIB_DECLARE_WINDOW_LAYOUT_BEGIN(NAME) \
	SLIB_DECLARE_UILAYOUT_BEGIN(NAME, slib::WindowLayoutResource)
	
#define SLIB_DECLARE_WINDOW_LAYOUT_END \
	SLIB_DECLARE_UILAYOUT_END
	
#define SLIB_DEFINE_WINDOW_LAYOUT(NAME) \
	SLIB_DEFINE_UILAYOUT(NAME, slib::WindowLayoutResource)
	
	
	class WindowLayoutResource : public Window, public UILayoutResource
	{
		SLIB_DECLARE_OBJECT

	public:
		WindowLayoutResource(sl_real sp = 1);
		
		~WindowLayoutResource();

	public:
		UISize getContentSize();
		
	public:
		void dispatchResize(sl_ui_len width, sl_ui_len height) override;
		
	protected:
		void _layoutViews_safe();
		
	};
	
#define SLIB_DECLARE_VIEW_LAYOUT_BEGIN(NAME) \
	SLIB_DECLARE_UILAYOUT_BEGIN(NAME, slib::ViewLayoutResource)
	
#define SLIB_DECLARE_VIEW_LAYOUT_END \
	SLIB_DECLARE_UILAYOUT_END
	
#define SLIB_DEFINE_VIEW_LAYOUT(NAME) \
	SLIB_DEFINE_UILAYOUT(NAME, slib::ViewLayoutResource)
	
	class ViewLayoutResource : public ViewGroup, public UILayoutResource
	{
		SLIB_DECLARE_OBJECT
	public:
		ViewLayoutResource(sl_real sp = 1);
		
		~ViewLayoutResource();

	public:
		UISize getContentSize();
		
	public:
		void dispatchResize(sl_ui_len width, sl_ui_len height) override;
		
	};
	
	
#define SLIB_DECLARE_PAGE_LAYOUT_BEGIN(NAME) \
	SLIB_DECLARE_UILAYOUT_BEGIN(NAME, slib::PageLayoutResource)
	
#define SLIB_DECLARE_PAGE_LAYOUT_END \
	SLIB_DECLARE_UILAYOUT_END
	
#define SLIB_DEFINE_PAGE_LAYOUT(NAME) \
	SLIB_DEFINE_UILAYOUT(NAME, slib::PageLayoutResource)
	
	class PageLayoutResource : public ViewPage, public UILayoutResource
	{
		SLIB_DECLARE_OBJECT

	public:
		PageLayoutResource(sl_real sp = 1);
		
		~PageLayoutResource();

	public:
		UISize getContentSize();
		
	public:
		void dispatchResize(sl_ui_len width, sl_ui_len height) override;
		
	};
	
	
	class Button;
	class LabelView;
	class CheckBox;
	class RadioButton;
	class RadioGroup;
	class EditView;
	class PasswordView;
	class TextArea;
	class ImageView;
	class SelectView;
	class ScrollView;
	class LinearView;
	class ListView;
	class ListReportView;
	class RenderView;
	class TabView;
	class TreeView;
	class WebView;
	class SplitView;
	class ProgressBar;
	class Slider;
	class PickerView;
	class ViewPager;
	class VideoView;

}

#endif
