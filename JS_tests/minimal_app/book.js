function Book(slots)
{
	this.isbn = slots.isbn;
	this.author = slots.author;
	this.title = slots.title;
	this.year = slots.year;
	console.log("Book created");
};


Book.instances = {};
storageKey = "bookTable";

Book.recordToObject = function (record)
{
	var book = new Book(record);
	return book;
}

Book.loadAll = function ()
{
	var i=0;
	var key="";
	var keys=[];
	var bookTableString="";
	var bookTable={};

	try{
		if(localStorage[storageKey]){
			bookTableString = localStorage[storageKey];
		}
	} catch(e) {
		alert("Error when reading storage " + e);
	}
	if(bookTableString){
		bookTable = JSON.parse(bookTableString);
		console.log(bookTable);
	}
	// Load all books from persistent storage
};

Book.add = function (slots)
{
	var nb = new Book(slots);
	Book.instances[nb.isbn] = nb;
	console.log("Book added to instance list");
	// Load all books from persistent storage
};

Book.destroy = function ()
{
	// Load all books from persistent storage
	console.log("Book destroyed");
};
n = 1234;
function testBookCreation()
{
	Book.add({isbn:n, author:"Phil", title:"The art of javascript", year:2017});
	n += 1;
	console.log(Book.instances);
};
