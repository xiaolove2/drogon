link_libraries(drogon trantor pthread dl)

add_executable(cache_map_test CacheMapTest.cc)
add_executable(cache_map_test2 CacheMapTest2.cc)
add_executable(cookies_test CookiesTest.cc)
add_executable(class_name_test ClassNameTest.cc)
add_executable(sha1_test Sha1Test.cc)
add_executable(view_data_test HttpViewDataTest.cc)

