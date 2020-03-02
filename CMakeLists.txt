# hack to make sure the perfbench.* libraries compile
include_directories(
  ${CMAKE_SOURCE_DIR}/libs/bench_lib/inc
  ${CMAKE_SOURCE_DIR}/libs/stdio_lib/inc
  ${CMAKE_SOURCE_DIR}/libs/string_lib/inc
  ${CMAKE_SOURCE_DIR}/libs/sys_lib/inc
  .
)

add_subdirectory(aes)
#add_subdirectory(adpcm_encode) #Too big
add_subdirectory(basicmath) #Nice one
#add_subdirectory(dijkstra) #TOO Big
add_subdirectory(picojpeg) #Maybe nice
add_subdirectory(rsa)
add_subdirectory(stringsearch) #Nice one
#add_subdirectory(susan) #Too big
#add_subdirectory(patricia)
add_subdirectory(randmath)
#add_subdirectory(vcflags) #Incomplete

