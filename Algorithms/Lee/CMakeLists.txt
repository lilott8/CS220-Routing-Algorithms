#set(LEE_SOURCES *.cpp)
file(GLOB LEE_SOURCES
"*.h"
"*.cpp"
)

#Add any files in this directory
add_library(LEE ${LEE_SOURCES})