#include "UI/ChatHeader.h"

#include <Font.h>
#include <LayoutUtils.h>

// Avatar colors (same as ContactItem)
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

// Colors
static const rgb_color kNameColor = {0, 0, 0, 255};
static const rgb_color kStatusColor = {128, 128, 128, 255};
static const rgb_color kChannelColor = {66, 133, 244, 255};
static const rgb_color kOnlineColor = {77, 182, 172, 255};
static const rgb_color kHeaderBg = {255, 255, 255, 255};
static const rgb_color kBorderColor = {230, 230, 230, 255};

// Layout constants
static const float kHeaderHeight = 56.0f;
static const float kAvatarSize = 40.0f;
static const float kMargin = 12.0f;

ChatHeader::ChatHeader(const char* name)
	:
	BView(name, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
	//fContact(NULL),
	fDisplayName("Select a contact"),
	fStatus(""),
	fIsChannel(false)
	{
		SetViewColor(kHeaderBg);
		SetExplicitMinSize(BSize(B_SIZE_UNSET, kHeaderHeight));
		SetExplicitMaxSize(BSize(B_SIZE_UNLIMITED, kHeaderHeight));
	}
	
	
ChatHeader::~ChatHeader()
{
}

void
ChatHeader::AttachedToWindow()
{
	BView::AttachedToWindow();
	if (Parent() != NULL)
		SetViewColor(Parent()->ViewColor());
	//SetViewColor(kHeaderBg);
	SetViewColor(tint_color(ui_color(B_PANEL_BACKGROUND_COLOR), B_LIGHTEN_1_TINT));
}


void
ChatHeader::Draw(BRect updateRect)
{
	BRect bounds = Bounds();

	// Background
	//SetHighColor(kHeaderBg);
	SetHighColor(ui_color(B_CONTROL_BACKGROUND_COLOR/*B_LIST_BACKGROUND_COLOR*/));
	FillRect(bounds);
	// Bottom border
	SetHighColor(kBorderColor);
	StrokeLine(BPoint(bounds.left, bounds.bottom),
		BPoint(bounds.right, bounds.bottom));
		
	/*if (fContact == NULL &&
	 		!fIsChannel) 
	 {
		// No contact selected - show placeholder
		SetHighColor(kStatusColor);
		BFont font;
		GetFont(&font);
		font.SetSize(14);
		SetFont(&font);

		font_height fh;
		font.GetHeight(&fh);

		DrawString(fDisplayName.String(),
			BPoint(kMargin, bounds.top + (bounds.Height() + fh.ascent - fh.descent) / 2));
		return;
	}*/
	
	// Avatar
	BRect avatarRect(
		kMargin,
		(bounds.Height() - kAvatarSize) / 2,
		kMargin + kAvatarSize,
		(bounds.Height() + kAvatarSize) / 2
	);
	_DrawAvatar(avatarRect);

	// Name
	float textLeft = avatarRect.right + kMargin;

	BFont nameFont;
	GetFont(&nameFont);
	nameFont.SetSize(15);
	nameFont.SetFace(B_BOLD_FACE);
	SetFont(&nameFont);
	
	font_height nameFh;
	nameFont.GetHeight(&nameFh);

	SetHighColor(/*fIsChannel ? kChannelColor :*/ kNameColor);
	DrawString(fDisplayName.String(),
		BPoint(textLeft, bounds.top + kMargin + nameFh.ascent));

	// Status line
	BFont statusFont;
	GetFont(&statusFont);
	statusFont.SetSize(12);
	statusFont.SetFace(B_REGULAR_FACE);
	SetFont(&statusFont);

	font_height statusFh;
	statusFont.GetHeight(&statusFh);

}

void
ChatHeader::_DrawAvatar(BRect rect)
{
	// Draw circular avatar with initials
	rgb_color avatarColor = /*fIsChannel ? kChannelColor :*/ _AvatarColor();
	SetHighColor(avatarColor);
	FillEllipse(rect);

	// Get initials
	BString initials;
	/*if (fIsChannel) {
		initials = "#";
	}*//* else if (fContact != NULL) {
		const char* name = fContact->name;
		if (name[0] != '\0') {
			initials.Append(toupper(name[0]), 1);
			const char* space = strchr(name, ' ');
			if (space != NULL && space[1] != '\0') {
				initials.Append(toupper(space[1]), 1);
			}
		} else {
			initials = "?";
		}
	}*/ /*else {
		initials = "?";
	}*/
	initials = "#";

	// Draw initials
	SetHighColor(255, 255, 255);
	BFont font;
	GetFont(&font);
	font.SetSize(kAvatarSize * 0.45f);
	font.SetFace(B_BOLD_FACE);
	SetFont(&font);

	font_height fh;
	font.GetHeight(&fh);
	float textWidth = StringWidth(initials.String());

	DrawString(initials.String(),
		BPoint(rect.left + (rect.Width() - textWidth) / 2,
			rect.top + (rect.Height() + fh.ascent - fh.descent) / 2));
}

rgb_color
ChatHeader::_AvatarColor() const
{
	//if (fContact == NULL)
	//	return kAvatarColors[0];

	// Generate consistent color based on name hash
	uint32 hash = 0;
	const char* name = "Name" /*fContact->name*/;
	while (*name) {
		hash = hash * 31 + (uint8)*name++;
	}
	return kAvatarColors[hash % kAvatarColorCount];
}

BSize
ChatHeader::MinSize()
{
	return BSize(200, kHeaderHeight);
}


BSize
ChatHeader::PreferredSize()
{
	return BSize(B_SIZE_UNLIMITED, kHeaderHeight);
}

