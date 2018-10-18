
/*
 * This test demonstrates the use of regexes in the string replace function.
 *
 * Note that there are no quotes around the regex.  Thanks for the confusion JS.
 */

var path = '/asdfa/asdf/asfa///';
var trimmedPath = path.replace(/^\/+|\/+$/g, '');
console.log(path);
console.log(trimmedPath);
