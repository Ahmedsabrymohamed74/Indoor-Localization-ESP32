import socket
import pandas as pd
import numpy as np 
#in
s = socket.socket()

s.bind(('0.0.0.0', 9001))
s.listen(0)
data = []
MAC_arr1 = []
RSSI_arr1 = []
while True:
    client, addr = s.accept()
    while True:
        content = client.recv(2567).decode('utf-8').replace('\r\n','')
 
        if len(content) == 0:
           break
        else:       
            data.append(content)
            print(content)
    for x in range(len(data)):
        MAC_arr1 = data[::2]
        RSSI_arr1 = data[1::2]
    print("Closing connection")
    client.close()



Ax= data.iloc[:,:]
df= pd.DataFrame(Ax)