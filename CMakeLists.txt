project(simplex-framework)

file (GLOB MODULES "modules/*")

foreach ( MODULE ${MODULES} )
  include_directories ( "${MODULE}/include/" )
endforeach ()

foreach ( MODULE ${MODULES} )
  message(${MODULE})
  add_subdirectory ( "${MODULE}" )
endforeach ()