#ifndef VTK_H_RENDERER_VOLUME_HPP
#define VTK_H_RENDERER_VOLUME_HPP

#include <vtkh/rendering/Renderer.hpp>
#include <vtkm/rendering/MapperVolume.h>

namespace vtkh {

class VolumeRenderer : public Renderer
{
public:
  VolumeRenderer();
  virtual ~VolumeRenderer();
  std::string GetName() const override;
  void SetNumberOfSamples(const int num_samples);
  static Renderer::vtkmCanvasPtr GetNewCanvas(int width = 1024, int height = 1024);

  void Update() override;
  virtual void SetColorTable(const vtkm::cont::ColorTable &color_table) override;
protected:
  virtual void Composite(const int &num_images) override;
  virtual void PreExecute() override;
  virtual void PostExecute() override;

  void CorrectOpacity();
  void FindVisibilityOrdering();
  void DepthSort(int num_domains,
                 std::vector<float> &min_depths,
                 std::vector<int> &local_vis_order);
  float FindMinDepth(const vtkm::rendering::Camera &camera,
                     const vtkm::Bounds &bounds) const;

  int m_num_samples;
  std::shared_ptr<vtkm::rendering::MapperVolume> m_tracer;
  vtkm::cont::ColorTable m_uncorrected_color_table;
  std::vector<std::vector<int>> m_visibility_orders;

};

} // namespace vtkh
#endif
