#ifndef __DESKBARREPLICANT_H__
#define __DESKBARREPLICANT_H__

#include <View.h>
#include <Bitmap.h>
#include <Dragger.h>
#include <MessageRunner.h>

//#define REPLICANT_NAME "IM_Client"

// Required export for replicant instantiation
extern "C" _EXPORT BView* instantiate_deskbar_item();

class DeskbarReplicant : public BView
{
	public:
    	// Constructor for normal creation
    	DeskbarReplicant(BRect frame, const char* name);
	
    	// Constructor for replicant instantiation from archive
    	DeskbarReplicant(BMessage* archive);
	
    	virtual ~DeskbarReplicant();

    	// BArchivable interface
    	static BArchivable* Instantiate(BMessage* archive);
    	virtual status_t Archive(BMessage* archive, bool deep = true) const override;

    	// BView interface
    	virtual void Draw(BRect updateRect) override;
    	virtual void MouseDown(BPoint where) override;
    	virtual void MessageReceived(BMessage* message) override;
    	virtual void AttachedToWindow() override;
    	virtual void DetachedFromWindow() override;
    public:
    	void SetConnected(bool connected);
    private:
    	void Init();
    	void CreateIcons();
    	void ShowPopUpMenu(BPoint where);
    private:
    	//BBItmap* 
    	BBitmap* fConnectedIcon;
    	BBitmap* fDisconnectedIcon;
    	BDragger* fDragger;
    	BMessageRunner* fStatusPoller;
    	int32			fUnreadNotificationsCount;
};

#endif
