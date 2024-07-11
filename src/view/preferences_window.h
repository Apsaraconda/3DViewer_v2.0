#ifndef CPP4_3DVIEWER_V_2_0_SRC_VIEW_PREFERENCES_WINDOW_H
#define CPP4_3DVIEWER_V_2_0_SRC_VIEW_PREFERENCES_WINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QDialog>

namespace Ui {
class PreferencesWindow;
}

namespace s21 {

class PreferencesWindow : public QDialog {
  Q_OBJECT

 public:
  Ui::PreferencesWindow *ui_;
  explicit PreferencesWindow(QWidget *parent = nullptr);
  ~PreferencesWindow();

  struct PreferencesStruct {
    int highlight_vertexes_;
    int round_vertexes_;
    int central_projection_;
    int vertexes_size_;
    QColor vertexes_color_;
    int dotted_facets_;
    int facets_size_;
    QColor facets_color_;
    QColor background_color_;
  };
  PreferencesStruct preferences_;

 public:
  void SetHighlightVertexesCheckBox(int value);
  void ChangeComboBoxVertexesType(int index);
  void ChangeProjectionTypeRadioButtons(int value);
  void ChangeVertexesColor(float red, float green, float blue);
  void ChangeVertexesSize(int value);
  void ChangeFacetsTypeCheckBox(int index);
  void ChangeFacetsColor(float red, float green, float blue);
  void ChangeFacetsSize(int value);
  void ChangeBackgroundColor(float red, float green, float blue);
  void MainWindowClosed();
 signals:
  void SignalPref(PreferencesStruct Preferences);
 private slots:
  void SavePreferences();
  void ApplyPreferences();
  void on_checkBox_Highlight_Vertexes_stateChanged(int arg1);
  void on_pushButton_Vertexes_Color_clicked();
  void on_pushButton_Facets_Color_clicked();
  void on_pushButton_Background_Color_clicked();
};

}  //  namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_VIEW_PREFERENCES_WINDOW_H
