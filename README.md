# left-clicky
Basic Node.js synthetic left mouse click event working on Windows, Mac, and Linux.

Heavily inspired (parts of the native code reused) by the [robotjs](http://robotjs.io/) written by the [Jason Stallings](https://github.com/octalmage) under MIT license. Differences:

* Just left mouse click - nothing more.
* Implements N-API, specifically [node-addon-api](https://www.npmjs.com/package/node-addon-api) - no rebuilding, no messing around with gyp!
