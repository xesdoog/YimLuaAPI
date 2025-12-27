include(FetchContent)

FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG        61c944895e071872370219cadade8423dc6e04dc
    GIT_PROGRESS TRUE
) 
message("pugixml")
FetchContent_MakeAvailable(pugixml)
set_property(TARGET pugixml PROPERTY CXX_STANDARD 23)
