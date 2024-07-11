#include "model.h"

namespace s21 {

//  Функция установки начального scale, который можно выставить с помощью value
int Model::ScaleData(DataT *data, double value) {
  int error = 0;
  if (data->matrix_) {
    if ((value < 0.01) || (value > 1))
      value = 0.5;  //  по умолчанию не должно выходить за эти рамки
    double scaleX = data->minMax_[1] - data->minMax_[0];
    double scaleY = data->minMax_[3] - data->minMax_[2];
    double scaleZ = data->minMax_[5] - data->minMax_[4];
    double Dmax = scaleX;
    if (scaleY > Dmax) {
      Dmax = scaleY;
    }
    if (scaleZ > Dmax) {
      Dmax = scaleZ;
    }
    double scale = (value - (value * (-1))) / Dmax;
    MultiplyMatrix(data, scale);
  } else {
    error = 1;
  }
  return error;
}

void Model::MultiplyMatrix(DataT *data, double value) {
  for (unsigned int i = 1; i < data->count_of_vertexes_ + 1; i++) {
    data->matrix_[i][0] *= value;
    data->matrix_[i][1] *= value;
    data->matrix_[i][2] *= value;
  }
}

}  //  namespace s21
