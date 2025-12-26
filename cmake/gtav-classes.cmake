
include(FetchContent)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/Mr-X-GTA/GTAV-Classes-1.git
    GIT_TAG        b74e688860b0df47d7ec87c1eb6227ee853fc90a
    GIT_PROGRESS TRUE
    SOURCE_SUBDIR "why" # FetchContent_Populate is depricated now, so we set this to a non existing directory.
)
message("GTAV-Classes")
FetchContent_MakeAvailable(gtav_classes)
