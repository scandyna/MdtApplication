
if(ENABLE_CORE_APPLICATION_FOR_NON_QT_USAGE)
  add_subdirectory(MyNonQtCoreLibrary)
endif()

if(ENABLE_GUI_APPLICATION_FOR_NON_QT_USAGE)
  add_subdirectory(MyNonQtGuiLibrary)
endif()
