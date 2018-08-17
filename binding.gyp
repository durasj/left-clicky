{
    "targets": [{
        "target_name": "left-clicky",

        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],

        "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],

        "libraries": [],

        "dependencies": [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],

        "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],

        "conditions": [
            ["OS == 'mac'", {
                "include_dirs": [
                    "System/Library/Frameworks/CoreFoundation.Framework/Headers",
                    "System/Library/Frameworks/Carbon.Framework/Headers",
                    "System/Library/Frameworks/ApplicationServices.framework/Headers",
                    "System/Library/Frameworks/OpenGL.framework/Headers",
                ],

                "link_settings": {
                    "libraries": [
                        "-framework Carbon",
                        "-framework CoreFoundation",
                        "-framework ApplicationServices",
                        "-framework OpenGL"
                    ]
                },

                "defines": ["IS_MAC"]
            }],

            ["OS == 'linux'", {
                "link_settings": {
                    "libraries": [
                        "-lpng",
                        "-lz",
                        "-lX11",
                        "-lXtst"
                    ]
                },

                "sources": [
                    "src/xdisplay.c"
                ],

                "defines": ["IS_LINUX"]
            }],

            ["OS == 'win'", {
                "defines": ["IS_WINDOWS"]
            }]
        ],

        "sources": [
            "src/main.cpp",
            "src/Mouse/click.cpp"
        ],
    }]
}