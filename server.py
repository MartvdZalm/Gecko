import socket
import threading

HOST = '127.0.0.1'  # Localhost
PORT = 8080

clients = []

def handle_client(conn, addr):
    clients.append(conn)
    print(f"Connected by {addr}")

    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(f"Received from {addr}: {data.decode()}")
            broadcast(data, conn)

    except Exception as e:
        print(f"Exception: {e}")

    finally:
        clients.remove(conn)
        conn.close()
        print(f"Connection closed by {addr}")

def broadcast(message, sender_conn):
    for client in clients:
        if client != sender_conn:
            try:
                client.sendall(message)
            except Exception as e:
                print(f"Error broadcasting message to client: {e}")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print(f"Server listening on {HOST}:{PORT}")

        while True:
            conn, addr = s.accept()
            thread = threading.Thread(target=handle_client, args=(conn, addr))
            thread.start()

if __name__ == "__main__":
    main()