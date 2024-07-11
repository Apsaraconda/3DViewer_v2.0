#ifndef CPP4_3DVIEWER_V_2_0_SRC_VIEW_GLVIEW_H
#define CPP4_3DVIEWER_V_2_0_SRC_VIEW_GLVIEW_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>

#include "model/model.h"

namespace s21 {

class glView : public QOpenGLWidget {
  Q_OBJECT

 public:
  glView(QWidget *parent = nullptr);
  DataT *port_data_;
  SettingsT *settings_;
  double painting_time_;
  int highlight_vertexes_ = 1;
  int round_vertexes_ = 0;
  int central_projection_ = 0;
  float vertexes_color_red_;
  float vertexes_color_green_;
  float vertexes_color_blue_;
  int vertexes_size_ = 2;
  int dotted_facets_ = 0;
  float facets_color_red_;
  float facets_color_green_;
  float facets_color_blue_;
  int facets_size_ = 1;
  float background_color_red_;
  float background_color_green_;
  float background_color_blue_;
  double frustrum_near_val_ =
      0.87;  //  Параметр glFrustrum для центральной проекции
  int central_painting_ =
      0;  //  Флаг, показывает выбирали ли ранее центральную проекцию
 signals:
  void MultiplyMatrixSignal(DataT *port_data, double value);

 protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void DrawLines(DataT *port_data, GLfloat width, double red, double green,
                 double blue);
  void DrawPoints(DataT *port_data, GLfloat size, double red, double green,
                  double blue, int round_Vertexes);
  void ChangeProjection();
};

}  //  namespace s21

#endif  // CPP4_3DVIEWER_V_2_0_SRC_VIEW_GLVIEW_H
