/*******************************************************************************
 * This demonstrates creation of a class.
 * It has mechanisms for defining a constructor that, with the new operator,
 * defines a class and provides the mechanism for creating it.  Only by using
 * the new operator can we get an actual instance of a "class" (JavaScript
 * technically doesn't have classes), otherwise the this keyword doesn't have
 * meaning in the constructor (as I understand it being at my first day of JS)
 * The prototype mechanism allows for the definition of methods.
*******************************************************************************/

// Source
// https://www.codeproject.com/Articles/753724/JavaScript-Front-End-Web-App-Tutorial-Part
function message(string){
	document.getElementById("message").innerHTML += "<p>" + string + "</p>";
}

// Defining a class and using the prototype thing

// First define a constructor:
// What makes this a special kind of function is that we're going to use it with
// the 'new' operator.
function Person( first_name, last_name )
{
	this.first = first_name;
	this.last = last_name;
}

// Define a method (This can be done before having defined a constructor.
Person.prototype.getFullName = function ()
{
	var retval = this.first + " " + this.last;
	message("GetFullName : retval = " + retval);
	return retval;
}

function main()
{
	var p = new Person("Philippe", "Carphin");
	message("Created person Philippe Carphin");
	return p.getFullName();
}

function do_it()
{
	document.getElementById("message").innerHTML = "";
	document.getElementById("output").innerHTML = main();
}
