#include <View.h>
#include <GroupView.h>
#include <String.h>
#include <StringView.h>
#include <Font.h>
#include <ControlLook.h>

class ContactInfoSideView: public BView
{
	public:
		explicit ContactInfoSideView(const char* name = "contact_side_info_view");
		virtual ~ContactInfoSideView();
	public:
		void Draw(BRect updateRect);
		
	private:
		BGroupView* fGroupView;
		BFont fFont;
};
