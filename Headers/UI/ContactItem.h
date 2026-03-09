#ifndef __CONTACTITEM_H__
#define __CONTACTITEM_H__

#include <ListItem.h>
#include <String.h>

//class BString;

class ContactItem: public BListItem
{
	public:
		explicit ContactItem(const char* name = "", bool isChannel = false);
		virtual ~ContactItem();
		bool IsChannel() const { return _IsChannel; }
	public:
		void DrawItem(BView* owner, BRect frame, bool complete);
		void Update(BView* owner, const BFont* font);
	public:
		void _DrawAvatar(BView* owner, BRect rect);
		rgb_color _AvatarColor() const;
	private:
		bool _IsChannel;
		uint32 _UnreadMessageCount;
		BString _LastMessage;
	private:
		float _BaseLineOffset;
};

#endif
