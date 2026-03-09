#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <String.h>
#include <ObjectList.h>

enum
{
	CONTACT_DIRECT,
	CONTACT_CHANNEL,
	CONTACT_SUBCHANNEL
};

/*class Contact
{
};*/

struct Contact
{
	uint32 id; // contact identifier
	uint32 contact_type; // contact type, dm, group, subchat, etc.
	BString name; // displayed name
	uint32 last_activity; // last activity timestamp
	Contact()
	:
	name(""), id(0), contact_type(CONTACT_DIRECT), last_activity(0)
	{
	}
};

#endif
