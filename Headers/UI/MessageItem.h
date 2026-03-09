#ifndef __MESSAGEITEM_H__
#define __MESSAGEITEM_H__
#include <ListItem.h>
#include <String.h>

class MessageView: public BListItem
{
	public:
		explicit MessageView(const char* msg_text = "", const char* sender_name = "");
		virtual ~MessageView();
	public:
		virtual void			DrawItem(BView* owner, BRect frame,
								bool complete = false);
		virtual void			Update(BView* owner, const BFont* font);
	public:
		const char*		Text() const { return _MessageText.String(); }
		const char*		SenderName() const { return _SenderName.String(); }
	private:
		BString _MessageText;
		BString _SenderName;
};

#endif
