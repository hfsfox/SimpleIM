#ifndef __FOLDERITEM_H__
#define __FOLDERITEM_H__

#include <ListItem.h>
#include <String.h>

class FolderItem: public BListItem
{
	public:
		explicit FolderItem(const char* name = "", bool isAll = false);
		virtual ~FolderItem();
	public:
		void DrawItem(BView* owner, BRect frame, bool complete);
		void Update(BView* owner, const BFont* font);
	public:
		bool IsAllFolder() const { return _IsAll; }
	private:
		bool _IsAll;
		BString _FolderName;
};

#endif
