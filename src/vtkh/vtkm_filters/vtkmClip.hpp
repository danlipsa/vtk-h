#ifndef VTK_H_VTKM_CLIP_HPP
#define VTK_H_VTKM_CLIP_HPP

#include <vtkm/cont/DataSet.h>
#include <vtkm/filter/FieldSelection.h>
#include <vtkm/cont/ImplicitFunctionHandle.h>

namespace vtkh
{

class vtkmClip
{
public:
  vtkm::cont::DataSet Run(vtkm::cont::DataSet &input,
                          vtkm::cont::ImplicitFunctionHandle func,
                          vtkm::Id activeCellSet,
                          bool invert,
                          vtkm::filter::FieldSelection map_fields);
};
}
#endif
