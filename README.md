# Arduino
Cara mengatasi program eror
Mengatsi program arduino ide yang tidak mau diupload karena akses ke usb masih tertutup di ubuntu
ls /dev/ttyUSB0 untuk mengecek usb dalam kondisi on atau off
sudo chmod a+rw /dev/ttyUSB0 untuk membuka akses
