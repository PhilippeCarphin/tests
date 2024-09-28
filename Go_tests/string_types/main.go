package main

import (
	"fmt"
)

func main() {
	// Backquotes allow for multiline strings but \n is not interpreted
	// and other backslash escapes are not interpreted either
	//
	// This also shows that `fmt.Printf` does not interpret basckslash
	// sequences
	fmt.Printf(`String with \033[32mbackquotes\033[0m\nasdf
xyz`)
	print("\n")
	// Double quotes cannot do multiline strings but \n is interpreted
	fmt.Printf("String with \033[32mdouble quotes\033[0m\nasdf\nxyz")
	print("\n")
}
