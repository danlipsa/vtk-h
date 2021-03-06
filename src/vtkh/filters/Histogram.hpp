#ifndef VTK_H_HISTOGRAM_HPP
#define VTK_H_HISTOGRAM_HPP

#include <vtkh/vtkh.hpp>
#include <vtkh/filters/Filter.hpp>
#include <vtkh/DataSet.hpp>

#include <vector>

namespace vtkh
{

class Histogram
{
public:
  Histogram();
  virtual ~Histogram();

  struct HistogramResult
  {
    vtkm::cont::ArrayHandle<vtkm::Id> m_bins;
    vtkm::Range m_range;
    vtkm::Float64 m_bin_delta;
    void Print();
  };

  HistogramResult Run(vtkh::DataSet &data_set, const std::string &field_name);
  void SetRange(const vtkm::Range &range);
  void SetNumBins(const int num_bins);
protected:
  int m_num_bins;
  vtkm::Range m_range;
};

} //namespace vtkh
#endif
