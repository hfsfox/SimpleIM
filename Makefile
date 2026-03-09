NAME = Messenger
TYPE = APP
SRCS = \
	Sources/main.cpp \
	Sources/UI/MainWindow.cpp \
	Sources/UI/ChatView.cpp \
	Sources/UI/ChatHeader.cpp \
	Sources/UI/ContactItem.cpp \
	Sources/UI/FolderItem.cpp \
	Sources/UI/ContactInfoSideView.cpp \
	Sources/UI/Views/AvatarView.cpp \
	Sources/UI/Views/ChatMediaView.cpp \
	Sources/UI/Deskbar/DeskbarReplicant.cpp \
	Sources/Core/Contact.cpp
RDEFS = Resources/Resource.rdef
LIBS = root be media tracker localestub $(STDCPPLIBS)
SYSTEM_INCLUDE_PATHS = \
	$(shell finddir B_SYSTEM_HEADERS_DIRECTORY)/private/interface
LOCAL_INCLUDE_PATHS = \
	./Headers
OPTIMIZE := FULL
WARNINGS = ALL
SYMBOLS := FALSE
DEBUGGER := FALSE
## Include the Makefile-Engine
DEVEL_DIRECTORY := /boot/system/develop
include $(DEVEL_DIRECTORY)/etc/makefile-engine
