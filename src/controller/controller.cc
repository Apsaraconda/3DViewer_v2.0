#include "controller/controller.h"

namespace s21 {

int Controller::Parsing(char* str, DataT* data) {
  int error = model_->ParsingPub(str);
  if (!error) *data = *model_->GetData();
  return error;
}
int Controller::CountsItoA(unsigned int data, char* result) {
  int error = model_->CountsItoA(data, result);
  return error;
}

void Controller::MultiplyMatrix(DataT* data, double value) {
  model_->MultiplyMatrixPub(value);
  *data = *model_->GetData();
}

void Controller::MoveModel(DataT* data, double number, int axis) {
  model_->MoveModelPub(number, axis);
  *data = *model_->GetData();
}

void Controller::RotationModel(DataT* data, double angle, int axis) {
  model_->RotationModelPub(angle, axis);
  *data = *model_->GetData();
}

int Controller::ScaleData(DataT* data, double value) {
  int error = model_->ScaleDataPub(value);
  if (!error) *data = *model_->GetData();
  return error;
}
int Controller::CenterData(DataT* data) {
  int error = model_->CenterDataPub();
  if (!error) *data = *model_->GetData();
  return error;
}

DataT* Controller::GetData() { return model_->GetData(); }

SettingsT* Controller::GetSettings() { return model_->GetSettings(); }

int Controller::OpenFile(char* str, DataT* data, SettingsT* settings) {
  int error = model_->OpenFile(str);
  if (!error) {
    *data = *model_->GetData();
    *settings = *model_->GetSettings();
  }
  return error;
}

void Controller::LoadSettings(SettingsT* settings) {
  model_->LoadSettings();
  *settings = *model_->GetSettings();
}

}  // namespace s21
