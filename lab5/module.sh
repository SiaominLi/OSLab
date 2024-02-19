輸入 make 編譯成 .ko 檔

查看module資訊：modinfo hello_module.ko

安裝 kernel module：sudo insmod hello_module.ko

使用 lsmod 指令查看 hello_module 是否成功安裝

確認 hello_module 是否成功印出訊息：sudo dmesg | tail 

dmesg：顯示 kernel 訊息  tail：顯示末 10 筆資料

解除安裝 kernel module：**sudo rmmod hello_module**
