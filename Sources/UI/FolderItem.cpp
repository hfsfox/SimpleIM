#include "UI/FolderItem.h"

#include <Font.h>
#include <View.h>

static const float kItemHeight = 64.0f;
static const float kTextMargin = 8.0f;

static const rgb_color kNameColor = {0, 0, 0, 255};
static const rgb_color kSelectedBg = {228, 241, 254, 255};


FolderItem::FolderItem(const char* name, bool isAll)
	:
	BListItem(),
	_FolderName(name),
	_IsAll(isAll)
	{
	}
	
FolderItem::~FolderItem()
{
}

void
FolderItem::DrawItem(BView* owner, BRect frame, bool complete)
{
	rgb_color lowColor = owner->LowColor();
	rgb_color highColor = owner->HighColor();
	
	// Get fonts
	BFont nameFont;
	owner->GetFont(&nameFont);
	nameFont.SetSize(10);
	nameFont.SetFace(B_REGULAR_FACE);
	
	font_height nameFh;
	nameFont.GetHeight(&nameFh);
	// Background
	if (IsSelected()) {
		owner->SetLowColor(/*kSelectedBg*/ ui_color(B_LIST_SELECTED_BACKGROUND_COLOR));
	} else {
		owner->SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR/*B_LIST_BACKGROUND_COLOR*/));
	}
	owner->FillRect(frame, B_SOLID_LOW);
	
	// Folder name (top left, bold)
	owner->SetFont(&nameFont);
	owner->SetHighColor(kNameColor);
	
	//float textLeft = avatarRect.right + kTextMargin;
	//float textRight = frame.right - kTextMargin;
	float textLeft = frame.right - kTextMargin;
	
	BString displayName = _FolderName;
	owner->DrawString(displayName/*truncatedName.String()*/,
		BPoint(kTextMargin/*0.0*//*textLeft*/, frame.bottom /*- kTextMargin*/ - nameFh.ascent));
}

void
FolderItem::Update(BView* owner, const BFont* font)
{
	BListItem::Update(owner, font);

	/*font_height fh;
	font->GetHeight(&fh);
	fBaselineOffset = fh.ascent + fh.leading;*/

	SetHeight(kItemHeight);
}

