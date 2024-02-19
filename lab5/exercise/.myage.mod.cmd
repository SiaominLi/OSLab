cmd_/home/s109037012/lab5/exercise/myage.mod := printf '%s\n'   myage.o | awk '!x[$$0]++ { print("/home/s109037012/lab5/exercise/"$$0) }' > /home/s109037012/lab5/exercise/myage.mod
