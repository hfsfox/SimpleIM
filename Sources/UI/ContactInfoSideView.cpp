#include "UI/ContactInfoSideView.h"
#include <SpaceLayoutItem.h>
#include <Catalog.h>

#undef  B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT          "ConactInfoSideView"

ContactInfoSideView::ContactInfoSideView(const char* name)
	:
	BView(name, B_WILL_DRAW)
	{
		SetExplicitMinSize(BSize(32,32));
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
}

