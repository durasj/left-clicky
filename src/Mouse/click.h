/**
 * @author Inpsired by https://github.com/octalmage/robotjs from Jason Stallings under MIT license
 */

#include <napi.h>

#include "os.h"
#include "types.h"

#if defined(_MSC_VER)
	#include "ms_stdbool.h"
#else
	#include <stdbool.h>
#endif

namespace Mouse {
  MMPoint getMousePos(void);
  void toggleMouse(bool down);
  bool click();
  Napi::Boolean ClickWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
