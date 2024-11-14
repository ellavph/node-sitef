{
  "targets": [
    {
      "target_name": "node-sitef",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 },
      },
      "conditions": [
        [
          'OS=="win"',
          {
            "defines": [
              "_HAS_EXCEPTIONS=1"
              ]
          }
        ]
      ],
      "sources": [
        "lib/promises/*",
        "lib/nodesitef.hpp",
        "lib/nodesitef.cpp"
      ],
      "include_dirs": [
        "/home/phillipi/PycharmProjects/node-sitef/node_modules/node-addon-api"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
