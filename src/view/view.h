#ifndef CPP4_3DVIEWER_V_2_0_SRC_VIEW_VIEW_H
#define CPP4_3DVIEWER_V_2_0_SRC_VIEW_VIEW_H

#include <stdlib.h>

#include <QFileDialog>
#include <QFontMetrics>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSettings>
#include <QSlider>
#include <QString>
#include <cmath>
#include <cstdlib>

#include "../controller/controller.h"
#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include "model/model.h"
#include "view/preferences_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT
 public:
  View(Controller *c);
  ~View();
 signals:
  void Window_Closed_signal(QCloseEvent *event);
 public slots:
  void SlotPreferencesSet(PreferencesWindow::PreferencesStruct Preferences);
  void GifRecording();
 private slots:
  void MoveByAxis();
  void ValuesByAxisSet(QSlider *slider, double *position, double *current_val,
                       QLineEdit *text_LineEdit, int val_corrector,
                       int central_val);
  void MoveByAxisLineEdit();
  void RotateByAxisLineEdit();
  int ValuesByAxisLineEditSet(QLineEdit *line, double *position,
                              double *current_val, int val_corrector,
                              int central_val);
  void RotateByAxis();
  void on_actionOpen_file_triggered();
  void on_horizontalSlider_Scale_sliderMoved(int position);
  void on_lineEdit_Scale_editingFinished();
  void on_actionPreferences_triggered();
  void on_save_button_clicked();
  void MultiplyMatrixSlot(DataT *port_data, double value);

 private:
  void LoadPreferences();
  int QStringToDouble(QString text, double *result);
  int LabelsCountsSet(unsigned int count, QLabel *label);
  void QStringToChar(QString line_in, char *input_string);
  Ui::View *ui_;
  PreferencesWindow preferences_;
  QGifImage *gif_frame_;
  QTimer *gif_timer_;
  int count_ = 0;
  Controller *controller_;
};

}  //  namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_VIEW_VIEW_H
