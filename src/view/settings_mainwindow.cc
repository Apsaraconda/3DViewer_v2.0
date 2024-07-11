#include "view/ui_view.h"
#include "view/view.h"

namespace s21 {

//  Загрузка и применение настроек
void View::LoadPreferences() {
  preferences_.SetHighlightVertexesCheckBox(
      ui_->openGLWidget->settings_->highlight_vertexes_);
  if (ui_->openGLWidget->settings_->round_vertexes_ == 1) {
    preferences_.ChangeComboBoxVertexesType(0);
  } else {
    preferences_.ChangeComboBoxVertexesType(1);
  }
  preferences_.ChangeProjectionTypeRadioButtons(
      ui_->openGLWidget->settings_->central_projection_);
  preferences_.ChangeVertexesColor(
      ui_->openGLWidget->settings_->vertexes_color_red_,
      ui_->openGLWidget->settings_->vertexes_color_green_,
      ui_->openGLWidget->settings_->vertexes_color_blue_);
  preferences_.ChangeVertexesSize(ui_->openGLWidget->settings_->vertexes_size_);
  preferences_.ChangeFacetsTypeCheckBox(
      ui_->openGLWidget->settings_->dotted_facets_);
  preferences_.ChangeFacetsColor(
      ui_->openGLWidget->settings_->facets_color_red_,
      ui_->openGLWidget->settings_->facets_color_green_,
      ui_->openGLWidget->settings_->facets_color_blue_);
  preferences_.ChangeFacetsSize(ui_->openGLWidget->settings_->facets_size_);
  preferences_.ChangeBackgroundColor(
      ui_->openGLWidget->settings_->background_color_red_,
      ui_->openGLWidget->settings_->background_color_green_,
      ui_->openGLWidget->settings_->background_color_blue_);
}

//  Открывается окно изменения настроек
void View::on_actionPreferences_triggered() { preferences_.show(); }

//  Функция применения настроек по сигналу от preferences
void View::SlotPreferencesSet(
    PreferencesWindow::PreferencesStruct Preferences) {
  if (Preferences.highlight_vertexes_ == 1) {
    ui_->openGLWidget->settings_->highlight_vertexes_ = 1;
    if (Preferences.round_vertexes_) {
      ui_->openGLWidget->settings_->round_vertexes_ = 1;
    } else {
      ui_->openGLWidget->settings_->round_vertexes_ = 0;
    }
  } else {
    ui_->openGLWidget->settings_->highlight_vertexes_ = 0;
  }
  if (Preferences.central_projection_) {
    ui_->openGLWidget->settings_->central_projection_ = 1;
  } else {
    ui_->openGLWidget->settings_->central_projection_ = 0;
  }
  Preferences.vertexes_color_.getRgbF(
      &ui_->openGLWidget->settings_->vertexes_color_red_,
      &ui_->openGLWidget->settings_->vertexes_color_green_,
      &ui_->openGLWidget->settings_->vertexes_color_blue_);
  ui_->openGLWidget->settings_->vertexes_size_ = Preferences.vertexes_size_;
  ui_->openGLWidget->settings_->dotted_facets_ = Preferences.dotted_facets_;
  ui_->openGLWidget->settings_->facets_size_ = Preferences.facets_size_;
  Preferences.facets_color_.getRgbF(
      &ui_->openGLWidget->settings_->facets_color_red_,
      &ui_->openGLWidget->settings_->facets_color_green_,
      &ui_->openGLWidget->settings_->facets_color_blue_);
  Preferences.background_color_.getRgbF(
      &ui_->openGLWidget->settings_->background_color_red_,
      &ui_->openGLWidget->settings_->background_color_green_,
      &ui_->openGLWidget->settings_->background_color_blue_);
  ui_->openGLWidget->settings_ = controller_->GetSettings();
  ui_->openGLWidget->repaint();
  ui_->label_Painting_Time_Counter->setText(
      QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
}

}  //  namespace s21
