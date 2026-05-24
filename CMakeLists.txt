cmake_minimum_required(VERSION 3.16)
project(remoting-source)


add_subdirectory(remoting)


add_custom_target(__release_all)
add_dependencies(__release_all _remoting_rfb_client)
add_dependencies(__release_all _remoting_rfb_node_desktop)

if(${WIN32})
   add_dependencies(__release_all _remoting_rdx_client)
endif()




