import socket
import csv
from datetime import datetime

def save_data(additional_data, file='./public/data.csv') -> None:
    with open(file, mode='a', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=['HM', 'TP', 'SL', 'TM'])  # Adjusted fieldnames order
        for row in additional_data:
            writer.writerow(row)

def start_server(host='0.0.0.0', port=5000, dataList=[], humidity=None, temperature=None, soil=None) -> None:
    # Create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    server_socket.bind((host, port))
    
    server_socket.listen(5)
    
    print(f"Server listening on {host}:{port}")
    
    while True:
        client_socket, addr = server_socket.accept()
    
        data = client_socket.recv(1024).decode('utf-8')
        
        if data:
            print(f"Data: {data}")
            dataList = data.split()
            humidity = 0
            temperature = 0
            soil = 0
            try:
                humidity = dataList[1]
                temperature = dataList[4]
                soil = dataList[7]
            except:
                pass
            
            print(humidity, temperature, soil)
            
            # Get current time
            current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            
            # Prepare data to be saved
            savings = [{'HM': humidity, 'TP': temperature, 'SL': soil, 'TM': current_time}]  # Adjusted order
            save_data(savings)
        
        client_socket.close()

if __name__ == '__main__':
    start_server()
