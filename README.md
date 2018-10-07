# Домашнее задание 1
___
## Верстка статического сайта
Целью домашнего задания является подготовка статический верстки сайта (так называемой «рыбы»). Верстку можно размещать в обычных html файлах, в директории public, но рекомендуется сразу размещать верстку в шаблонах Django. Во втором случае понадобится создать примитивные view и роутинг в urls.py.

### 1. Верстка общего вида (layout) страницы
В файле **base.html** нужно создать основную верстку (любой) страницы. Для упрощения задачи нужно скачать и использовать CSS библиотеку [Twitter Bootstrap](https://getbootstrap.com/getting-started). Файлы (как свои CSS стили, так и файлы Bootstrap) нужно разместить в директории static.

При верстке страницы важно обратить внимание на:

- Терпимые отступы (padding/margin) между блоками;
- Юзерблок в шапке (для авторизованного и неавторизованного пользователя);
- Поисковая строка и логотип;
- Блоки в правой колонке.

### 2. Верстка списка вопросов на главной странице
В файле **index.html** нужно создать верстку для списка вопросов. Основную верстку (layout) можно просто скопировать из **base.html**. При использовании шаблонизатора - вам необходимо унаследовать ([extends](https://docs.djangoproject.com/en/2.0/ref/templates/builtins/#std:templatetag-extends)) шаблон от базового.

Обратить внимание на:

- Терпимые отступы (padding/margin) между блоками;
- Аватарки;
- Кнопки лайков;
- Тэги, счетчики ответов, остальные ссылки;
- Пагинатор (список номеров страниц).

### 3. Верстка страницы одного вопроса
HTML разместить в файле **question.html**.

Обратить внимание на:

- Список тегов у вопроса;
- Листинг ответов по верстки аналогичен листингу вопросов.

### 4. Верстка формы добавления вопроса
HTML разместить в файле **ask.html**.

Обратить внимание на:

- **Вывод сообщения об ошибках формы и подсказок к полям**. В верстке должны отображаться ошибки, чтобы было понятно как они сверстаны. Можно найти пример на макетах ниже;
- Ширину полей ввода;
- Максимальную длину полей ввода.

### 5. Верстка форм логина и регистрации
HTML разместить в файлах **login.html** и **signup.html** соответственно.

Обратить внимание на:

- **Вывод сообщения об ошибках формы и подсказок к полям**. В верстке должны отображаться ошибки, чтобы было понятно как они сверстаны. Можно найти пример на макетах ниже;
- Ширину полей ввода;
- Максимальную длину полей ввода.

### 6. Примерный внешний вид страниц

#### 6.1. Страница листинга вопросов

  ![Листинг вопросов](../img/main.png)

#### 6.2. Страница добавления вопроса

  ![Страница добавления вопроса](../img/ask.png)

#### 6.3. Страница одного вопроса

  ![Страница вопроса со списком ответов](../img/single.png)

#### 6.4. Страница листинга вопросов по тегу

  ![Листинг вопросов по тэгу](../img/tags.png)

#### 6.5. Страница пользователя с настройками

  ![Страница пользователя](../img/settings.png)

#### 6.6. Форма авторизации

  ![Форма авторизации](../img/login.png)

#### 6.7.  Форма регистрации

  ![Страница регистрации](../img/reg.png)

Подробное описание страниц и блоков в [техническом задании](technical_details.pdf).

### 7. Полезные ссылки
- Общая информация про [Bootstrap](https://getbootstrap.com/css/#grid);
- [Готовые блоки в Bootstrap](https://getbootstrap.com/components);
- [Верстка форм в Bootstrap](https://getbootstrap.com/css/#forms);
- [Основы шаблонизатора Django](https://docs.djangoproject.com/en/2.0/ref/templates/language);
- [Как отрисовать шаблон](https://docs.djangoproject.com/en/2.0/topics/http/shortcuts/#render).