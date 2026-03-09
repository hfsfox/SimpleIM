#include <View.h>
#include <Size.h>
#include <String.h>

class ChatHeader : public BView
{
	public:
		explicit ChatHeader(const char* name = "");
		virtual ~ChatHeader();

		virtual void			Draw(BRect updateRect);
		virtual void			AttachedToWindow();
		virtual BSize			MinSize();
		virtual BSize			PreferredSize();
		virtual void			_DrawAvatar(BRect rect);
		rgb_color				_AvatarColor() const;
	private:
		BString fDisplayName;
		BString fStatus;
		bool isOnline;
		bool fIsChannel;
};
