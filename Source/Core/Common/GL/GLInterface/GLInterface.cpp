// Copyright 2014 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <memory>

#include "Common/CommonFuncs.h"
#include "Common/GL/GLInterfaceBase.h"

#if defined(__APPLE__)
#include "Common/GL/GLInterface/AGL.h"
#elif defined(_WIN32)
#include "Common/GL/GLInterface/WGL.h"
#elif HAVE_X11
#if defined(USE_EGL) && USE_EGL
#include "Common/GL/GLInterface/EGLX11.h"
#else
#include "Common/GL/GLInterface/GLX.h"
#endif
#elif defined(USE_EGL) && USE_EGL && defined(USE_HEADLESS)
#include "Common/GL/GLInterface/EGL.h"
#elif ANDROID
#include "Common/GL/GLInterface/EGLAndroid.h"
#else
#error Platform doesnt have a GLInterface
#endif

std::unique_ptr<cInterfaceBase> HostGL_CreateGLInterface()
{
	#if defined(__APPLE__)
		return make_unique<cInterfaceAGL>();
	#elif defined(_WIN32)
		return make_unique<cInterfaceWGL>();
	#elif defined(USE_EGL) && defined(USE_HEADLESS)
		return make_unique<cInterfaceEGL>();
	#elif defined(HAVE_X11) && HAVE_X11
	#if defined(USE_EGL) && USE_EGL
		return make_unique<cInterfaceEGLX11>();
	#else
		return make_unique<cInterfaceGLX>();
	#endif
	#elif ANDROID
		return make_unique<cInterfaceEGLAndroid>();
	#else
		return nullptr;
	#endif
}
