#include "UI/Views/ChatMediaView.h"

ChatMediaView::ChatMediaView(const char* contact_name)
	:
	BView(contact_name, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
	_contact_name(contact_name)
	{
	}

ChatMediaView::~ChatMediaView()
{
}

	
void
ChatMediaView::AttachedToWindow()
{
	BView::AttachedToWindow();
	if (Parent() != NULL)
		SetViewColor(Parent()->ViewColor());
	//SetViewColor(kHeaderBg);
	//SetViewColor(tint_color(ui_color(B_PANEL_BACKGROUND_COLOR), B_LIGHTEN_1_TINT));
	//SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	SetViewColor(255,255,255,255);
}




