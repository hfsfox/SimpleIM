#include <View.h>

class ChatMediaView: public BView
{
	public:
		explicit ChatMediaView(const char* contact_name = "");
		virtual ~ChatMediaView();
	public:
		//virtual void Draw(BRect updateRect);
		virtual void AttachedToWindow();
	private:
		const char* _contact_name;
};
