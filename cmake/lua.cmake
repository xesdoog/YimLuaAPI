include(FetchContent)

message("Lua")
FetchContent_Declare(
    Lua
    GIT_REPOSITORY https://github.com/walterschell/Lua.git
    GIT_TAG 504ef66d500fa1fb4f1684b6617b01342eee704a
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Lua)

set_property(TARGET lua_static PROPERTY CXX_STANDARD 23)
