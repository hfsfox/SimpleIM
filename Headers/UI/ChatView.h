#ifndef __CHATVIEW_H__
#define __CHATVIEW_H__

#include <ListView.h>

class ChatView : public BListView
{
	public:
		explicit ChatView(const char* name = "");
		virtual ~ChatView();
	public:
		virtual void AttachedToWindow();
		virtual void MessageReceived(BMessage* message);
};

#endif
