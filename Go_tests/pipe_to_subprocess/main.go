package main
/*
This code demonstrates how to take an exec.Command and pipe some data to its
STDIN.

This approach is good for when the data is small since it is completely read
into a string.
*/

import (
	"fmt"
	"os"
	"os/exec"
	"io/ioutil"
)

func main() {
	c := exec.Command("aha", "-b", "--no-header")

	p, err := c.StdinPipe()
	if err != nil {
		panic(err)
	}

	s, err := ioutil.ReadFile("ansi.txt")
	if err != nil {
		panic(err)
	}
	fmt.Fprintf(os.Stderr, "%s", s)
	p.Write([]byte(s))
	p.Close()

	c.Stderr = os.Stderr

	out, err := c.Output()

	fmt.Printf("%s\n", string(out))
}
