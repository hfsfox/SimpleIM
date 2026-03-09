#include "UI/ContactInfoSideView.h"
#include "Core/Contact.h"
#include <SpaceLayoutItem.h>
#include <Catalog.h>

#undef  B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT          "ConactInfoSideView"

// Layout constants
static const float kPanelMinWidth = 160.0f;
static const float kAvatarSize = 64.0f;

//Contact contact;

ContactInfoSideView::ContactInfoSideView(const char* name)
	:
	BView(name, B_WILL_DRAW)
	{
		SetExplicitMinSize(BSize(kPanelMinWidth,B_SIZE_UNSET));
		SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
		
		fGroupView = new BGroupView("g_stat_view", B_VERTICAL, 1);
		fGroupView->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	 	fGroupView->GroupLayout()->SetInsets(8);
		this->AddChild(fGroupView);
		
		fGroupView->GetFont(&fFont);
		fFont.SetSize(fFont.Size() * 0.9);
		fFont.SetFace(B_BOLD_FACE);
		
		BGroupLayout *vertLayout = new BGroupLayout(B_VERTICAL);
		vertLayout->SetInsets(1, 0, 0, 0);
		SetLayout(vertLayout);
		
		BStringView *fileTitle = new BStringView("file", B_TRANSLATE("Name:"));
		fileTitle->SetFont(&fFont, B_FONT_FACE);
		fileTitle->SetAlignment(B_ALIGN_CENTER);
		
		fGroupView->AddChild(fileTitle);
		
		fGroupView->AddChild(BSpaceLayoutItem::CreateGlue());
		
		BView *child;
		if ( child = fGroupView->ChildAt(0) )
		{
			while ( child )
			{
				child->SetFont(&fFont, B_FONT_SIZE);
				child = child->NextSibling();
			}
		}
	}
	
ContactInfoSideView::~ContactInfoSideView()
{
}

void
ContactInfoSideView::Draw(BRect updateRect)
{
	BRect rect = Bounds();
	rgb_color base = LowColor();

	BView::Draw(rect & updateRect);
	be_control_look->DrawBorder(this, rect, updateRect, base, B_PLAIN_BORDER, 0, BControlLook::B_LEFT_BORDER);
	
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
}

