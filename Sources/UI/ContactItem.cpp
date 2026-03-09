#include "UI/ContactItem.h"

#include <View.h>
#include <GraphicsDefs.h>
#include <Font.h>
#include <Point.h>
//#include <String.h>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>

// Avatar colors (Telegram-style palette)
static const rgb_color kAvatarColors[] = {
	{229, 115, 115, 255},  // Red
	{186, 104, 200, 255},  // Purple
	{121, 134, 203, 255},  // Indigo
	{79, 195, 247, 255},   // Light Blue
	{77, 182, 172, 255},   // Teal
	{129, 199, 132, 255},  // Green
	{255, 183, 77, 255},   // Orange
	{240, 98, 146, 255},   // Pink
};
static const int kAvatarColorCount = sizeof(kAvatarColors) / sizeof(kAvatarColors[0]);

// Layout constants
static const float kItemHeight = 64.0f;
static const float kAvatarSize = 46.0f;
static const float kAvatarMargin = 10.0f;
static const float kTextMargin = 8.0f;
static const float kBadgeSize = 20.0f;

// Colors
static const rgb_color kNameColor = {0, 0, 0, 255};
static const rgb_color kMessageColor = {128, 128, 128, 255};
static const rgb_color kTimeColor = {160, 160, 160, 255};
static const rgb_color kBadgeColor = {77, 182, 172, 255};  // Telegram green
static const rgb_color kBadgeTextColor = {255, 255, 255, 255};
static const rgb_color kChannelColor = {66, 133, 244, 255};  // Blue for channels
static const rgb_color kSelectedBg = {228, 241, 254, 255};


ContactItem::ContactItem(const char* name, bool isChannel)
	:
	BListItem(),
	_LastMessage(""),
	_IsChannel(false)
	{
	}
	
	
ContactItem::~ContactItem()
{
}

void
ContactItem::DrawItem(BView* owner, BRect frame, bool complete)
{
	rgb_color lowColor = owner->LowColor();
	rgb_color highColor = owner->HighColor();
	
	// Get fonts
	BFont nameFont;
	owner->GetFont(&nameFont);
	nameFont.SetFace(B_BOLD_FACE);

	BFont messageFont;
	owner->GetFont(&messageFont);
	messageFont.SetSize(messageFont.Size() * 0.9f);

	BFont timeFont;
	owner->GetFont(&timeFont);
	timeFont.SetSize(timeFont.Size() * 0.85f);

	font_height nameFh, messageFh, timeFh;
	nameFont.GetHeight(&nameFh);
	messageFont.GetHeight(&messageFh);
	timeFont.GetHeight(&timeFh);
	
	// Background
	if (IsSelected()) {
		owner->SetLowColor(/*kSelectedBg*/ui_color(B_LIST_SELECTED_BACKGROUND_COLOR));
	} else {
		owner->SetLowColor(ui_color(B_PANEL_BACKGROUND_COLOR/*B_LIST_BACKGROUND_COLOR*/));
	}
	owner->FillRect(frame, B_SOLID_LOW);
	// Draw separator line at bottom
	owner->SetHighColor(tint_color(ui_color(B_PANEL_BACKGROUND_COLOR), B_DARKEN_1_TINT));
	owner->StrokeLine(BPoint(frame.left /*+ kAvatarMargin + kAvatarSize + kTextMargin*/, frame.bottom),
		BPoint(frame.right, frame.bottom));
		
	// Avatar
	BRect avatarRect(
		frame.left + kAvatarMargin,
		frame.top + (frame.Height() - kAvatarSize) / 2,
		frame.left + kAvatarMargin + kAvatarSize,
		frame.top + (frame.Height() + kAvatarSize) / 2
	);
	_DrawAvatar(owner, avatarRect);
		
	float textLeft = avatarRect.right + kTextMargin;
	float textRight = frame.right - kTextMargin;
		
	// Time string (top right)
	char timeStr[16] = "";
	/*
	if (fLastMessageTime > 0) {
		_FormatTime(timeStr, sizeof(timeStr), fLastMessageTime);
	}
	*/
	float timeWidth = 0;
	if (timeStr[0] != '\0')
	{
		owner->SetFont(&timeFont);
		timeWidth = owner->StringWidth(timeStr) + kTextMargin;
		owner->SetHighColor(kTimeColor);
		owner->DrawString(timeStr,
			BPoint(textRight - owner->StringWidth(timeStr),
				frame.top + kTextMargin + nameFh.ascent));
	}
	
	// Contact name (top left, bold)
	owner->SetFont(&nameFont);
	owner->SetHighColor(/*fIsChannel ? kChannelColor :*/ kNameColor);

	BString displayName = /*fContact.name[0] ? fContact.name :*/ "Unknown";
	float maxNameWidth = textRight - textLeft - timeWidth - kTextMargin;

	// Truncate name if too long
	BString truncatedName = displayName;
	if (owner->StringWidth(truncatedName.String()) > maxNameWidth) {
		BString testStr;
		do {
			truncatedName.Truncate(truncatedName.Length() - 1);
			testStr = truncatedName;
			testStr.Append("...");
		} while (truncatedName.Length() > 0 &&
				 owner->StringWidth(testStr.String()) > maxNameWidth);
		truncatedName.Append("...");
	}

	owner->DrawString(truncatedName.String(),
		BPoint(textLeft, frame.top + kTextMargin + nameFh.ascent));
}

void
ContactItem::Update(BView* owner, const BFont* font)
{
	BListItem::Update(owner, font);

	font_height fh;
	font->GetHeight(&fh);
	_BaseLineOffset = fh.ascent + fh.leading;

	SetHeight(kItemHeight);
}


void
ContactItem::_DrawAvatar(BView* owner, BRect rect)
{
	// Draw circular avatar with initials
	rgb_color avatarColor = _IsChannel ? kChannelColor : _AvatarColor();
	owner->SetHighColor(avatarColor);
	owner->FillEllipse(rect);

	// Get initials (first letter, or first two for two-word names)
	BString initials;
	if (_IsChannel) {
		initials = "#";  // Channel symbol
	} else {
		const char* name = "Name"/*fContact.name*/;
		if (name[0] != '\0') {
			initials.Append(toupper(name[0]), 1);
			// Find second word
			const char* space = strchr(name, ' ');
			if (space != NULL && space[1] != '\0') {
				initials.Append(toupper(space[1]), 1);
			}
		} else {
			initials = "?";
		}
	}

	// Draw initials
	owner->SetHighColor(255, 255, 255);
	BFont font;
	owner->GetFont(&font);
	font.SetSize(kAvatarSize * 0.45f);
	font.SetFace(B_BOLD_FACE);
	owner->SetFont(&font);

	font_height fh;
	font.GetHeight(&fh);
	float textWidth = owner->StringWidth(initials.String());

	owner->DrawString(initials.String(),
		BPoint(rect.left + (rect.Width() - textWidth) / 2,
			rect.top + (rect.Height() + fh.ascent - fh.descent) / 2));
}


rgb_color
ContactItem::_AvatarColor() const
{
	// Generate consistent color based on name hash
	uint32 hash = 0;
	const char* name = "Name"/*fContact.name*/;
	while (*name) {
		hash = hash * 31 + (uint8)*name++;
	}
	return kAvatarColors[hash % kAvatarColorCount];
}
