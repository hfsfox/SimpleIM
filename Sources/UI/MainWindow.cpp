#include "Defs/Constants.h"
#include "UI/MainWindow.h"
#include "UI/ChatHeader.h"
#include "UI/ChatView.h"
#include "UI/ContactItem.h"
#include "UI/FolderItem.h"
#include "UI/MessageItem.h"
#include "UI/ContactInfoSideView.h"

#include <Button.h>
#include <MenuBar.h>
#include <ListView.h>
#include <ScrollView.h>
#include <SplitView.h>
#include <GroupView.h>
#include <TextControl.h>
#include <LayoutBuilder.h>
#include <Application.h>
#include <Catalog.h>

#include <Deskbar.h>
#include <Roster.h>
#include <cstdio>
//#include ""

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MainWindow"

static const rgb_color kBackgroundColor = {24, 28, 32, 255};

MainWindow::MainWindow()
:
BWindow(BRect(), B_TRANSLATE("Messenger"), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS),
MainMenuBar(NULL),
ContactList(NULL)
{
	_BuildMenuBar();
	_BuildUI();
	SetSizeLimits(600, B_SIZE_UNLIMITED, 400, B_SIZE_UNLIMITED);
}

MainWindow::~MainWindow()
{
}

void
MainWindow::_BuildUI()
{
	
	fMenuBarContainer = new BGroupView(B_HORIZONTAL, 0);
	fMenuBarContainer->GroupLayout()->AddView(MainMenuBar);
	
	// Sidebar with contact list
	BView* sidebar = new BView("sidebar", 0);
	//sidebar->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	sidebar->SetViewUIColor(B_CONTROL_BACKGROUND_COLOR);
	sidebar->SetExplicitMinSize(BSize(220, B_SIZE_UNSET));
	sidebar->SetExplicitPreferredSize(BSize(260, B_SIZE_UNSET));
	
	// === LEFT SIDEBAR: Contact List ===
	BListView* fContactList = new BListView("contacts");
	//fContactList->SetLowColor(ui_color(B_CONTROL_BACKGROUND_COLOR));
	fContactList->SetSelectionMessage(new BMessage(/*MSG_CONTACT_SELECTED*/));
	fContactScroll = new BScrollView("contact_scroll", fContactList,
		B_WILL_DRAW | B_FRAME_EVENTS, false, true, B_PLAIN_BORDER);
		
	fContactList->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	//fContactScroll->SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	//fContactScroll->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	
	ContactItem* _ChannelItem = new ContactItem("Public Channel", true);
	fContactList->AddItem(_ChannelItem);
	
	ContactItem* _ArchivedChannelItem = new ContactItem("Archive", true);
	fContactList->AddItem(_ArchivedChannelItem);
	
	ContactItem* _BookmarkChannelItem = new ContactItem("Archive", true);
	fContactList->AddItem(_BookmarkChannelItem);
	
	fContactList->AddItem(new ContactItem("Another contact", true));
	fContactList->AddItem(new ContactItem("Another contact 2", true));
	
	
	//BScrollView* fContactScroll = new BScrollView("chat_scroll", sidebar, B_WILL_DRAW | B_FRAME_EVENTS, false, false, B_PLAIN_BORDER);
	BLayoutBuilder::Group<>(sidebar, B_VERTICAL, 0)
		.Add(fContactScroll, 1.0)
	.End();
	
	// Chat header
	ChatHeader* fChatHeader = new ChatHeader("chat_header");
	
	// contact info sidebar
	BGroupView* fViewerContainer = new BGroupView(B_HORIZONTAL, 0);
	
	fContactInfoSideView = new ContactInfoSideView();
	//fContactInfoItem = fViewerContainer->GroupLayout()->AddView(fContactInfoSideView);
	//fContactInfoItem->SetVisible(false);
	
	
	// Message input area
	BTextControl* fMessageInput = new BTextControl("message", NULL, "",
		new BMessage(/*MSG_SEND_MESSAGE*/));
	fMessageInput->SetEnabled(false);
	fMessageInput->TextView()->SetExplicitMinSize(BSize(200, B_SIZE_UNSET));

	BButton* fSendButton = new BButton("send", "Send", new BMessage(/*MSG_SEND_MESSAGE*/));
	fSendButton->SetEnabled(false);
	fSendButton->MakeDefault(true);

	// Input bar
	BView* inputBar = new BView("input_bar", 0);
	inputBar->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	BLayoutBuilder::Group<>(inputBar, B_HORIZONTAL, B_USE_SMALL_SPACING)
		.SetInsets(B_USE_SMALL_SPACING)
		.Add(fMessageInput, 1.0)
		.Add(fSendButton)
	.End();
	
	//
	// Chat view
	fChatView = new ChatView("chat");
	BScrollView* fChatScroll = new BScrollView("chat_scroll", fChatView, B_WILL_DRAW | B_FRAME_EVENTS, false, true, B_PLAIN_BORDER);
	
	BView* chatPanel = new BView("chat_panel", 0);
	chatPanel->SetViewUIColor(B_DOCUMENT_BACKGROUND_COLOR);
	//chatPanel->SetViewUIColor(B_DOCUMENT_BACKGROUND_COLOR);
	BLayoutBuilder::Group<>(chatPanel, B_VERTICAL, 0)
		.Add(fChatHeader)
		.Add(fChatScroll, 1.0)
		.Add(inputBar)
	.End();
	
	fMainSplit = new BSplitView(B_HORIZONTAL, 0);
	fMainSplit->AddChild(sidebar, 0.30);
	fMainSplit->AddChild(chatPanel, 0.70);
	fMainSplit->SetCollapsible(0, false);
	fMainSplit->SetCollapsible(1, false);
	
	BListView* folders_view = /*new BView("folders_view", 0)*/ new BListView("folders");
	folders_view->SetLowColor(ui_color(B_LIST_BACKGROUND_COLOR));
	BScrollView* foldersScroll = new BScrollView("chat_scroll", folders_view,
		B_WILL_DRAW | B_FRAME_EVENTS, false, true, B_NO_BORDER);
		
	//foldersScroll->SetLowColor(ui_color(B_LIST_BACKGROUND_COLOR));

	//sidebar->SetViewUIColor(B_BACKGROUND_COLOR);
	//folders_view->SetViewColor(kBackgroundColor);
	//folders_view->SetViewUIColor(B_CONTROL_BACKGROUND_COLOR);
	folders_view->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	folders_view->SetExplicitMaxSize(BSize(80, B_SIZE_UNSET));
	folders_view->SetExplicitPreferredSize(BSize(60, B_SIZE_UNSET));
	
	folders_view->AddItem(new FolderItem("All", true));
	folders_view->AddItem(new FolderItem("Folder 1", false));
	folders_view->AddItem(new FolderItem("Folder 2", false));
	
	BView* panels_view = new BView("panels_view", 0);
	BLayoutBuilder::Group<>(panels_view, B_HORIZONTAL, 0)
		.Add(/*folders_view*/foldersScroll, 1.0)
		.Add(fMainSplit, 1.0)
	.End();
	
	fContactInfoItem = fViewerContainer->GroupLayout()->AddView(panels_view);
	//fContactInfoItem->SetVisible(false);
	fContactInfoItem = fViewerContainer->GroupLayout()->AddView(fContactInfoSideView);
	fContactInfoItem->SetVisible(false);
	
	// === MAIN LAYOUT ===
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(fMenuBarContainer)
		//.AddGroup(B_HORIZONTAL, 0)
			//.Add(panels_view, 1.0)
			.Add(fViewerContainer)
			//.AddGlue()
		//.Add(MainMenuBar)
		//.Add(panels_view, 1.0)
		//.End()
	.End();
}

void
MainWindow::_BuildMenuBar()
{
	MainMenuBar = new BMenuBar("menubar");
	// File menu
	BMenu* fileMenu = new BMenu("File");
	fileMenu->AddItem(new BMenuItem(B_TRANSLATE("Preferences"), new BMessage(/*MSG_OPEN_PREFS*/),','));
	fileMenu->AddItem(new BSeparatorItem());
	fileMenu->AddItem(new BMenuItem(B_TRANSLATE("About"), new BMessage(B_ABOUT_REQUESTED), 'H'));
	fileMenu->AddItem(new BSeparatorItem());
	fileMenu->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	MainMenuBar->AddItem(fileMenu);
	// Edit menu
	BMenu* editMenu = new BMenu("Edit");
	editMenu->AddItem(new BMenuItem(B_TRANSLATE("Add Deskbar replicant"), new BMessage(MSG_ADD_TO_DESKBAR), 'I'));
	editMenu->AddItem(new BMenuItem(B_TRANSLATE("Remove Deskbar replicant"), new BMessage(MSG_RM_FROM_DESKBAR), 'R'));
	editMenu->AddItem(new BMenuItem(B_TRANSLATE("Show contact info"), new BMessage(MSG_SHOW_CONTACT_INFO), 'I'));
	MainMenuBar->AddItem(editMenu);
	// View menu
	BMenu* viewMenu = new BMenu("View");
	MainMenuBar->AddItem(viewMenu);
	
}

void
MainWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_ADD_TO_DESKBAR:
			{
				BDeskbar deskbar;
				if (!deskbar.HasItem(REPLICANT_NAME))
				{
					entry_ref ref;
					if (be_roster->FindApp(APP_SIGNATURE, &ref) == B_OK)
					{
						status_t result = deskbar.AddItem(&ref);
						//_LogMessage("INFO", "Added to Deskbar");
						if (result != B_OK)
						{
        					fprintf(stderr, "Failed to install Deskbar replicant: %s\n",
            				strerror(result));
    					}
					}
				} 
				else
				{
					//_LogMessage("INFO", "Already in Deskbar");
					fprintf(stdout, "Already in Deskbar");
				}
			}
			break;
		case MSG_RM_FROM_DESKBAR:
			{
				BDeskbar deskbar;
    			if (deskbar.HasItem(REPLICANT_NAME))
    			{
        			deskbar.RemoveItem(REPLICANT_NAME);
    			}
			}
			break;
		case B_ABOUT_REQUESTED:
			{
				be_app->AboutRequested();
			}
			break;
		case MSG_SHOW_CONTACT_INFO:
			{
				if(!fContactInfoItem->IsVisible() == true)
				{
					fContactInfoItem->SetVisible(true);
				}
				else
				{
					fContactInfoItem->SetVisible(false);
				}
			}
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

bool
MainWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


		
