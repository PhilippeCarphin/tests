function message(string){
	document.getElementById("message").innerHTML += "<p>" + string + "</p>";
}
function main(){
	message("using singlequotes inside of double quotes 'HELLO' bla bla.");
	message('using doublequotes inside of single quotes "HELLO" bla bla.');
	message("using escaped double quotes inside of quotes \"HELLO\" bla bla.");
	// Syntax error
	// message("using unescaped double quotes inside of double quotes "HELLO" bla bla.");
	return "result"
}

function do_it(){
	document.getElementById("message").innerHTML = "";
	document.getElementById("output").innerHTML = main();
}
