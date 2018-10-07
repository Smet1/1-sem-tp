// From: admin\n
// Subject: hi\n
// Sender: admin\0
// EOF = ctr + D

// TODO(): add_item - не оптимальна(кек) не нужно копировать в новую память старые строки - достаточно "переместить" их, т.е. просто перенести указатели вообще есть стандартная функция realloc, которая увеличивает размер массива, лучше воспользоваться ей
// TODO(): realloc только вот нахуя
// TODO(): ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct buf {  // типа строка
    char* str;  // string
    size_t size;  // used mem in char
    size_t capacity;  // capacity
};

void init_buf(struct buf *);  // около конструктор

void free_buf(struct buf *);  // около деструктор

int copy_buf(struct buf*, struct buf*);

struct mas_str {  // массив строк
    struct buf* elem;  // хранимые элементы
    size_t size;  // реал сайз
    size_t capacity;  // капасити
};

int add_item(struct mas_str*, struct buf*);

int str_input(struct buf*);

struct mas_str* parse_str(const struct mas_str*);


int main() {
    struct mas_str all_str = {NULL, 0, 0};  // хранит весь ввод
    struct buf tmp_buf;  // хранит только одну введенную строку
    init_buf(&tmp_buf);

    while (str_input(&tmp_buf) == 1) {
        add_item(&all_str, &tmp_buf);

        free_buf(&tmp_buf);
    }

    struct mas_str* res = parse_str(&all_str);  // результат парсера
    for (size_t i = 0; i < res->size; i++) {
        printf("%s", res->elem[i].str);
    }

    free_buf(&tmp_buf);

    for (size_t i = 0; i < all_str.size; i++) {
        free_buf(&all_str.elem[i]);
    }
    free(all_str.elem);

    for (size_t i = 0; i < res->capacity; i++) {
        free_buf(&res->elem[i]);
    }
    free(res->elem);
    free(res);
    return 0;
}

void init_buf(struct buf *init_buf) {
    init_buf->str = NULL;
    init_buf->size = 0;
    init_buf->capacity = 0;
}

void free_buf(struct buf *free_buf) {
    free(free_buf->str);
    init_buf(free_buf);  // мб не надо, да и выглядит странно, но конструктор зануляет все значения
}

int copy_buf(struct buf* l_buf, struct buf* r_buf) {
    if (!r_buf || !r_buf->str || !l_buf) {
        printf("!r_buf || !r_buf->str || !l_buf\n");
        return 1;
    }

    char* tmp = (char*)malloc((r_buf->size + 1) * sizeof(char));
    if (!tmp) {
        printf("[error]\n");
        return 1;
    }

    strncpy(tmp, r_buf->str, r_buf->size);
    tmp[r_buf->size] = 0;
    l_buf->str = tmp;

    tmp = NULL;
    l_buf->size = r_buf->size;
    l_buf->capacity = r_buf->size;

    return 0;
}

int add_item(struct mas_str* in_mas, struct buf* in_buf) {
    if (in_mas->size + 1 > in_mas->capacity) {
        size_t new_size = (in_mas->capacity * 2) > 4 ? (in_mas->capacity * 2) : 4;  // стандартный размер 4

        in_mas->elem = (struct buf*)realloc(in_mas->elem, (new_size) * (sizeof(struct buf)));
        if (!in_mas->elem) {
            return 1;
        }
        for (size_t i = in_mas->size + 1; i < new_size; i++) {  // зануляю выделенную неиспользованную память
            init_buf(&in_mas->elem[i]);
        }
        in_mas->capacity = new_size;
    }

    copy_buf(&in_mas->elem[in_mas->size], in_buf);  // добавление in_buf в конец
    in_mas->size++;

    return 0;
}

int str_input(struct buf* tmp_buf) {  // '\0' - 0, '\n' - 1
    char in_char;  // введенный символ

    while ((in_char = getchar()) != 'D') {  // В силайоне не работает поэтому там 'D'
        if (tmp_buf->size + 1 > tmp_buf->capacity) {
            size_t new_size = ((tmp_buf->capacity * 2)>(16))?(tmp_buf->capacity * 2):(16);

            tmp_buf->str = (char *)realloc(tmp_buf->str, (new_size + 1) * sizeof(char));
            if (!tmp_buf->str) {
                return 1;
            }
            tmp_buf->capacity = new_size;
        }
        tmp_buf->str[tmp_buf->size] = in_char;
        tmp_buf->size++;

        if (in_char == '\n') {
            return 1;
        }
    }
    return 0;
}

struct mas_str* parse_str(const struct mas_str* in_mas) {
    if (!in_mas) {
        return NULL;
    }

    struct mas_str* result = (struct mas_str*)malloc(1 * sizeof(struct mas_str));
    result->capacity = 0;
    result->size = 0;
    result->elem = NULL;
    for (size_t i = 0; i < in_mas->size; i++) {
        if (((strncmp(in_mas->elem[i].str, "Date: ", 6)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "From: ", 6)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "To: ", 4)) == 0) ||
            ((strncmp(in_mas->elem[i].str, "Subject: ", 9)) == 0)) {

            add_item(result, &in_mas->elem[i]);
        }
    }
    return result;
}
