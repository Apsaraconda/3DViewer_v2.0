#include "view/preferences_window.h"

#include "view/ui_preferences_window.h"

namespace s21 {

PreferencesWindow::PreferencesWindow(QWidget *parent)
    : QDialog(parent), ui_(new Ui::PreferencesWindow) {
  ui_->setupUi(this);
  connect(ui_->pushButton_OK, SIGNAL(clicked()), this, SLOT(SavePreferences()));
  connect(ui_->pushButton_Cancel, SIGNAL(clicked()), this,
          SLOT(SavePreferences()));
  connect(ui_->pushButton_Apply, SIGNAL(clicked()), this,
          SLOT(SavePreferences()));
}

PreferencesWindow::~PreferencesWindow() { delete ui_; }

//  Логика работы кнопок
void PreferencesWindow::SavePreferences() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString str_ok = "OK";
  QString str_cancel = "Cancel";
  QString str_apply = "Apply";
  if (!QString::compare(button_text, str_ok, Qt::CaseInsensitive)) {
    ApplyPreferences();
    hide();
  } else if (!QString::compare(button_text, str_cancel, Qt::CaseInsensitive)) {
    hide();
  } else if (!QString::compare(button_text, str_apply, Qt::CaseInsensitive)) {
    ApplyPreferences();
  }
}

// Функция отправки сигнала с настройками
void PreferencesWindow::ApplyPreferences() {
  preferences_.highlight_vertexes_ = 0;
  preferences_.round_vertexes_ = 0;
  preferences_.central_projection_ = 0;
  preferences_.vertexes_size_ = 2;
  preferences_.dotted_facets_ = 0;
  preferences_.facets_size_ = 1;
  if (ui_->checkBox_Highlight_Vertexes->isChecked()) {
    preferences_.highlight_vertexes_ = 1;
    if (ui_->comboBox_Vertexes_Type->currentIndex() == 0) {
      preferences_.round_vertexes_ = 1;
    }
    preferences_.vertexes_size_ = ui_->spinBox_Vertexes_Size->value();
  }
  if (ui_->radioButton_Central->isChecked())
    preferences_.central_projection_ = 1;
  preferences_.dotted_facets_ = ui_->comboBox_Facets_Type->currentIndex();
  preferences_.facets_size_ = ui_->spinBox_Facets_Size->value();
  emit SignalPref(preferences_);
}

//  Управление включением Highlight Vertexes
void PreferencesWindow::SetHighlightVertexesCheckBox(int value) {
  ui_->checkBox_Highlight_Vertexes->setChecked(value);
  ui_->comboBox_Vertexes_Type->setEnabled(value);
  ui_->pushButton_Vertexes_Color->setEnabled(value);
  ui_->spinBox_Vertexes_Size->setEnabled(value);
}

void PreferencesWindow::ChangeComboBoxVertexesType(int index) {
  ui_->comboBox_Vertexes_Type->setCurrentIndex(index);
}

void PreferencesWindow::ChangeProjectionTypeRadioButtons(int value) {
  if (value) {
    ui_->radioButton_Parallel->setChecked(0);
  } else {
    ui_->radioButton_Parallel->setChecked(1);
  }
  ui_->radioButton_Central->setChecked(value);
}

void PreferencesWindow::ChangeVertexesColor(float red, float green,
                                            float blue) {
  preferences_.vertexes_color_.setRgbF(red, green, blue);
}

void PreferencesWindow::ChangeVertexesSize(int value) {
  ui_->spinBox_Vertexes_Size->setValue(value);
}

void PreferencesWindow::ChangeFacetsTypeCheckBox(int index) {
  ui_->comboBox_Facets_Type->setCurrentIndex(index);
}

void PreferencesWindow::ChangeFacetsColor(float red, float green, float blue) {
  preferences_.facets_color_.setRgbF(red, green, blue);
}

void PreferencesWindow::ChangeFacetsSize(int value) {
  ui_->spinBox_Facets_Size->setValue(value);
}

void PreferencesWindow::ChangeBackgroundColor(float red, float green,
                                              float blue) {
  preferences_.background_color_.setRgbF(red, green, blue);
}

//  Закрывает окно, если поступает сигнал о том, что закрывается главное окно
void PreferencesWindow::MainWindowClosed() { close(); }

//  Делает активными-неактивными все настройки вершин,
//  если выбрана-не выбрана галочка Highlight Vertexes
void PreferencesWindow::on_checkBox_Highlight_Vertexes_stateChanged(int arg1) {
  ui_->comboBox_Vertexes_Type->setEnabled(arg1);
  ui_->pushButton_Vertexes_Color->setEnabled(arg1);
  ui_->spinBox_Vertexes_Size->setEnabled(arg1);
}

void PreferencesWindow::on_pushButton_Vertexes_Color_clicked() {
  preferences_.vertexes_color_ =
      QColorDialog::getColor(Qt::green, this, "Choose Vertexes Color");
}

void PreferencesWindow::on_pushButton_Facets_Color_clicked() {
  preferences_.facets_color_ =
      QColorDialog::getColor(Qt::red, this, "Choose Facets Color");
}

void PreferencesWindow::on_pushButton_Background_Color_clicked() {
  preferences_.background_color_ =
      QColorDialog::getColor(Qt::black, this, "Choose Background Color");
}

}  //  namespace s21
