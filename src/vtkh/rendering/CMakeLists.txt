#==============================================================================
# See License.txt
#==============================================================================
set(vtkh_rendering_headers
  Annotator.hpp
  Image.hpp
  ImageCompositor.hpp
  LineRenderer.hpp
  MeshRenderer.hpp
  RayTracer.hpp
  Render.hpp
  Renderer.hpp
  PointRenderer.hpp
  Scene.hpp
  VolumeRenderer.hpp
  compositing/Compositor.hpp
  compositing/PartialCompositor.hpp
  compositing/AbsorptionPartial.hpp
  compositing/EmissionPartial.hpp
  compositing/VolumePartial.hpp
  )

set(vtkh_rendering_sources
  Annotator.cpp
  Image.cpp
  LineRenderer.cpp
  MeshRenderer.cpp
  RayTracer.cpp
  Render.cpp
  Renderer.cpp
  PointRenderer.cpp
  Scene.cpp
  VolumeRenderer.cpp
  compositing/Compositor.cpp
  compositing/PartialCompositor.cpp
  )


set(vtkh_rendering_deps vtkh_core vtkh_utils vtkh_filters)

if(VTKm_CUDA_FOUND)
    # triggers cuda compile
    list(APPEND vtkh_rendering_deps cuda)
endif()

if(ENABLE_OPENMPJ)
    list(APPEND vtkh_rendering_deps openmp)
endif()

blt_add_library(
  NAME vtkh_rendering
  SOURCES ${vtkh_rendering_sources}
  HEADERS ${vtkh_rendering_headers}
  DEPENDS_ON ${vtkh_rendering_deps}
  )

vtkm_add_target_information(vtkh_rendering DEVICE_SOURCES ${vtkh_rendering_sources})

if(ENABLE_OPENMP)
    blt_add_target_compile_flags(TO vtkh_rendering FLAGS "-DVTKH_USE_OPENMP")
endif()


# Install libraries
install(TARGETS vtkh_rendering
  EXPORT ${VTKh_EXPORT_NAME}
  ARCHIVE DESTINATION ${VTKh_INSTALL_LIB_DIR}
  LIBRARY DESTINATION ${VTKh_INSTALL_LIB_DIR}
  RUNTIME DESTINATION ${VTKh_INSTALL_BIN_DIR}
  )

# Install headers
install(FILES ${vtkh_rendering_headers}
  DESTINATION ${VTKh_INSTALL_INCLUDE_DIR}/vtkh/rendering)


#------------------------------------------------------------------------------
# Handle parallel library
#------------------------------------------------------------------------------
set(vtkh_rendering_mpi_headers
  compositing/DirectSendCompositor.hpp
  compositing/DIYCompositor.hpp
  compositing/MPICollect.hpp
  compositing/RadixKCompositor.hpp
  compositing/vtkh_diy_collect.hpp
  compositing/vtkh_diy_image_block.hpp
  compositing/vtkh_diy_utils.hpp
  compositing/PartialCompositor.hpp
  )

set(vtkh_rendering_mpi_sources
  compositing/DIYCompositor.cpp
  compositing/DirectSendCompositor.cpp
  compositing/RadixKCompositor.cpp
  compositing/PartialCompositor.cpp
  )

if (MPI_FOUND)

    set(vtkh_rendering_mpi_deps vtkh_core_mpi vtkh_utils_mpi vtkh_filters_mpi )

    # necessary b/c of how find_cuda works
    if(CUDA_FOUND)
         # triggers cuda compile
         list(APPEND vtkh_rendering_mpi_deps cuda)
    endif()

    if(ENABLE_OPENMP)
         list(APPEND vtkh_rendering_mpi_deps openmp)
    endif()

    blt_add_library(
        NAME vtkh_rendering_mpi
        SOURCES ${vtkh_rendering_sources} ${vtkh_rendering_mpi_sources}
        HEADERS ${vtkh_rendering_headers} ${vtkh_rendering_mpi_headers}
        DEPENDS_ON ${vtkh_rendering_mpi_deps}
    )

    vtkm_add_target_information(vtkh_rendering_mpi DEVICE_SOURCES ${vtkh_rendering_sources})

    if(ENABLE_OPENMP)
      blt_add_target_compile_flags(TO vtkh_rendering_mpi FLAGS "-DVTKH_USE_OPENMP")
    endif()

    blt_add_target_compile_flags(TO vtkh_rendering_mpi FLAGS "-D VTKH_PARALLEL")

    # Install libraries
    install(TARGETS vtkh_rendering_mpi
            EXPORT ${VTKh_EXPORT_NAME}
            ARCHIVE DESTINATION ${VTKh_INSTALL_LIB_DIR}
            LIBRARY DESTINATION ${VTKh_INSTALL_LIB_DIR}
            RUNTIME DESTINATION ${VTKh_INSTALL_BIN_DIR})

    # Install headers
    install(FILES ${ParallelHeaders}
            DESTINATION ${VTKh_INSTALL_INCLUDE_DIR}/vtkh/rendering)

endif()
