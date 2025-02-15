import socket
import re
import requests
import whisper

def whisper_api():
    model = whisper.load_model("large")
    audio_path = "received_whisper.wav"
    result = model.transcribe(audio_path)
    transcription = result['text']
    filename = "speaking_ok.txt"
    with open(filename, 'w') as text_file:
        text_file.write(transcription)

def receive_and_save_client_data(client_socket):
    buffer_size = 1024
    # 接收4字节的文件大小信息
    file_size_bytes = client_socket.recv(4)
    file_size = int.from_bytes(file_size_bytes, 'big')
    print("服务端发送的文件大小为 %s" % file_size)
    client_socket.send("准备就绪，可以开始发送文件。".encode("utf-8"))
    
    file_total_size = file_size
    received_size = 0
    with open("received_whisper.wav", "wb") as f:
        while received_size < file_total_size:
            data = client_socket.recv(buffer_size)
            f.write(data)
            received_size += len(data)

    print("客户端文件接收完成，大小为 %s 字节" % received_size)
    whisper_api()  # 处理接收到的WAV文件并生成文本
    
    # 接下来的处理流程
    file_path = "speaking_ok.txt"
    chinese_text = read_chinese_from_file(file_path)
    print("提取的中文文本内容为：", chinese_text)
    response_content = test_function_2(chinese_text)
    client_socket.sendall(response_content.encode('utf-8'))
    client_socket.close()

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = '127.0.0.1'
    port = 8080
    server_socket.bind((host, port))
    server_socket.listen(1)
    print("等待客户端连接...")
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"连接来自 {client_address}")
        receive_and_save_client_data(client_socket)

def read_chinese_from_file(file_path):
    with open(file_path, "r", encoding='utf-8') as file:
        content = file.read()
        chinese_characters = re.findall(r'[\u4e00-\u9fff]+', content)
        chinese_text = ''.join(chinese_characters)
    return chinese_text

def test_function_2(chinese_text):
    url = "http://localhost:8000"
    fixed_prompt = """
给我返回一个包含action和object的JSON格式数据,例如:
[
问题:"帮我拿一个苹果"
{"action": "定位", "object": "苹果"}, 
{"action": "移动", "object": "苹果"}, 
{"action": "抓取", "object": "苹果"}, 
]
"""
    prompt = f"我的输入是: \"{chinese_text}\",请按照例子{fixed_prompt} "
    data = {
        "prompt": prompt,
        "max_length": 2048,
        "top_p": 0.7,
        "temperature": 0.95
    }

    response = requests.post(url, json=data)
    if response.status_code == 200:
        answer = response.json()
        print("Response received from model:", answer["response"])
        return answer["response"]
    else:
        print("Request to model failed:", response.text)
        return "Model request failed."

if __name__ == '__main__':
    start_server()