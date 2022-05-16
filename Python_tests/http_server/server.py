import http.server
import json

class MyServer(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        print(f"INCOMING POST REQUEST ON self.path = {self.path}")
        print(f"Headers = {{{self.headers}}}")
        self.send_header('Content-Type', 'application/json')
        if 'Content-Length' in self.headers:
            content_length = int(headers['Content-Length'])
            request_body = self.rfile.read(content_length).decode('utf-8')
            print(f"request_body = {request_body}")
        self.end_headers()
        self.wfile.write(bytes(json.dumps({"message": "Hello World"},indent='    ') + '\n', 'utf-8'))

server = http.server.HTTPServer(("0.0.0.0", 5447), MyServer)

server.serve_forever()
