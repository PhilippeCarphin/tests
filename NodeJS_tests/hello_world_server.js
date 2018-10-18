/*
 * Primary file for the API
 */

const http = require('http');


// The server responds to requests with a string
var server = http.createServer(function(req, res){
    console.log('got request on port 3000');
    res.end('Hello World\n');
});

// Start the server, and have it listen on port 3000
server.listen(3000, function(){
    console.log("the server is listening on port 3000");
});

