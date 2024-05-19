import socket
import csv


def save_data(additional_data, file ='./public/data.csv') -> None:

    with open(file, mode='a', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=['HM', 'TP', 'SL'])

        for row in additional_data:
            writer.writerow(row)


def start_server(host ='0.0.0.0', port =5000, dataList = [], humidity = None, temperature = None, soil = None) -> None:
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
            humidity = dataList[1]
            temperature = dataList[4]
            soil = dataList[7]
            
            print(humidity, temperature, soil)
            savings = [{'HM': humidity, 'TP': temperature, 'SL': soil}]
            save_data(savings)
            
        
        
        client_socket.close()

if __name__ == '__main__':
    start_server()
