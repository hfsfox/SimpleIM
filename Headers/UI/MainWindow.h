#ifndef __MAINWINDOW_H__
#define __MAINWINODW_H__

#include <Window.h>

class BMenuBar;
class BListView;
class BScrollView;
class BSplitView;
class ChatView;
class ContactInfoSideView;

class MainWindow: public BWindow
{
	public:
		MainWindow();
		virtual ~MainWindow();
	public:
		virtual void MessageReceived(BMessage* message);
		virtual bool QuitRequested();
	private:
		void _BuildUI();
		void _BuildMenuBar();
	private:
		//UI elements - menu
		BMenuBar* MainMenuBar;
		// UI elements - Sidebar
		BListView*		ContactList;
		BScrollView*	fContactScroll;
		//ContactItem*	fChannelItem;
		//UI elements - Layout
		BSplitView*		fMainSplit;
		ChatView* fChatView;
		ContactInfoSideView* fContactInfoSideView;
};

#endif
