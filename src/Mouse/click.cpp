#include "click.h"

#if defined(IS_MAC)
	#include <ApplicationServices/ApplicationServices.h>
#elif defined(IS_LINUX)
	#include <X11/Xlib.h>
	#include <X11/extensions/XTest.h>
	#include <stdlib.h>
	#include "xdisplay.h"
#endif

/**
 * Get mouse position
 * @author Inpsired by https://github.com/octalmage/robotjs from Jason Stallings under MIT license
 */
MMPoint Mouse::getMousePos()
{
#if defined(IS_MAC)
  CGEventRef event = CGEventCreate(NULL);
  CGPoint point = CGEventGetLocation(event);
  CFRelease(event);

  return MMPointFromCGPoint(point);
#elif defined(IS_LINUX)
  int x, y; /* This is all we care about. Seriously. */
  Window garb1, garb2; /* Why you can't specify NULL as a parameter */
  int garb_x, garb_y;  /* is beyond me. */
  unsigned int more_garbage;

  Display *display = XGetMainDisplay();
  XQueryPointer(display, XDefaultRootWindow(display), &garb1, &garb2,
                &x, &y, &garb_x, &garb_y, &more_garbage);

  return MMPointMake(x, y);
#elif defined(IS_WINDOWS)
  POINT point;
  GetCursorPos(&point);

  return MMPointFromPOINT(point);
#endif
}

/**
 * Press down a button, or release it.
 * @param down   True for down, false for up.
 * @author Inpsired by https://github.com/octalmage/robotjs from Jason Stallings under MIT license
 */
void Mouse::toggleMouse(bool down)
{
  #if defined(IS_MAC)
    const CGPoint currentPos = CGPointFromMMPoint(getMousePos());
    const CGEventType mouseType = (down ? kCGEventLeftMouseDown : kCGEventLeftMouseUp);
    CGEventRef event = CGEventCreateMouseEvent(NULL,
                                              mouseType,
                                              currentPos,
                                              (CGMouseButton)kCGMouseButtonLeft);
    CGEventPost(kCGSessionEventTap, event);
    CFRelease(event);
  #elif defined(IS_LINUX)
    Display *display = XGetMainDisplay();
    XTestFakeButtonEvent(display, 1, down ? True : False, CurrentTime);
    XSync(display, false);
  #elif defined(IS_WINDOWS)
    mouse_event((down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP), 0, 0, 0, 0);
  #endif
}

bool Mouse::click() {
  Mouse::toggleMouse(true);
  Mouse::toggleMouse(false);

  return true;
}

Napi::Boolean Mouse::ClickWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();
  Napi::Boolean returnValue = Napi::Boolean::New(env, Mouse::click());

  return returnValue;
}

Napi::Object Mouse::Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set(
    "click", Napi::Function::New(env, Mouse::ClickWrapped)
  );
 
  return exports;
}
