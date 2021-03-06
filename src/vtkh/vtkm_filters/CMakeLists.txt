#==============================================================================
# See License.txt
#==============================================================================

set(vtkm_filters_headers
  vtkmCellAverage.hpp
  vtkmClip.hpp
  vtkmCleanGrid.hpp
  vtkmClipWithField.hpp
  vtkmExtractStructured.hpp
  vtkmLagrangian.hpp
  vtkmMarchingCubes.hpp
  vtkmPointAverage.hpp
  vtkmThreshold.hpp
  vtkmVectorMagnitude.hpp
  )

set(vtkm_filters_sources
  vtkmCellAverage.cpp
  vtkmClip.cpp
  vtkmCleanGrid.cpp
  vtkmClipWithField.cpp
  vtkmExtractStructured.cpp
  vtkmLagrangian.cpp
  vtkmMarchingCubes.cpp
  vtkmPointAverage.cpp
  vtkmThreshold.cpp
  vtkmVectorMagnitude.cpp
  )

# we use these specific vtk-m targets b/c our favorite version
# of cmake does not yet support transitive deps for object libs
set(vtkm_filters_deps  vtkm_compiler_flags vtkm_taotuple vtkm_diy )

if(ENABLE_OPENMP)
  list(APPEND vtkm_filters_deps openmp)
endif()

if(CUDA_FOUND)
    # triggers cuda compile
    list(APPEND vtkm_filters_deps cuda)
endif()

blt_add_library(
  NAME vtkm_compiled_filters
  SOURCES ${vtkm_filters_sources}
  HEADERS ${vtkm_filters_headers}
  DEPENDS_ON ${vtkm_filters_deps}
  OBJECT TRUE
  )

vtkm_add_target_information(vtkm_compiled_filters DEVICE_SOURCES ${vtkm_filter_sources})

if(CUDA_FOUND)
  # defend against vtkm code cuda can't reason about
  if(CMAKE_CUDA_COMPILER_VERSION VERSION_LESS 10.0.0)
    blt_add_target_compile_flags(TO vtkm_compiled_filters FLAGS "-DVTKH_BYPASS_VTKM_BIH")
  endif()
endif()
