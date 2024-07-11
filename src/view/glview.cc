#include "view/glview.h"

namespace s21 {

glView::glView(QWidget *parent) : QOpenGLWidget{parent}, port_data_(nullptr) {}

void glView::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION);  // устанавливает текущей проекционную матрицу
  glLoadIdentity();  // присваивает проекционной матрице единичную матрицу
  settings_->ratio_ = (float)h / (float)w;
  ChangeProjection();
  // поле просмотра
  glViewport(0, 0, (GLint)w, (GLint)h);
}

void glView::paintGL() {
  glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
  glMatrixMode(GL_PROJECTION);  // устанавливаем положение и ориентацию матрице
                                // моделирования
  glClearColor(settings_->background_color_red_,
               settings_->background_color_green_,
               settings_->background_color_blue_,
               0);  //  отвечает за состояние цвета фона
  // очистка буфера изображения и глубины
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();  // загружаем единичную матрицу моделирования
  if (port_data_->matrix_) {
    if (settings_->central_projection_) {
      ChangeProjection();
      glTranslated(0, 0, -settings_->frustrum_near_val_ * 5.4);
      if (!settings_->central_painting_) {
        emit MultiplyMatrixSignal(
            port_data_,
            5);  //  увеличиваем масштаб на 5 для центральной проекции
        settings_->central_painting_ = 1;
      }
    } else {
      ChangeProjection();
      if (settings_->central_painting_ == 1) {
        emit MultiplyMatrixSignal(
            port_data_,
            0.2);  //  уменьшаем масштаб в 5 раз для параллельной проекции
      }
      settings_->central_painting_ = 0;
    }
    auto start = std::chrono::steady_clock::now();
    DrawLines(port_data_, settings_->facets_size_, settings_->facets_color_red_,
              settings_->facets_color_green_, settings_->facets_color_blue_);
    if (settings_->highlight_vertexes_) {
      DrawPoints(port_data_, settings_->vertexes_size_,
                 settings_->vertexes_color_red_,
                 settings_->vertexes_color_green_,
                 settings_->vertexes_color_blue_, settings_->round_vertexes_);
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration delta = (stop - start);  //высчитываем разницу
    painting_time_ = (double)(delta.count()) / 1000000000;
  }
}

void glView::DrawLines(DataT *port_data, GLfloat width, double red,
                       double green, double blue) {
  glLineWidth(width);  // устанавливаем ширину линии
  glColor3d(red, green, blue);  // устанавливаем цвет линии
  if (settings_->dotted_facets_) {
    glLineStipple(1, 0x00F0);  // штриховой
    glEnable(GL_LINE_STIPPLE);  // разрешаем рисовать прерывистую линию
  } else {
    glDisable(GL_LINE_STIPPLE);  // запрещаем рисовать прерывистую линию
  }
  glBegin(GL_LINES);
  for (auto it = port_data->edges_.cbegin(); it != port_data->edges_.cend();
       it++) {
    const auto &edge = *it;
    glVertex3d(port_data->matrix_[edge.first][0],    //  x
               port_data->matrix_[edge.first][1],    //  y
               port_data->matrix_[edge.first][2]);   //  z
    glVertex3d(port_data->matrix_[edge.second][0],   //  x
               port_data->matrix_[edge.second][1],   //  y
               port_data->matrix_[edge.second][2]);  //  z
  }
  glEnd();
}

void glView::DrawPoints(DataT *port_data, GLfloat size, double red,
                        double green, double blue, int round_vertexes) {
  glColor3d(red, green, blue);  // устанавливаем цвет

  if (round_vertexes) {
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(size);
  glBegin(GL_POINTS);
  for (unsigned int k = 1; k < port_data->count_of_vertexes_ + 1; k++) {
    glVertex3d(port_data->matrix_[k][0], port_data->matrix_[k][1],
               port_data->matrix_[k][2]);
  }
  glEnd();
}

void glView::ChangeProjection() {
  if (!settings_->central_projection_) {
    if (settings_->ratio_ <= 1) {
      // параметры видимости ортогональной проекции
      glOrtho(-1 / (GLfloat)settings_->ratio_, 1 / (GLfloat)settings_->ratio_,
              -1, 1, -1, 10);
    } else {
      glOrtho(-1, 1, -1 * (GLfloat)settings_->ratio_,
              1 * (GLfloat)settings_->ratio_, -1, 10);
    }
    // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
  } else {
    if (settings_->ratio_ <= 1) {
      // параметры видимости перспективной проекции
      glFrustum(-1 / (GLfloat)settings_->ratio_, 1 / (GLfloat)settings_->ratio_,
                -1, 1, settings_->frustrum_near_val_, 10);
    } else {
      glFrustum(-1, 1, -1 * (GLfloat)settings_->ratio_,
                1 * (GLfloat)settings_->ratio_, settings_->frustrum_near_val_,
                10);
    }
    // плоскости отсечения (левая, правая, верхняя, нижняя, ближняя, дальняя)
  }
}
}  //  namespace s21
