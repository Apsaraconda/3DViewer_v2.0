#include "model.h"

namespace s21 {

// перед парсингом структуру обнулять и освобождать не обязательно
int Model::Parsing(char* str, DataT* data) {
  int res = 0;
  FreeData(data);
  long int len_input = 0;
  // копируем файл в одну строку
  FILE* f = fopen(str, "r");
  if (NULL != f) {  // копируем весь файл в одну строку
    res = fseek(f, 0, SEEK_END);  // ставим курсор в конец файла
    if (res == 0) {
      len_input = ftell(f);  // определяем количество символов в файле
      if (len_input == -1) {
        res = 1;
      } else {
        res = fseek(f, 0, SEEK_SET);
        if (!res) {
          char* input = (char*)malloc(sizeof(char) * (len_input + 1));
          if (NULL != input) {
            long int len_read = fread(input, 1, len_input, f);
            if (len_read != len_input)  // ошибка чтения
              res = 1;
            input[len_input] = 0;  // зануляем конец строки
            data->count_of_vertexes_ = 0;
            data->count_of_facets_ = 0;
            if (res == 0) res = CountStruct(input, data);
            if (data->count_of_vertexes_ > 0) {
              res = CreateMatrix(data);
            } else {
              res = 1;
            }
            if (res == 0) res = ParsVertFacet(input, &len_input, data);
            free(input);
          } else {
            res = 1;
          }
        }
      }
    }
    fclose(f);
  } else {
    res = 1;
  }
  return res;
}

int Model::ParsVertFacet(char* input, long int* len_input, DataT* data) {
  int res = 0;
  unsigned int vert = 1;  // текущий номер вершины, которую заполняем
  for (long int i = 0; i < *len_input - 1 && res == 0; i++) {
    if (input[i] == 'v') {
      if (input[i + 1] == ' ') {
        i++;
        ParsingVertexes(input, &i, vert, data);
        FindMinMax(vert, data);
        vert++;
      }
      NextLine(input, &i);
    } else if (input[i] == 'f') {
      if (input[i + 1] == ' ') {
        i++;
        res = ParsingFacets(input, &i, data);
      }
      NextLine(input, &i);
    } else {
      // переходим на следующую строку
      NextLine(input, &i);
    }
  }
  return res;
}

void Model::FreeData(DataT* data) {
  if (data->matrix_ != nullptr) {
    free(data->matrix_);
    data->matrix_ = nullptr;
  }
  data->edges_.clear();
}

void Model::FindMinMax(unsigned int vert, DataT* data) {
  if (vert == 1) {  // обрабатываем максимальные и минимальные значения
    data->minMax_[0] = data->matrix_[1][0];
    data->minMax_[1] = data->matrix_[1][0];
    data->minMax_[2] = data->matrix_[1][1];
    data->minMax_[3] = data->matrix_[1][1];
    data->minMax_[4] = data->matrix_[1][2];
    data->minMax_[5] = data->matrix_[1][2];
  }
  if (data->matrix_[vert][0] < data->minMax_[0])
    data->minMax_[0] = data->matrix_[vert][0];
  if (data->matrix_[vert][0] > data->minMax_[1])
    data->minMax_[1] = data->matrix_[vert][0];
  if (data->matrix_[vert][1] < data->minMax_[2])
    data->minMax_[2] = data->matrix_[vert][1];
  if (data->matrix_[vert][1] > data->minMax_[3])
    data->minMax_[3] = data->matrix_[vert][1];
  if (data->matrix_[vert][2] < data->minMax_[4])
    data->minMax_[4] = data->matrix_[vert][2];
  if (data->matrix_[vert][2] > data->minMax_[5])
    data->minMax_[5] = data->matrix_[vert][2];
}

// парсит координаты вершин
void Model::ParsingVertexes(char* input, long int* i, unsigned int vert,
                            DataT* data) {
  double number = 0;
  for (int j = 0; j < 3; j++) {
    ParsingDouble(input, i, &number);
    data->matrix_[vert][j] = number;
  }
}

// парсинг поверхностей
int Model::ParsingFacets(char* input, long int* i, DataT* data) {
  int res = 0;
  // считаем сколько вершин в поверхности
  unsigned int vert = CountDouble(input + *i);
  unsigned int* facets = (unsigned int*)calloc(vert + 1, sizeof(unsigned int));
  if (facets == NULL) {
    res = 1;
  } else {
    facets[0] = vert;
    for (unsigned int j = 1; j < vert + 1; j++) {
      double number = 0;
      ParsingDouble(input, i, &number);
      facets[j] = (unsigned int)number;
    }
    if (vert > 1) {
      for (unsigned int k = 1; k < vert + 1; k++)
        if ((k + 1) <= vert) {
          std::pair<unsigned int, unsigned int> pair =
              NormalizePair(facets[k], facets[k + 1]);
          data->edges_.insert(pair);
        } else if ((k + 1) > vert) {
          std::pair<unsigned int, unsigned int> pair =
              NormalizePair(facets[k], facets[1]);
          data->edges_.insert(pair);
        }
    }
    free(facets);
  }
  return res;
}

// считает количество чисел в строке
unsigned int Model::CountDouble(char* input) {
  unsigned int res = 0;
  char temp = 0;
  for (int i = 0; input[i] != 0 && input[i] != '\n'; i++) {
    if (input[i] == ' ') {
      temp = 0;
    } else {
      if (temp == 0) {
        res++;
        temp = 1;
      }
    }
  }
  return res;
}

// находит в строке число и переводит его в дабл
void Model::ParsingDouble(char* input, long int* i, double* number) {
  *number = 0;
  char str[50] = {0};  // строка для получения числа
  int j = 0;  // порядковый номер в предыдущем массиве
  //пропускаем пробелы
  while (input[*i] == ' ') ++*i;
  while (input[*i] != ' ' && input[*i] != '\n' && input[*i] != 0) {
    str[j] = input[*i];
    ++*i;
    j++;
  }
  *number = strtod(str, NULL);
}

// считаетколичество вершин и поверхностей
int Model::CountStruct(char* input, DataT* data) {
  int res = 0;  // 0 - все нормально, 1 - ошибка
  for (long int i = 0; input[i] != 0; i++) {
    if (input[i] == 'v') {
      if (input[i + 1] == ' ') data->count_of_vertexes_++;
      NextLine(input, &i);
    } else if (input[i] == 'f') {
      if (input[i + 1] == ' ') data->count_of_facets_++;
      NextLine(input, &i);
    } else {
      // переходим на следующую строку
      NextLine(input, &i);
    }
  }
  return res;
}

int Model::CreateMatrix(DataT* data) {  // выделять буду за один раз
  int res = 0;
  // делаем на один элемент больше, чтобы индекс массива совпадал с номером
  // вершины
  data->matrix_ =
      (double**)malloc((data->count_of_vertexes_ + 1) * sizeof(double*) +
                       (data->count_of_vertexes_ + 1) * 3 * sizeof(double));
  // создаю указатель, направляю его в начало наших чисел
  if (data->matrix_ != NULL) {
    double* p = (double*)(data->matrix_ + data->count_of_vertexes_ + 1);
    // заполняем данные для массива 2го уровня
    for (unsigned int i = 0; i < data->count_of_vertexes_ + 1; i++) {
      data->matrix_[i] = p;
      if (i != data->count_of_vertexes_) p = p + 3;
    }
    for (unsigned int j = 0; j < 3; j++) data->matrix_[0][j] = 0;
  } else {
    res = 1;
  }
  return res;
}

// переходим на следующую строку
void Model::NextLine(char* input, long int* i) {
  while (input[*i] != 0) {
    if (input[*i] == '\n') {
      break;
    }
    ++*i;
  }
  if (input[*i] == 0) --*i;
}

std::pair<unsigned int, unsigned int> Model::NormalizePair(unsigned int a,
                                                           unsigned int b) {
  return std::make_pair(std::min(a, b), std::max(a, b));
}

}  //  namespace s21
