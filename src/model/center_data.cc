#include "model.h"

namespace s21 {

int Model::CenterData(DataT* data) {
  int error = 0;
  if (data->matrix_) {
    double centerX =
        data->minMax_[0] + (data->minMax_[1] - data->minMax_[0]) / 2;
    double centerY =
        data->minMax_[2] + (data->minMax_[3] - data->minMax_[2]) / 2;
    double centerZ =
        data->minMax_[4] + (data->minMax_[5] - data->minMax_[4]) / 2;
    for (unsigned int i = 1; i < data->count_of_vertexes_ + 1; i++) {
      data->matrix_[i][0] -= centerX;
      data->matrix_[i][1] -= centerY;
      data->matrix_[i][2] -= centerZ;
    }
  } else {
    error = 1;
  }
  return error;
}

}  //  namespace s21
