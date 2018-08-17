#include <napi.h>
#include "Mouse/click.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Mouse::Init(env, exports);
}

NODE_API_MODULE(left_clicky, InitAll)
