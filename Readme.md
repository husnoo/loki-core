


```
./setup_deps.sh
```

# test linux version
```
make -j8
make run
```


# build android version
```
$ android-studio &

(Artic Fox, 2020.3.1)
SDK platform 7.0 Nougat, API 24.
SDK platform tools 33.0.3
```

Use Android Studio to open `loki-core/android/android` as a project

```
$ adb shell
On device:
$ mkdir /storage/sdcard0/Loki

On laptop:
$ adb push deps/chibi-scheme-static/lib/*  /storage/sdcard0/Loki/chibi-lib
```









