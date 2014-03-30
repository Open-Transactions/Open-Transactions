#ifndef _H_OT_ME_SWITCH
#define _H_OT_ME_SWITCH


#ifdef OT_USE_SCRIPT_CHAI
// USE_OLD_CHAISCRIPT == 0   This will use the C++ conversion of the Chaiscript in OT_ME, OT command line, and otapitest unit tests
// USE_OLD_CHAISCRIPT == 1   This will use the original Chaiscript in OT_ME, OT command line, and otapitest unit tests
#define USE_OLD_CHAISCRIPT  0
#else
// DO NOT CHANGE THIS ONE! WHen Chaiscript is not included we always have to use the C++ code
#define USE_OLD_CHAISCRIPT  0
#endif

#endif
