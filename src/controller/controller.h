#ifndef CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  Controller(Model* m) : model_(m){};
  int Parsing(char* str, DataT* data);
  int CountsItoA(unsigned int data, char* result);
  void MultiplyMatrix(DataT* data, double value);
  void MoveModel(DataT* data, double number, int axis);
  void RotationModel(DataT* data, double angle, int axis);
  int ScaleData(DataT* data, double value);
  int CenterData(DataT* data);
  int OpenFile(char* str, DataT* data, SettingsT* settings);
  void LoadSettings(SettingsT* settings);
  DataT* GetData();
  SettingsT* GetSettings();

 private:
  Model* model_;
};
}  // namespace s21

#endif  //  CPP4_3DVIEWER_V_2_0_SRC_CONTROLLER_CONTROLLER_H
