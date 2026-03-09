#include <Application.h>
#include <Window.h>
#include <Deskbar.h>
#include <private/interface/AboutWindow.h>
#include <IconUtils.h>
#include <Catalog.h>
#include <cstdio>

#include "Defs/Constants.h"
#include "UI/MainWindow.h"
#include "UI/Deskbar/DeskbarReplicant.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"

class IMApp : public BApplication {
public:
							IMApp();
	virtual					~IMApp();

	virtual void			ReadyToRun();
	virtual bool			QuitRequested();
	virtual void			AboutRequested();
	
	void InstallDeskbarReplicant();
	void RemoveDeskbarReplicant();

private:
			MainWindow*		_MainWindow;
};


IMApp::IMApp()
	:
	BApplication(APP_SIGNATURE),
	_MainWindow(NULL)
{
}


IMApp::~IMApp()
{
	RemoveDeskbarReplicant();
}


void
IMApp::ReadyToRun()
{
	_MainWindow = new MainWindow();
	_MainWindow->Show();
	
	// Install Deskbar replicant
    //InstallDeskbarReplicant();
}

void
IMApp::InstallDeskbarReplicant()
{
    BDeskbar deskbar;

    // Remove existing replicant if present
    if (deskbar.HasItem(REPLICANT_NAME))
    {
        deskbar.RemoveItem(REPLICANT_NAME);
    }
    
    // Create and install the replicant
    DeskbarReplicant* replicant = new DeskbarReplicant(
        BRect(0, 0, B_MINI_ICON - 1, B_MINI_ICON - 1), REPLICANT_NAME);

    status_t result = deskbar.AddItem(replicant);
    delete replicant;

    if (result != B_OK) {
        fprintf(stderr, "Failed to install Deskbar replicant: %s\n",
            strerror(result));
    }
    
}

void
IMApp::RemoveDeskbarReplicant()
{
    BDeskbar deskbar;
    if (deskbar.HasItem(REPLICANT_NAME)) {
        deskbar.RemoveItem(REPLICANT_NAME);
    }
}

bool
IMApp::QuitRequested()
{
	// MainWindow handles cleanup in its QuitRequested
	// Just let the default behavior close everything
	return BApplication::QuitRequested();
}

void
IMApp::AboutRequested()
{
	BAboutWindow* about = new BAboutWindow("Messenger", APP_SIGNATURE);
	about->AddCopyright(2026,"HFS.Fox");
	about->AddDescription(B_TRANSLATE("My application"));
	about->Show();
}


int
main()
{
	IMApp app;
	app.Run();
	return 0;
}
