## Установка SBCL на Windows

### Качаем инсталлятор по ссылке с http://www.sbcl.org/platform-table.html
Я поставил 2.3.2

Но в дисте только sbcl.exe и sbcl.core

### Дальше ставим Msys2
Как описано тут:
https://www.msys2.org/

Я ставил версию от 20231026. В директорию C:\msys64, которая по-умолчанию.

### Затем компилим SBCL

В консоли msys2 "MSYS2 MINGW64":

```bash
pacman -S --noconfirm --needed git

# На момент проверки был коммит:
# f62e9659384f25dfeb416d707301ef5175f68702
git clone git://git.code.sf.net/p/sbcl/sbcl

cd sbcl

# Эту команду взял из https://github.com/sbcl/sbcl/blob/cf9dff3b59e4ae0025dbfa542e73c7f1235382c0/azure-pipelines.yml#L62
pacman -S --noconfirm --needed mingw-w64-ucrt-x86_64-gcc make diffutils

PATH="/c/Program Files/Steel Bank Common Lisp/":$PATH sh make.sh --with-sb-linkable-runtime --fancy

# Устанавливаем
sh install.sh --prefix=/c/sbcl

# Ставим quicklisp
cd ~/
curl -O https://beta.quicklisp.org/quicklisp.lisp

/c/sbcl/bin/sbcl --load quicklisp.lisp

# Дальше в REPL
# (quicklisp-quickstart:install)
# (ql:add-to-init-file)
# Эта команда добавит код инициализации в ~/.sbclrc
```

После этих процедур, в `~/sbcl/src/runtime` должен появиться файл `libsbcl.a`, который можно статически слинковать в запускаемый файл или dll.

## Сборка dll из примера

```
cd dll-with-slynk
SBCL_SRC=~/sbcl/ make
```

Теперь у вас должны появиться `libhello.dll`, `app.exe` и `hello.core`. DLL содержит пару функций `hello-world` и `start-slynk`.
Lisp версии этих функций описаны в script.lisp, но если кода много, то лучше вынести их в отдельную ASDF system.
Важно то, что все функции, которые надо сделать вызываемыми из C, должны быть перечислены в аргументе `:callable-exports` функции `sb-ext:save-lisp-and-die`,
а так же описаны с помощью макроса `sb-alien:define-alien-callable`. Кроме того, для каждой экспортируемой функции нужно в `hello.c` файл [добавить указатель](https://github.com/40ants/sbcl-shared-library-examples/blob/master/dll-with-slynk/hello.c#L12-L14)
а в `hello.h` [декларацию](https://github.com/40ants/sbcl-shared-library-examples/blob/master/dll-with-slynk/hello.h#L26-L27).

После запуска `app.exe`, приложение начинает ждать подключения SLY на порту 4005:

```shell
$ ./app.exe
Initializing
Initialized
Calling Lisp function from DLL.
Hello World, Bob!
Calling start-slynk function from DLL.
Starting Slynk on port 4005!
;; Slynk started at port: 4005.
Waiting for connection
Waiting for connection
Waiting for connection
```

# Известные проблемы

Программа часто крэшится. Особенно при попытке загрузить жирные библиотеки прямо в REPL. Лучше загружать их при сборке `core` файла. Например в `script.lisp` есть загрузка `dexador` с помощью `quicklisp`.

# Дальнейшие шаги

Стоит попробовать допилить [sbcl-librarian](https://github.com/quil-lang/sbcl-librarian), так как это избавит от необходимости вручную описывать врапперы в `hello.c` и `hello.h` файлах, а так же будет делать и враппер либы для Python.
