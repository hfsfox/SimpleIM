#include "UI/Views/AvatarView.h"


#include <Font.h>
#include <LayoutUtils.h>

static const float kHeaderHeight = 56.0f;
static const float kAvatarSize = 64.0f;
static const float kMargin = 12.0f;

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

AvatarView::AvatarView(const char* contact_name)
	:
	BView(contact_name, B_WILL_DRAW | B_FULL_UPDATE_ON_RESIZE),
	_contact_name(contact_name)
	{
		//SetViewColor(kHeaderBg);
		//SetExplicitMinSize(BSize(200,kAvatarSize));
		//float iconSize = height.ascent + height.descent + 2.0f;
		
		//SetExplicitMinSize(BSize(64/*iconSize*/, B_SIZE_UNSET));
		//SetExplicitMaxSize(BSize(64/*iconSize*/, B_SIZE_UNSET));
		//SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	}
	
AvatarView::~AvatarView()
{
}

void
AvatarView::AttachedToWindow()
{
	BView::AttachedToWindow();
	if (Parent() != NULL)
		SetViewColor(Parent()->ViewColor());
	//SetViewColor(kHeaderBg);
	//SetViewColor(tint_color(ui_color(B_PANEL_BACKGROUND_COLOR), B_LIGHTEN_1_TINT));
	SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
}


void
AvatarView::Draw(BRect updateRect)
{
	BRect bounds = Bounds();
	
	float x = bounds.left + kMargin;
	float y = bounds.top + kMargin;
	float contentWidth = bounds.Width() - kMargin * 2;
	float avatarX = x + (contentWidth - kAvatarSize) / 2;
	BRect avatarRect(avatarX, y, avatarX + kAvatarSize, y + kAvatarSize);

	/*
	BRect avatarRect(
		kMargin,
		(bounds.Height() - kAvatarSize) / 2,
		kMargin + kAvatarSize,
		(bounds.Height() + kAvatarSize) / 2
	);
	*/
	
	_DrawAvatar(avatarRect);
}

void
AvatarView::_DrawAvatar(BRect rect)
{
	rgb_color avatarColor = _AvatarColor();
	SetHighColor(avatarColor);
	FillEllipse(rect);
}


rgb_color
AvatarView::_AvatarColor() const
{
	//if (fContact == NULL)
	//	return kAvatarColors[0];

	// Generate consistent color based on name hash
	uint32 hash = 0;
	const char* name = _contact_name;
	while (*name) {
		hash = hash * 31 + (uint8)*name++;
	}
	return kAvatarColors[hash % kAvatarColorCount];
}

BSize
AvatarView::MinSize()
{
	return BSize(200, kHeaderHeight);
}


BSize
AvatarView::PreferredSize()
{
	//return BSize(B_SIZE_UNLIMITED, kHeaderHeight);
	return BSize(20, 70);
}

