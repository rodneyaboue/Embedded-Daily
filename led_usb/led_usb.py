import time

arduino_port = '/dev/ttyACM0'

with open(arduino_port, 'w') as arduino:
        while True:
            cmd = input("Allumer 1 ou eteindre 0 ? \n")
            if cmd in ['0', '1']:
                arduino.write(cmd + '\n')
                arduino.flush()
            else:
                print("Tapez 1 ou 0\n")