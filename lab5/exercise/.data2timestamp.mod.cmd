cmd_/home/s109037012/lab5/exercise/data2timestamp.mod := printf '%s\n'   data2timestamp.o | awk '!x[$$0]++ { print("/home/s109037012/lab5/exercise/"$$0) }' > /home/s109037012/lab5/exercise/data2timestamp.mod
