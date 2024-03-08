# Basic CI/CD

## Содержание

1. [Part 1. Настройка gitlab-runner](#part-1-настройка-gitlab-runner)
2. [Part 2. Сборка](#part-1-настройка-gitlab-runner)
3. [Part 3. Тест кодстайла](#part-1-настройка-gitlab-runner)
4. [Part 4. Интеграционные тесты](#part-1-настройка-gitlab-runner)
5. [Part 5. Этап деплоя](#part-1-настройка-gitlab-runner)
6. [Part 6. Дополнительно. Уведомления](#part-1-настройка-gitlab-runner)

## Part 1. Настройка gitlab-runner

1. Поднять виртуальную машину `Ubuntu Server 22.04 LTS`:

    ![part 1.1](screenshots/Part_1/1.png)

2. Скачать и установить на виртуальную машину `gitlab-runner`:

    ``` bash
    curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
    ```

    ![part 1.2](screenshots/Part_1/2.png)

    ``` bash
    sudo apt-get install gitlab-runner
    ```

    ![part 1.3](screenshots/Part_1/3.png)

3. Запустить `gitlab-runner` и зарегистрировать его для использования в текущем проекте (`DO6_CICD`).

    >Для корретной работы Runner его необходимо связать с текущим проектом.

    * Для регистрации раннера необходимы `URL` и `токен`. Их можно взять со страницы Task на платформе:

        ![part 1.4](screenshots/Part_1/4.png)

    * Запустить `gitlab-runner`:

        ``` bash
        sudo gitlab-runner start
        ```

        ![part 1.5](screenshots/Part_1/5.png)

    * Зарегистрировать текущий проект:

        ``` bash
        sudo gitlab-runner register
        ```

        ![part 1.6](screenshots/Part_1/6.png)






    



[Содержание](#содержание)

## Part 2. Сборка

[Содержание](#содержание)

## Part 3. Тест кодстайла

[Содержание](#содержание)

## Part 4. Интеграционные тесты

[Содержание](#содержание)

## Part 5. Этап деплоя

[Содержание](#содержание)

## Part 6. Дополнительно. Уведомления

[Содержание](#содержание)
