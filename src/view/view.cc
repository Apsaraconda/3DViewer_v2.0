#include "view/view.h"

#include "view/ui_view.h"

namespace s21 {

View::View(Controller *c)
    : QMainWindow(),
      ui_(new Ui::View),
      preferences_(new PreferencesWindow(nullptr)),
      controller_(c) {
  ui_->setupUi(this);
  ui_->openGLWidget->port_data_ = controller_->GetData();
  ui_->openGLWidget->settings_ = controller_->GetSettings();
  ui_->label_Error->setStyleSheet("color: rgb(150, 0, 0)");
  connect(ui_->horizontalSlider_move_X, SIGNAL(valueChanged(int)), this,
          SLOT(MoveByAxis()));
  connect(ui_->horizontalSlider_move_Y, SIGNAL(valueChanged(int)), this,
          SLOT(MoveByAxis()));
  connect(ui_->horizontalSlider_move_Z, SIGNAL(valueChanged(int)), this,
          SLOT(MoveByAxis()));
  connect(ui_->horizontalSlider_rotate_X, SIGNAL(valueChanged(int)), this,
          SLOT(RotateByAxis()));
  connect(ui_->horizontalSlider_rotate_Y, SIGNAL(valueChanged(int)), this,
          SLOT(RotateByAxis()));
  connect(ui_->horizontalSlider_rotate_Z, SIGNAL(valueChanged(int)), this,
          SLOT(RotateByAxis()));
  connect(ui_->lineEdit_move_X, SIGNAL(editingFinished()), this,
          SLOT(MoveByAxisLineEdit()));
  connect(ui_->lineEdit_move_Y, SIGNAL(editingFinished()), this,
          SLOT(MoveByAxisLineEdit()));
  connect(ui_->lineEdit_move_Z, SIGNAL(editingFinished()), this,
          SLOT(MoveByAxisLineEdit()));
  connect(ui_->lineEdit_rotate_X, SIGNAL(editingFinished()), this,
          SLOT(RotateByAxis()));
  connect(ui_->lineEdit_rotate_Y, SIGNAL(editingFinished()), this,
          SLOT(RotateByAxis()));
  connect(ui_->lineEdit_rotate_Z, SIGNAL(editingFinished()), this,
          SLOT(RotateByAxisLineEdit()));
  connect(&preferences_, &PreferencesWindow::SignalPref, this,
          &View::SlotPreferencesSet);
  connect(this, &View::Window_Closed_signal, &preferences_,
          &PreferencesWindow::MainWindowClosed);
  connect(ui_->openGLWidget, &glView::MultiplyMatrixSignal, this,
          &View::MultiplyMatrixSlot);
  controller_->LoadSettings(ui_->openGLWidget->settings_);
  LoadPreferences();
}

View::~View() { delete ui_; }

void View::on_actionOpen_file_triggered() {
  QString file_path;
  file_path = QFileDialog::getOpenFileName(
      this, "Choose file", "", ".obj files (*.obj);; All files (*.*)");
  if (file_path != nullptr) {
    ui_->label_File_Path->setText(file_path);
    ui_->label_File_Path->setMaximumWidth(180);
    QFontMetrics fm(ui_->label_File_Path->font());
    int pixelsWide = fm.horizontalAdvance(ui_->label_File_Path->text());
    if (pixelsWide > 180) {
      ui_->label_File_Dots->setText("...");
    }
    int len = file_path.length();
    int resize_len = len * 6;
    if (resize_len > 180 && resize_len <= 680) {
      ui_->label_File_Path->setMaximumWidth(resize_len);
    } else if (resize_len > 680) {
      ui_->label_File_Path->setMaximumWidth(680);
    }
    int error = 0;
    char *file_path_str = (char *)malloc(sizeof(char) * (len + 1));
    if (file_path_str != NULL) {
      QStringToChar(file_path, file_path_str);
      ui_->label_Error->setText("Opening file...");
      error =
          controller_->OpenFile(file_path_str, ui_->openGLWidget->port_data_,
                                ui_->openGLWidget->settings_);
      LoadPreferences();
      free(file_path_str);
      if (!error) {
        error =
            LabelsCountsSet(ui_->openGLWidget->port_data_->count_of_vertexes_,
                            ui_->label_Vertexes_Count);
        if (!error)
          error =
              LabelsCountsSet(ui_->openGLWidget->port_data_->count_of_facets_,
                              ui_->label_Facets_Count);
        ui_->openGLWidget->repaint();
        ui_->label_Painting_Time_Counter->setText(
            QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
        ui_->label_Error->setText("");
      }
    } else {
      error = 2;
    }
    if (error == 2) {
      ui_->label_Error->setText("File path: Memory allocation error");
    } else if (error == 3) {
      ui_->label_Error->setText("Labels text: Memory allocation error");
    } else if (error) {
      ui_->label_Error->setText("Open file error");
    }
  }
}

int View::LabelsCountsSet(unsigned int count, QLabel *label) {
  int error = 0;
  char *count_str = (char *)malloc(count);
  if (count_str != NULL) {
    error = controller_->CountsItoA(count, count_str);
    if (!error) label->setText(count_str);
    free(count_str);
  } else {
    error = 3;
  }
  return error;
}

void View::QStringToChar(QString line_in, char *input_string) {
  int line_length = line_in.length();
  if (line_length > 0) {
    QByteArray button_in = line_in.toLocal8Bit();
    char *input_copy = button_in.data();
    strncpy(input_string, input_copy, line_length);
    input_string[line_length] = '\0';
  } else {
    *input_string = '\0';
  }
}

void View::on_horizontalSlider_Scale_sliderMoved(int position) {
  double curr_scale = ui_->openGLWidget->settings_->scale_;
  ui_->lineEdit_Scale->setText(
      QString::number(round(((double)position / 99) * 100) / 100));
  ui_->openGLWidget->settings_->scale_ = (double)position / 99;
  controller_->MultiplyMatrix(
      ui_->openGLWidget->port_data_,
      ui_->openGLWidget->settings_->scale_ / curr_scale);
  ui_->openGLWidget->repaint();
  ui_->label_Painting_Time_Counter->setText(
      QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
  ui_->label_Error->setText("");
}

void View::on_lineEdit_Scale_editingFinished() {
  double curr_scale = ui_->openGLWidget->settings_->scale_;
  double line_val;
  int error = 0;
  QString str = ui_->lineEdit_Scale->text();
  error = QStringToDouble(str, &line_val);
  if (!error) {
    ui_->openGLWidget->settings_->scale_ = line_val;
    controller_->MultiplyMatrix(
        ui_->openGLWidget->port_data_,
        ui_->openGLWidget->settings_->scale_ / curr_scale);
    ui_->openGLWidget->repaint();
    ui_->label_Painting_Time_Counter->setText(
        QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
    ui_->label_Error->setText("");
  } else {
    ui_->label_Error->setText("Error: Incorrect number format");
  }
}

void View::MoveByAxis() {
  QSlider *slider = (QSlider *)sender();
  double position = 0;
  QString name = slider->objectName();
  QString str1 = "horizontalSlider_move_X";
  QString str2 = "horizontalSlider_move_Y";
  QString str3 = "horizontalSlider_move_Z";
  int axis = 0;
  if (!QString::compare(name, str1, Qt::CaseInsensitive)) {
    axis = 0;
    ValuesByAxisSet(slider, &position, &ui_->openGLWidget->settings_->currX_,
                    ui_->lineEdit_move_X, 100, 100);
  } else if (!QString::compare(name, str2, Qt::CaseInsensitive)) {
    axis = 1;
    ValuesByAxisSet(slider, &position, &ui_->openGLWidget->settings_->currY_,
                    ui_->lineEdit_move_Y, 100, 100);
  } else if (!QString::compare(name, str3, Qt::CaseInsensitive)) {
    axis = 2;
    ValuesByAxisSet(slider, &position, &ui_->openGLWidget->settings_->currZ_,
                    ui_->lineEdit_move_Z, 100, 100);
  }
  controller_->MoveModel(ui_->openGLWidget->port_data_, position, axis);
  ui_->openGLWidget->repaint();
  ui_->label_Painting_Time_Counter->setText(
      QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
  ui_->label_Error->setText("");
}

void View::ValuesByAxisSet(QSlider *slider, double *position,
                           double *current_val, QLineEdit *text_LineEdit,
                           int val_corrector, int central_val) {
  *position = ((double)(slider->value()) - *current_val) / val_corrector;
  text_LineEdit->setText(QString::number(
      round(((double)(slider->value() - central_val) / val_corrector) * 100) /
      100));
  *current_val = slider->value();
}

void View::RotateByAxis() {
  QSlider *slider = (QSlider *)sender();
  double angle = 0;
  QString name = slider->objectName();
  QString str1 = "horizontalSlider_rotate_X";
  QString str2 = "horizontalSlider_rotate_Y";
  QString str3 = "horizontalSlider_rotate_Z";
  int axis = 0;
  if (!QString::compare(name, str1, Qt::CaseInsensitive)) {
    axis = 0;
    ValuesByAxisSet(slider, &angle,
                    &ui_->openGLWidget->settings_->curr_angle_X_,
                    ui_->lineEdit_rotate_X, 1, 180);
  } else if (!QString::compare(name, str2, Qt::CaseInsensitive)) {
    axis = 1;
    ValuesByAxisSet(slider, &angle,
                    &ui_->openGLWidget->settings_->curr_angle_Y_,
                    ui_->lineEdit_rotate_Y, 1, 180);
  } else if (!QString::compare(name, str3, Qt::CaseInsensitive)) {
    axis = 2;
    ValuesByAxisSet(slider, &angle,
                    &ui_->openGLWidget->settings_->curr_angle_Z_,
                    ui_->lineEdit_rotate_Z, 1, 180);
  }
  controller_->RotationModel(ui_->openGLWidget->port_data_, angle, axis);
  ui_->openGLWidget->repaint();
  ui_->label_Painting_Time_Counter->setText(
      QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
  ui_->label_Error->setText("");
}

void View::MoveByAxisLineEdit() {
  QLineEdit *line = (QLineEdit *)sender();
  int error = 0;
  double position = 0;
  QString name = line->objectName();
  QString str1 = "lineEdit_move_X";
  QString str2 = "lineEdit_move_Y";
  QString str3 = "lineEdit_move_Z";
  int axis = 0;
  if (!QString::compare(name, str1, Qt::CaseInsensitive)) {
    axis = 0;
    error = ValuesByAxisLineEditSet(
        line, &position, &ui_->openGLWidget->settings_->currX_, 1, 100);
  } else if (!QString::compare(name, str2, Qt::CaseInsensitive)) {
    axis = 1;
    error = ValuesByAxisLineEditSet(
        line, &position, &ui_->openGLWidget->settings_->currY_, 1, 100);
  } else if (!QString::compare(name, str3, Qt::CaseInsensitive)) {
    axis = 2;
    error = ValuesByAxisLineEditSet(
        line, &position, &ui_->openGLWidget->settings_->currZ_, 1, 100);
  }
  if (!error) {
    controller_->MoveModel(ui_->openGLWidget->port_data_, position, axis);
    ui_->openGLWidget->repaint();
    ui_->label_Painting_Time_Counter->setText(
        QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
    ui_->label_Error->setText("");
  } else {
    ui_->label_Error->setText("Error: Incorrect number format");
  }
}

void View::RotateByAxisLineEdit() {
  QLineEdit *line = (QLineEdit *)sender();
  int error = 0;
  double angle = 0;
  QString name = line->objectName();
  QString str1 = "lineEdit_rotate_X";
  QString str2 = "lineEdit_rotate_Y";
  QString str3 = "lineEdit_rotate_Z";
  int axis = 0;
  if (!QString::compare(name, str1, Qt::CaseInsensitive)) {
    axis = 0;
    error = ValuesByAxisLineEditSet(
        line, &angle, &ui_->openGLWidget->settings_->curr_angle_X_, 180, 180);
  } else if (!QString::compare(name, str2, Qt::CaseInsensitive)) {
    axis = 1;
    error = ValuesByAxisLineEditSet(
        line, &angle, &ui_->openGLWidget->settings_->curr_angle_Y_, 180, 180);
  } else if (!QString::compare(name, str3, Qt::CaseInsensitive)) {
    axis = 2;
    error = ValuesByAxisLineEditSet(
        line, &angle, &ui_->openGLWidget->settings_->curr_angle_Z_, 180, 180);
  }
  if (!error) {
    controller_->RotationModel(ui_->openGLWidget->port_data_, angle, axis);
    ui_->openGLWidget->repaint();
    ui_->label_Painting_Time_Counter->setText(
        QString::number(ui_->openGLWidget->painting_time_, 'g', 2));
    ui_->label_Error->setText("");
  } else {
    ui_->label_Error->setText("Error: Incorrect number format");
  }
}

int View::QStringToDouble(QString text, double *result) {
  int error = 0;
  bool result_ok = 0;
  QString temp = text;
  temp.replace(",", ".");
  *result = temp.toDouble(&result_ok);
  if (!result_ok) error = 1;
  return error;
}

int View::ValuesByAxisLineEditSet(QLineEdit *line, double *position,
                                  double *current_val, int val_corrector,
                                  int central_val) {
  double line_val;
  int error = 0;
  QString str = line->text();
  error = QStringToDouble(str, &line_val);
  if (!error) {
    *position =
        line_val - (*current_val - central_val) * val_corrector / central_val;
    *current_val = central_val + line_val * central_val / val_corrector;
  }
  return error;
}

void View::on_save_button_clicked() {
  if (ui_->comboBox->currentText() == "*.jpeg") {
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "file.jpeg",
                                                tr("Image (*.bmp , *.jpeg)"));
    ui_->openGLWidget->grab().save(file);
  } else if (ui_->comboBox->currentText() == "*.bmp") {
    QString file = QFileDialog::getSaveFileName(this, "Save as...", "file.bmp",
                                                tr("Image (*.bmp , *.jpeg)"));
    ui_->openGLWidget->grab().save(file);
  } else if (ui_->comboBox->currentText() == "*.gif") {
    ui_->save_button->setEnabled(false);
    ui_->save_button->setStyleSheet("color: black");
    ui_->save_button->setText("recording");
    gif_frame_ = new QGifImage;
    gif_timer_ = new QTimer(this);
    gif_frame_->setDefaultDelay(100);
    connect(gif_timer_, SIGNAL(timeout()), this, SLOT(GifRecording()));
    gif_timer_->start(100);
  }
}
void View::GifRecording() {
  if (count_ != 50) {
    ui_->save_button->setText("recording " + QString::number(count_ * 2) + "%");
    count_++;
    QImage frame = ui_->openGLWidget->grabFramebuffer();
    int required_wigth = 640;
    int required_height = 480;
    gif_frame_->addFrame(
        frame.scaled(required_wigth, required_height,
                     Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation),
        0);
  } else {
    gif_timer_->stop();
    ui_->save_button->setEnabled(true);
    ui_->save_button->setText("Save");
    count_ = 0;
    QString file = QFileDialog::getSaveFileName(this, "Выбeрите папку",
                                                "file.gif", tr("Gif (*.gif)"));
    gif_frame_->save(file);
  }
}

void View::MultiplyMatrixSlot(DataT *port_data, double value) {
  controller_->MultiplyMatrix(port_data, value);
}

}  //  namespace s21
