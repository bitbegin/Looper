
set (SOURCES
    "Message/Message.cpp"
    "MessageQueue/MessageQueue.cpp"
    "LooperManager/LooperManager.cpp"
    "Looper/Looper.cpp"
    "Handler/Handler.cpp"
    "HandlerThread/HandlerThread.cpp"
)

set (HEADERS
    "Message/Message.h"
    "Message/HandlerCallBack.h"
    "MessageQueue/MessageQueue.h"
    "LooperManager/LooperManager.h"
    "LooperManager/LooperBase.h"
    "Looper/Looper.h"
    "Handler/Handler.h"
    "HandlerThread/HandlerThread.h"
)


add_library(LooperLib STATIC ${SOURCES} ${HEADERS})

target_include_directories(LooperLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Message/
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageQueue/
        ${CMAKE_CURRENT_SOURCE_DIR}/LooperManager/
        ${CMAKE_CURRENT_SOURCE_DIR}/Looper/
        ${CMAKE_CURRENT_SOURCE_DIR}/Handler/
        ${CMAKE_CURRENT_SOURCE_DIR}/HandlerThread/
)

