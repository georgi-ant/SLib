/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_UI_APP
#define CHECKHEADER_SLIB_UI_APP

#include "definition.h"

#include "../core/app.h"

namespace slib
{

	class Window;
	class Menu;
	
	class SLIB_EXPORT UIApp : public Application
	{
		SLIB_DECLARE_OBJECT
		
	public:
		UIApp();
		
		~UIApp();

	public:
		static Ref<UIApp> getApp();
		
	public:
		AppType getAppType() override;
		
		static void quit();
		
		Ref<Window> getMainWindow();
		
		void setMainWindow(const Ref<Window>& window);
		
		// Menu Bar (Mainly used in OSX)
		Ref<Menu> getMenu();
		
		// Menu Bar (Mainly used in OSX)
		void setMenu(const Ref<Menu>& menu);
		
	protected:
		virtual void onStart();
		
		virtual void onExit();
		
		void onRunApp() override;
		
	public:
		virtual void dispatchStart();
		
		static void dispatchStartToApp();
		
		virtual void dispatchExit();
		
		static void dispatchExitToApp();
		
	private:
		AtomicRef<Window> m_mainWindow;
		AtomicRef<Menu> m_mainMenu;
		
	};

}

#endif
