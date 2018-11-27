# src/

# include settings
#INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/lib)
#INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/lib/include)
INCLUDE_DIRECTORIES(${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include)

# lib settings
LINK_DIRECTORIES(${${CMAKE_PROJECT_NAME}_BINARY_DIR}/lib)


# all related files
AUX_SOURCE_DIRECTORY(. DIR_TARGET)
ADD_LIBRARY (relfiles ${DIR_TARGET})


ADD_EXECUTABLE(drtrain drtrain.cc)

#  executable dependencies
#ADD_DEPENDENCIES(svmus svm)


#  executable target links
TARGET_LINK_LIBRARIES(drtrain relfiles)
TARGET_LINK_LIBRARIES(drtrain m)

#  executable properties
SET_TARGET_PROPERTIES(drtrain PROPERTIES OUTPUT_NAME "drtrain")



ADD_EXECUTABLE(drtest drtest.cc)

TARGET_LINK_LIBRARIES(drtest relfiles)
TARGET_LINK_LIBRARIES(drtest m)


SET_TARGET_PROPERTIES(drtest PROPERTIES OUTPUT_NAME "drtest")

