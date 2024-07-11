
#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODEL_MODEL_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODEL_MODEL_H

#include <math.h>
#include <stdlib.h>

#include <QFile>
#include <QSettings>
#include <QString>
#include <iostream>
#include <set>

#define S21_PI 3.14159265358979323846264338327950288

//  Структура для хранения вершин и поверхностей модели
typedef struct {
  unsigned int count_of_vertexes_;  ///< Количество вершин в модели
  unsigned int count_of_facets_;  ///< Количество поверхностей в модели
  double**
      matrix_;  ///< Матрица координат вершин, нулевой элемент не используем
                /*!
                  \brief facets_ - Матрица вершин, из которых состоят поверхности
              
                  0й индекс - количетво вершин в поверхности,
                  1й индекс - номер поверхности,
                  2й индекс - перечень вершин
                */
  std::set<std::pair<unsigned int, unsigned int>> edges_;
  double
      minMax_[6];  ///< Матрица крайних значений: мин Х, макс Х, мин У, макс У
} DataT;

typedef struct {
  double scale_;  //  Начальный scale
  double currX_;  //  Начальные позиции ползунков перемещения
  double currY_;
  double currZ_;
  double curr_angle_X_;  //  Начальные позиции ползунков вращения
  double curr_angle_Y_;
  double curr_angle_Z_;
  double painting_time_;
  int highlight_vertexes_;
  int round_vertexes_;
  int central_projection_;
  float vertexes_color_red_;
  float vertexes_color_green_;
  float vertexes_color_blue_;
  int vertexes_size_;
  int dotted_facets_;
  float facets_color_red_;
  float facets_color_green_;
  float facets_color_blue_;
  int facets_size_;
  float background_color_red_;
  float background_color_green_;
  float background_color_blue_;
  double frustrum_near_val_;  //  Параметр glFrustrum для центральной проекции
  int central_painting_;  //  Флаг, показывает выбирали ли ранее центральную
                          //  проекцию
  float ratio_;
} SettingsT;

namespace s21 {

class Model {
 public:
  Model() {
    *port_data_ = PortDataInit();
    SettingsDataInit();
    settings_ = new QSettings(iniFilePath, QSettings::IniFormat);
    QFile file(iniFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
      std::cerr << "Unable to write to file: "
                << file.errorString().toStdString() << std::endl;
    } else {
      file.close();
    }
    LoadSettings();
  }
  ~Model() {
    if (port_data_->matrix_ != nullptr) {
      delete[] port_data_->matrix_;
    }
    delete port_data_;
    SaveSettings();
  }
  DataT* GetData() { return port_data_; }
  SettingsT* GetSettings() { return settings_data_; }
  void MultiplyMatrixPub(double value);
  void RotationModelPub(double angle, int axis);
  void MoveModelPub(double number, int axis);
  int ParsingPub(char* str);
  int CountsItoA(unsigned int data, char* result);
  int ScaleDataPub(double value);
  int CenterDataPub();
  int OpenFile(char* str);
  void LoadSettings();
  int ScalingModelPub(double K, int axis);

 private:
  DataT PortDataInit() {
    port_data_ = new DataT();
    port_data_->count_of_vertexes_ = 0;
    port_data_->count_of_facets_ = 0;
    port_data_->matrix_ = nullptr;
    return *port_data_;
  }
  void SettingsDataInit() {
    settings_data_ = new SettingsT();
    settings_data_->scale_ = 0.5;  //  Начальный scale
    settings_data_->currX_ = 100;  //  Начальные позиции ползунков перемещения
    settings_data_->currY_ = 100;
    settings_data_->currZ_ = 100;
    settings_data_->curr_angle_X_ =
        180;  //  Начальные позиции ползунков вращения
    settings_data_->curr_angle_Y_ = 180;
    settings_data_->curr_angle_Z_ = 180;
    settings_data_->highlight_vertexes_ = 1;
    settings_data_->round_vertexes_ = 0;
    settings_data_->central_projection_ = 0;
    settings_data_->vertexes_size_ = 2;
    settings_data_->dotted_facets_ = 0;
    settings_data_->facets_size_ = 1;
    settings_data_->frustrum_near_val_ = 0.87;
    settings_data_->central_painting_ = 0;
    settings_data_->ratio_ = 1;
  }
  int Parsing(char* str, DataT* data);
  int CountStruct(char* input, DataT* data);
  int CreateMatrix(DataT* data);
  unsigned int CountDouble(char* input);
  void ParsingDouble(char* input, long int* i, double* number);
  int ParsVertFacet(char* input, long int* len_input, DataT* data);
  void ParsingVertexes(char* input, long int* i, unsigned int vert,
                       DataT* data);
  int ParsingFacets(char* input, long int* i, DataT* data);
  void NextLine(char* input, long int* i);
  void FindMinMax(unsigned int vert, DataT* data);
  void FreeData(DataT* data);
  // athens
  void MoveModel(DataT* data, double number, int axis);
  int ScalingModel(DataT* data, double K, int axis);
  void RotationModel(DataT* data, double angle, int axis);
  int ScaleData(DataT* data, double value);
  void MultiplyMatrix(DataT* data, double value);
  int CenterData(DataT* data);
  void SaveSettings();
  std::pair<unsigned int, unsigned int> NormalizePair(unsigned int a,
                                                      unsigned int b);
  QString iniFilePath = "settings.ini";
  DataT* port_data_;
  SettingsT* settings_data_;
  QSettings* settings_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODEL_MODEL_H
