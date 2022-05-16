import http.server
from pprint import pprint
import json

class MyServer(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        print(f"INCOMING POST REQUEST ON self.path = {self.path}")
        print(f"Headers\n=======\n\n{self.headers}\n")
        if 'Content-Length' in self.headers:
            content_length = int(self.headers['Content-Length'])
            request_body = self.rfile.read(content_length).decode('utf-8')
            if 'Content-Type' in self.headers and self.headers['Content-Type'] == 'application/json':
                request = json.loads(request_body)
                print("JSON Response\n==============\n")
                pprint(request)
                print()
            else:
                print(f"Request body\nrequestpbody\n\n{request_body}\n")

        self.send_header('Content-Type', 'application/json')
        self.end_headers()
        self.wfile.write(bytes(json.dumps({"message": "Hello World"},indent='    ') + '\n', 'utf-8'))
        self.send_response(200)

server = http.server.HTTPServer(("0.0.0.0", 5447), MyServer)

server.serve_forever()
