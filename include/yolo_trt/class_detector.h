#ifndef CLASS_DETECTOR_H_
#define CLASS_DETECTOR_H_

#include <iostream>
#include <opencv2/opencv.hpp>

#include "API.h"

namespace yolo_trt {

struct Result {
  int id = -1;
  float prob = 0.f;
  cv::Rect rect;
};

typedef std::vector<Result> BatchResult;

enum ModelType {
  YOLOV2 = 0,
  YOLOV3,
  YOLOV2_TINY,
  YOLOV3_TINY,
  YOLOV4,
  YOLOV4_TINY,
  YOLOV5
};

enum Precision { INT8 = 0, FP16, FP32 };

struct Config {
  std::string file_model_cfg = "configs/yolov3.cfg";

  std::string file_model_weights = "configs/yolov3.weights";

  float detect_thresh = 0.9;
  float nms_thresh = 0.5;

  ModelType net_type = YOLOV3;

  Precision inference_precision = FP32;

  int gpu_id = 0;

  std::string calibration_image_list_file_txt =
      "configs/calibration_images.txt";
};

class API Detector {
 public:
  explicit Detector();

  ~Detector();

  void init(const Config &config);

  void detect(const std::vector<cv::Mat> &mat_image,
              std::vector<BatchResult> &vec_batch_result);

  void setNMSThresh(float m_nms_thresh);
  void setProbThresh(float m_prob_thresh);

 private:
  Detector(const Detector &);
  const Detector &operator=(const Detector &);
  class Impl;
  Impl *_impl;
};

}  // namespace yolo_trt
#endif  // !CLASS_QH_DETECTOR_H_