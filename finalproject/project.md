###關於Final Project

Server

    server_fd : 確認建立socket是否成功
    socket() : domain->屬於IPV4 , socktype->建立TCP連線 , 傳輸的potocal(0代表根據type以及建立的連線來使用相對的預設potocal)  , 最後會回傳一個file descriptor

    new_socket : 如果accept失敗會回傳一個-1宣告error，反之會回傳一個file descriptor
    accept() : socket->server_fd , sockeraddr->adress , addresslength->adrlen

    valread : nothing

    adress : socket要建立的資訊
    sockaddr_in => {sin_family , sin_port , sin_addr , sin_zero}
        sin_family : 可以選擇要IPV4或是IPV6的網路協定
        sin_port : 綁定port號
        sin_addr : 指定那些address可以向server連線
        sin_zero : (沒用過，不確定，之後再補)

    bind() : 指出server要監聽的port以及address
    listen() : 監聽client的動靜
    recv() : 接收client傳過來的file
    send() : 向client發送file

---

####透過IPC撰寫此程式

我建立了一個client端以及一個server端
clent端向server端發送一項指令，server端會回傳指令結果

---

####注意事項

此程式只能在linux執行，windows我還沒有試過

---

####參考

沒有參考

---

####待解決問題

server能夠接受的指令不夠多(正在寫當中)
因為課程屬於"系統程式"所以打算朝著重"IPC"的方向，例如做出一個2-3人對戰遊戲(終端機畫面)透過向server發送指令來做到同步效果