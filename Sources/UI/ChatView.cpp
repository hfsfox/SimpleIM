#include "UI/ChatView.h"

#include <ScrollView.h>

ChatView::ChatView(const char* name)
	:
	BListView(name, B_SINGLE_SELECTION_LIST)
	{
	}
	
ChatView::~ChatView()
{
	//ClearMessages();
}

void
ChatView::AttachedToWindow()
{
	BListView::AttachedToWindow();
	// Light gray background for chat area
	SetViewColor(tint_color(ui_color(B_PANEL_BACKGROUND_COLOR), B_DARKEN_1_TINT));
}

void
ChatView::MessageReceived(BMessage* message)
{
	BListView::MessageReceived(message);
}
