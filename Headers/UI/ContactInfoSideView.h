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
		virtual void _DrawAvatar(BRect rect);
		rgb_color				_AvatarColor() const;
	private:
		BGroupView* fGroupView;
		BFont fFont;
		const char* _contact_name;
};
