package main

import (
	"fmt"
)

func myPrintf(format string, a ...interface{}) {
	fmt.Printf("myPrintf(): " + format + "\n", a...)
}

func main(){

	s := "Hello World"
	i := 42
	b := true

	myPrintf("String: %s, int: %d, bool: %t", s, i, b)
}
