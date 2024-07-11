#include "model.h"

namespace s21 {

int Model::CountsItoA(unsigned int data, char *result) {
  int error = 0;
  if (data == 0) {
    result[0] = '\0';
  } else {
    char *res = (char *)malloc(data);
    if (res == NULL) {
      error = 1;
    } else {
      char tmp_char;
      int tmp_value;
      int base = 10;
      int i = 0;
      while (data) {
        tmp_value = data;
        data /= base;
        res[i] = "0123456789"[(tmp_value - data * base)];
        i++;
      }
      int k = 0;
      i--;
      while (k < i) {
        tmp_char = res[i];
        res[i] = res[k];
        res[k] = tmp_char;
        k++;
        i--;
      }
      res[k + i + 1] = '\0';
      i = 0;
      while (res[i] != '\0') {
        result[i] = res[i];
        i++;
      }
      result[i] = '\0';
      free(res);
    }
  }
  return error;
}

}  //  namespace s21
