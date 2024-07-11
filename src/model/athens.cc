#include "model.h"

namespace s21 {

// двигает модель на величину number вдоль оси axis (0-2)
void Model::MoveModel(DataT* data, double number, int axis) {
  for (unsigned int i = 1; i <= data->count_of_vertexes_; i++) {
    data->matrix_[i][axis] += number;
  }
}

// масштабирует модель умножением на коэффициерт К, вдоль оси axis (0-2)
// выдает 0, если все норм, 1 - если коэффициент К=0.
int Model::ScalingModel(DataT* data, double K, int axis) {
  int res = 0;
  if (K != 0) {
    for (unsigned int i = 1; i <= data->count_of_vertexes_; i++) {
      data->matrix_[i][axis] *= K;
    }
  } else {
    res = 1;
  }
  return res;
}

// поворачивает модель на заданный угол в противочасовую относительно оси axis
// поворот в градусах
void Model::RotationModel(DataT* data, double angle, int axis) {
  angle = angle / 180 * S21_PI;
  unsigned int coord[2] = {0};
  int c = 0;
  for (int j = 0; j < 3; j++) {
    if (j != axis) {
      coord[c] = j;
      c++;
    }
  }
  double A = cos(angle);
  double B = sin(angle);
  for (unsigned int i = 1; i <= data->count_of_vertexes_; i++) {
    double value_1 = data->matrix_[i][coord[0]];
    double value_2 = data->matrix_[i][coord[1]];
    data->matrix_[i][coord[0]] = A * value_1 + B * value_2;
    data->matrix_[i][coord[1]] = -B * value_1 + A * value_2;
  }
}

}  //  namespace s21
