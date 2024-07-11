#include "model.h"

namespace s21 {

//  Функция установки начального scale, который можно выставить с помощью value
void Model::MultiplyMatrixPub(double value) {
  MultiplyMatrix(port_data_, value);
}

void Model::RotationModelPub(double angle, int axis) {
  RotationModel(port_data_, angle, axis);
}

void Model::MoveModelPub(double number, int axis) {
  MoveModel(port_data_, number, axis);
}

int Model::ParsingPub(char* str) {
  int error = Parsing(str, port_data_);
  return error;
}

int Model::ScaleDataPub(double value) {
  int error = ScaleData(port_data_, value);
  return error;
}

int Model::ScalingModelPub(double K, int axis) {
  int error = ScalingModel(port_data_, K, axis);
  return error;
}

int Model::CenterDataPub() {
  int error = CenterData(port_data_);
  return error;
}

int Model::OpenFile(char* str) {
  int error = Parsing(str, port_data_);
  settings_data_->scale_ = 0.5;  //  Начальный scale
  settings_data_->currX_ = 100;  //  Начальные позиции ползунков перемещения
  settings_data_->currY_ = 100;
  settings_data_->currZ_ = 100;
  settings_data_->curr_angle_X_ = 180;  //  Начальные позиции ползунков вращения
  settings_data_->curr_angle_Y_ = 180;
  settings_data_->curr_angle_Z_ = 180;
  CenterData(port_data_);
  ScaleData(port_data_, settings_data_->scale_);
  //  Для увеличения масштаба при переключении на центральную проекцию
  //  обнуляем флаг Central_painting
  if (settings_data_->central_projection_)
    settings_data_->central_painting_ = 0;
  return error;
}

}  //  namespace s21
