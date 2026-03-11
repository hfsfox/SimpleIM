#include <View.h>

class AvatarView: public BView
{
	public:
		explicit AvatarView(const char* contact_name = "");
		virtual ~AvatarView();
	public:
		void Draw(BRect updateRect);
		virtual void			AttachedToWindow();
		//virtual BSize			MinSize();
		virtual BSize			PreferredSize();
		virtual void			_DrawAvatar(BRect rect);
		rgb_color				_AvatarColor() const;
	private:
		const char* _contact_name;
};
