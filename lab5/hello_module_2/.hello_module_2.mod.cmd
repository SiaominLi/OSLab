cmd_/home/s109037012/lab5/hello_module_2/hello_module_2.mod := printf '%s\n'   hello_module_2.o | awk '!x[$$0]++ { print("/home/s109037012/lab5/hello_module_2/"$$0) }' > /home/s109037012/lab5/hello_module_2/hello_module_2.mod
