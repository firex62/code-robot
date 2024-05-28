import serial
import time

ser = serial.Serial("/dev/ttyACM0", 115200, 8,'N',1,1000)

def requestt():
    while True:
        if ser.inWaiting() > 0:
            message = ser.readline().decode().strip()
            print('Received : ' + message)
            if message == "REQ":
                print("Requested")
                break

def kirim(perintah):
    ser.write(perintah.encode())
    time.sleep(1)
    while ser.inWaiting() > 0:
        print(ser.readline().decode().strip())

# waitt()

while True:
    requestt()
    # nilai = int(input("Masukkan nilai : "))
    nilai = 20
    kirim(str(nilai))
    # if nilai == 300:
    #     break
    
    print('Nilai yang dikirimkan : ' + str(nilai))