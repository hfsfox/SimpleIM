#include "UI/ContactInfoSideView.h"
#include "UI/Views/AvatarView.h"
#include "UI/Views/ChatMediaView.h"
#include "Core/Contact.h"
#include <SpaceLayoutItem.h>
#include <Catalog.h>

#undef  B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT          "ConactInfoSideView"

// Layout constants
static const float kPanelMinWidth = 200.0f;
static const float kAvatarSize = 64.0f;
static const float kMargin = 12.0f;
static const float kRowHeight = 20.0f;

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

//Contact contact;

ContactInfoSideView::ContactInfoSideView(const char* name)
	:
	BView(name, B_WILL_DRAW),
	_contact_name(name)
	{
		
		SetExplicitMinSize(BSize(kPanelMinWidth,B_SIZE_UNSET));
		SetExplicitMaxSize(BSize(kPanelMinWidth,B_SIZE_UNSET));
		SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
		
		/*
		fGroupView = new BGroupView("g_stat_view", B_VERTICAL, 1);
		fGroupView->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	 	fGroupView->GroupLayout()->SetInsets(8);
		this->AddChild(fGroupView);
		
		fGroupView->GetFont(&fFont);
		fFont.SetSize(fFont.Size() * 0.9);
		fFont.SetFace(B_BOLD_FACE);
		
		BGroupLayout *vertLayout = new BGroupLayout(B_VERTICAL);
		vertLayout->SetInsets(0, 0, 0, 0);
		SetLayout(vertLayout);
		
		AvatarView* av = new AvatarView("Name");
		
		fGroupView->AddChild(av);
		
		BStringView *nameTitle = new BStringView("name", B_TRANSLATE("Name:"));
		nameTitle->SetFont(&fFont, B_FONT_FACE);
		nameTitle->SetAlignment(B_ALIGN_CENTER);
		
		fGroupView->AddChild(nameTitle);
		
		BStringView *lastSeemTitle = new BStringView("last_seem", B_TRANSLATE("Last seem:"));
		lastSeemTitle->SetFont(&fFont, B_FONT_FACE);
		lastSeemTitle->SetAlignment(B_ALIGN_CENTER);
		
		fGroupView->AddChild(lastSeemTitle);
		
		BStringView *statusTitle = new BStringView("status", B_TRANSLATE("Status:"));
		statusTitle->SetFont(&fFont, B_FONT_FACE);
		statusTitle->SetAlignment(B_ALIGN_CENTER);
		
		fGroupView->AddChild(statusTitle);
		
		ChatMediaView* cmv = new ChatMediaView("contact");
		
		fGroupView->AddChild(cmv);
		
		
		//fGroupView->AddChild(BSpaceLayoutItem::CreateGlue());
		
		BView *child;
		if ( child = fGroupView->ChildAt(0) )
		{
			while ( child )
			{
				child->SetFont(&fFont, B_FONT_SIZE);
				child = child->NextSibling();
			}
		}
		*/
	}
	
ContactInfoSideView::~ContactInfoSideView()
{
}

void
ContactInfoSideView::Draw(BRect updateRect)
{
	BRect bounds = Bounds();
	rgb_color base = LowColor();

	BView::Draw(bounds & updateRect);
	be_control_look->DrawBorder(this, bounds, updateRect, base, B_PLAIN_BORDER, 0, BControlLook::B_LEFT_BORDER);
	
	//Contact* contact = {.name = "", .id= 0, .contact_type = CONTACT_DIRECT, .last_visibility= 0};
	
	/*
	if (NULL/contact == NULL//fContact == NULL && !fIsChannel/)
	{
		// No contact selected
		BFont font;
		GetFont(&font);
		font.SetSize(12);
		SetFont(&font);

		font_height fh;
		font.GetHeight(&fh);

		SetHighColor(/LabelColor()/tint_color(ui_color(B_PANEL_TEXT_COLOR), B_LIGHTEN_1_TINT));
		const char* hint = "Select a contact";
		float tw = StringWidth(hint);
		DrawString(hint,
			BPoint((rect.Width() - tw) / 2,
				rect.top + 40 + fh.ascent));
		return;
	}
	*/
	float x = bounds.left + kMargin;
	float y = bounds.top + kMargin;
	float contentWidth = bounds.Width() - kMargin * 2;

	// === Avatar (centered) ===
	float avatarX = x + (contentWidth - kAvatarSize) / 2;
	BRect avatarRect(avatarX, y, avatarX + kAvatarSize, y + kAvatarSize);
	_DrawAvatar(avatarRect);
	y += kAvatarSize + kMargin;

	// === Name (centered, bold) ===
	BFont nameFont;
	GetFont(&nameFont);
	nameFont.SetSize(be_plain_font->Size() +2/* * kFontScaleLarge*/);
	nameFont.SetFace(B_BOLD_FACE);
	SetFont(&nameFont);

	font_height nameFh;
	nameFont.GetHeight(&nameFh);
	
	const char* displayName;
	/*
	if (fIsChannel) {
		displayName = "Public Channel";
		SetHighColor(AccentColor());
	} else {
		displayName = fContact->name[0] ? fContact->name : "Unknown";
		SetHighColor(TextColor());
	}
	*/

	displayName = _contact_name;
	float nameWidth = StringWidth(displayName);
	float nameX = x + (contentWidth - nameWidth) / 2;
	if (nameX < x)
		nameX = x;
	DrawString(displayName, BPoint(nameX, y + nameFh.ascent));
	y += nameFh.ascent + nameFh.descent + 4;
	
}

rgb_color
ContactInfoSideView::_AvatarColor() const
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

void
ContactInfoSideView::_DrawAvatar(BRect rect)
{
	rgb_color avatarColor = _AvatarColor();
	SetHighColor(avatarColor);
	FillEllipse(rect);
}

