set_global_assignment -entity "DE10_Lite_SOPC" -library "lib_DE10_Lite_SOPC" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "DE10_Lite_SOPC" -library "lib_DE10_Lite_SOPC" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "DE10_Lite_SOPC" -library "lib_DE10_Lite_SOPC" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_DE10_Lite_SOPC" -name SPD_FILE [file join $::quartus(sip_path) "../DE10_Lite_SOPC.spd"]
set_global_assignment -library "lib_DE10_Lite_SOPC" -name MISC_FILE [file join $::quartus(sip_path) "../../DE10_Lite_SOPC.qsys"]

set_global_assignment -library "lib_DE10_Lite_SOPC" -name MISC_FILE [file join $::quartus(sip_path) "DE10_Lite_SOPC.v"]
set_global_assignment -library "lib_DE10_Lite_SOPC" -name MISC_FILE [file join $::quartus(sip_path) "submodules/DE10_Lite_SOPC_LCD_RESET_N.v"]
