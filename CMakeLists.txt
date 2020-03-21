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
add_subdirectory(bitcount) #Nice one
#add_subdirectory(blowfish) #Too big
add_subdirectory(crc)
#add_subdirectory(dijkstra) #TOO Big
add_subdirectory(fft) # Nice one
add_subdirectory(limits)
#add_subdirectory(lzfx) #Too big
#add_subdirectory(overflow) #incomplete
#add_subdirectory(patricia) #Too big
add_subdirectory(picojpeg) #0.36sec
#add_subdirectory(qsort) #Too big
add_subdirectory(randmath)
#add_subdirectory(rc4) #Illiegal data requests
#add_subdirectory(regress) #ASM is not riscv
add_subdirectory(rsa)
#add_subdirectory(sha) #Too big
add_subdirectory(stringsearch) #Nice one
#add_subdirectory(susan) #Too big
#add_subdirectory(vcflags) #Incomplete

