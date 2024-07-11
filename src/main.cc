#include <QApplication>

#include "view/view.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "en_US.UTF-8", 1);
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::View w(&controller);
  w.show();
  return a.exec();
}
