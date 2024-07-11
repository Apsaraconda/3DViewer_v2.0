#include "model.h"

namespace s21 {

//  Сохранение настроек
void Model::SaveSettings() {
  settings_->setValue("highlight_vertexes_",
                      settings_data_->highlight_vertexes_);
  settings_->setValue("round_vertexes_", settings_data_->round_vertexes_);
  settings_->setValue("central_projection_",
                      settings_data_->central_projection_);
  settings_->setValue("vertexes_color_red_",
                      settings_data_->vertexes_color_red_);
  settings_->setValue("vertexes_color_green_",
                      settings_data_->vertexes_color_green_);
  settings_->setValue("vertexes_color_blue_",
                      settings_data_->vertexes_color_blue_);
  settings_->setValue("vertexes_size_", settings_data_->vertexes_size_);
  settings_->setValue("dotted_facets_", settings_data_->dotted_facets_);
  settings_->setValue("facets_color_red_", settings_data_->facets_color_red_);
  settings_->setValue("facets_color_green_",
                      settings_data_->facets_color_green_);
  settings_->setValue("facets_color_blue_", settings_data_->facets_color_blue_);
  settings_->setValue("facets_size_", settings_data_->facets_size_);
  settings_->setValue("background_color_red_",
                      settings_data_->background_color_red_);
  settings_->setValue("background_color_green_",
                      settings_data_->background_color_green_);
  settings_->setValue("background_color_blue_",
                      settings_data_->background_color_blue_);
  settings_->sync();
  if (settings_->status() != QSettings::NoError) {
    std::cerr << "Error writing settings to file: " << settings_->status()
              << std::endl;
  }
}

//  Загрузка и применение настроек
void Model::LoadSettings() {
  settings_data_->highlight_vertexes_ =
      settings_->value("highlight_vertexes_", 1).toInt();
  if (settings_->value("round_vertexes_", 1).toInt() == 1) {
    settings_data_->round_vertexes_ = 1;
  } else {
    settings_data_->round_vertexes_ = 0;
  }
  settings_data_->central_projection_ =
      settings_->value("central_projection_", 0).toInt();
  settings_data_->vertexes_color_red_ =
      settings_->value("vertexes_color_red_", 0).toFloat();
  settings_data_->vertexes_color_green_ =
      settings_->value("vertexes_color_green_", 1).toFloat();
  settings_data_->vertexes_color_blue_ =
      settings_->value("vertexes_color_blue_", 0).toFloat();
  settings_data_->vertexes_size_ =
      settings_->value("vertexes_size_", 2).toInt();
  settings_data_->dotted_facets_ =
      settings_->value("dotted_facets_", 0).toInt();
  settings_data_->facets_color_red_ =
      settings_->value("facets_color_red_", 1).toFloat();
  settings_data_->facets_color_green_ =
      settings_->value("facets_color_green_", 0).toFloat();
  settings_data_->facets_color_blue_ =
      settings_->value("facets_color_blue_", 0).toFloat();
  settings_data_->facets_size_ = settings_->value("facets_size_", 1).toInt();
  settings_data_->background_color_red_ =
      settings_->value("background_color_red_", 0).toFloat();
  settings_data_->background_color_green_ =
      settings_->value("background_color_green_", 0).toFloat();
  settings_data_->background_color_blue_ =
      settings_->value("background_color_blue_", 0).toFloat();
}

}  //  namespace s21
