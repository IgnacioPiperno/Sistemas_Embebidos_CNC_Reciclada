import serial
import time


FILE_NAME = "cara_0004.NGC"
f_in = open(FILE_NAME,'rt')

baudrate = 115200
ser = serial.Serial('COM20', baudrate, timeout = 60)


flag = True

string = ""
time.sleep(3)

while(flag):
    data = ser.read() # espero a que el caracter de confirmación la EDU-CIAA 
    if(data == b''): # Si no llega nada despupés del timeout, corto el programa (no debe estar conectada)
        print("Timeout ocurred: CNC not connected")
        ser.close()
        f_in.close()
        break
    else: 
        print(f"status: {data}") #muestro el estado de la máquina (un b\x00 es STATUS_OK)
        print(time.time())

        if(data == b'O'): # el caracter 'O' es el caracter de confirmación de envío
            string = f_in.readline()
            for c in string:
                while ser.out_waiting > 15: # espero a que se vacíe el buffer de envío (para instrucciones largas)
                    continue
                if c == '(': # no envío comentarios
                    c = '\n'
                    ser.write(c.encode('utf-8'))
                    break
                else:
                    ser.write(c.encode('utf-8'))
            print(f"mandó {string}") #muestro la línea que se envió a la EDU-CIAA
            data = ""
                
        if string == "#\n": #la línea "#\n" indica finalización del archivo
            f_in.close()
            ser.close()
            break
