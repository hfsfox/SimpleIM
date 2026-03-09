#include "UI/Deskbar/DeskbarReplicant.h"
#include "Defs/Constants.h"

#include <MenuItem.h>
#include <Roster.h>
#include <PopUpMenu.h>
#include <IconUtils.h>
#include <Resources.h>
#include <File.h>
#include <Catalog.h>

#include <cstdio>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "DeskbarReplicant"

DeskbarReplicant::DeskbarReplicant(BRect frame, const char* name)
    :
    BView(frame, name, B_FOLLOW_ALL, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
    fUnreadNotificationsCount(0)
    {
    	//fUnreadNotificationsCount = 11;
    	Init();
    }
    
DeskbarReplicant::DeskbarReplicant(BMessage* archive)
    :
    BView(archive),
    fUnreadNotificationsCount(0)
    {
    	Init();
    }
    
DeskbarReplicant::~DeskbarReplicant()
{
    //delete fStatusPoller;
    delete fConnectedIcon;
    //delete fDisconnectedIcon;
}

void DeskbarReplicant::Init()
{
    CreateIcons();
}

void DeskbarReplicant::CreateIcons()
{
    // Create 16x16 RGBA icons
    //BRect iconRect(0, 0, 15, 15);
    BRect iconRect(0,0, B_MINI_ICON - 1, B_MINI_ICON - 1);
    //B_MINI_ICON - 1, B_MINI_ICON - 1
    
    fConnectedIcon = new BBitmap(iconRect, B_RGBA32);
    // Try to load HVIF icon from app resources
    entry_ref ref;
    if (be_roster->FindApp(APP_SIGNATURE, &ref) == B_OK) 
    {
        BFile file(&ref, B_READ_ONLY);
        BResources resources(&file);
        
        
    	size_t size;
    	const void* data = resources.LoadResource(B_VECTOR_ICON_TYPE, "deskbar_icon", &size);
        
     	if (data != nullptr && size > 0)
     	{
        	    // Render connected icon (full color)
            	BIconUtils::GetVectorIcon((const uint8*)data, size, fConnectedIcon);
     	}
    }     
}

void DeskbarReplicant::AttachedToWindow()
{
    BView::AttachedToWindow();

    if (Parent() != nullptr) {
        SetViewColor(Parent()->ViewColor());
        SetLowColor(Parent()->ViewColor());
    } else {
        SetViewColor(B_TRANSPARENT_COLOR);
    }

    SetLowColor(ViewColor());

    // Start polling for connection status every second
    /*
    if (fStatusPoller == nullptr) {
        BMessage pollMsg(MSG_POLL_STATUS);
        fStatusPoller = new BMessageRunner(BMessenger(this),
            &pollMsg, 1000000);  // 1 second interval
    }
    */

    // Query status immediately
    //QueryConnectionStatus();
}

void DeskbarReplicant::DetachedFromWindow()
{
    //delete fStatusPoller;
    //fStatusPoller = nullptr;

    BView::DetachedFromWindow();
}

/*
void DeskbarReplicant::QueryConnectionStatus()
{
}
*/

status_t DeskbarReplicant::Archive(BMessage* archive, bool deep) const
{
    status_t status = BView::Archive(archive, deep);
    if (status != B_OK)
        return status;

    // Add app signature for replicant loading
    status = archive->AddString("add_on", APP_SIGNATURE);
    if (status != B_OK)
        return status;

    status = archive->AddString("class", "IMDeskbarReplicant");
    return status;
}


BArchivable* DeskbarReplicant::Instantiate(BMessage* archive)
{
    if (!validate_instantiation(archive, "IMDeskbarReplicant"))
        return nullptr;
    return new DeskbarReplicant(archive);
}

void DeskbarReplicant::Draw(BRect updateRect)
{
	BRect bounds = Bounds();
    SetDrawingMode(B_OP_ALPHA);

    BBitmap* icon = /*fIsConnected ?*/ fConnectedIcon /*: fDisconnectedIcon*/;
    if (icon != nullptr) {
        DrawBitmap(icon/*, BPoint(0, 0)*/);
    }
    
    fUnreadNotificationsCount = 11;
    
    // Draw unread count badge
	if (fUnreadNotificationsCount > 0) {
		SetHighColor(220, 40, 40);
		BRect badge(bounds.right - 7, bounds.top,
			bounds.right, bounds.top + 7);
		FillEllipse(badge);

		SetHighColor(255, 255, 255);
		char countStr[4];
		if (fUnreadNotificationsCount > 9)
			strlcpy(countStr, "+", sizeof(countStr));
		else
			snprintf(countStr, sizeof(countStr), "%d",
				(int)(fUnreadNotificationsCount & 0xF));

		BFont font;
		GetFont(&font);
		font.SetSize(7);
		SetFont(&font);
		DrawString(countStr,
			BPoint(bounds.right - 5, bounds.top + 6));
	}
}

void DeskbarReplicant::MouseDown(BPoint where)
{
	BPoint screenWhere = ConvertToScreen(where);

    uint32 buttons;
    GetMouse(&where, &buttons);
    
    if (buttons & B_SECONDARY_MOUSE_BUTTON)
    {
        ShowPopUpMenu(screenWhere);
    }
}


void DeskbarReplicant::MessageReceived(BMessage* message)
{
    switch (message->what) {
    	case MSG_DR_QUIT:
    		{
    			 BMessenger messenger(APP_SIGNATURE);
            	if (messenger.IsValid())
            	{
                	messenger.SendMessage(B_QUIT_REQUESTED);
            	}
    		}
    		break;
    		case MSG_DR_SHOW_ABOUT:
    		{
    			 BMessenger messenger(APP_SIGNATURE);
            	if (messenger.IsValid())
            	{
                	messenger.SendMessage(B_ABOUT_REQUESTED);
            	}
    		}
    		break;
    	default:
            BView::MessageReceived(message);
            break;
    }
}

void DeskbarReplicant::SetConnected(bool connected)
{
}

void DeskbarReplicant::ShowPopUpMenu(BPoint where)
{
	BPopUpMenu* menu = new BPopUpMenu("IMPopUp", false, false);
	// Settings
    BMenuItem* settingsItem = new BMenuItem(B_TRANSLATE("Settings" B_UTF8_ELLIPSIS), new BMessage(/*MSG_SHOW_SETTINGS*/));
    menu->AddItem(settingsItem);
    menu->AddSeparatorItem();
    // About
    BMenuItem* aboutItem = new BMenuItem(B_TRANSLATE("About IM client" B_UTF8_ELLIPSIS), new BMessage(/*MSG_SHOW_ABOUT*/));
    menu->AddItem(aboutItem);
	menu->AddSeparatorItem();
    // Quit
    BMenuItem* quitItem = new BMenuItem(B_TRANSLATE("Quit"), new BMessage(MSG_DR_QUIT/*MSG_QUIT_REQUESTED*/));
    menu->AddItem(quitItem);

    menu->SetTargetForItems(this);
    menu->Go(where, true, true, true);
}

// Export function for Deskbar
extern "C" _EXPORT BView* instantiate_deskbar_item()
{
    return new DeskbarReplicant(BRect(0, 0, 15, 15), REPLICANT_NAME);
}




