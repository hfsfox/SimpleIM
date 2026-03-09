#ifndef __MESSAGEITEMVIEW_H__
#define __MESSAGEITEMVIEW_H__

#include <ListItem.h>
#include <Rect.h>
#include <String.h>
#include <vector>

class MessageItemView: public BListItem
{
	public:
		explicit MessageItemView(const char* _Message = "",
							const char* _SenderName = NULL);
		virtual ~MessageItemView();
	public:
		virtual void			DrawItem(BView* owner, BRect frame,
								bool complete = false);
		virtual void			Update(BView* owner, const BFont* font);
	private:
};

#endif
