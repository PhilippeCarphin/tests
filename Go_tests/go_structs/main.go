package main;

import "fmt"
import "time"

type person struct {
	id int
	name string
}

func (p *person) printMe(){
	fmt.Println(*p);
}

func printer(caller string){
	for i := 0; i < 8; i++ {
		fmt.Println(caller, ":", i)
		time.Sleep(time.Millisecond)
	}
}

func main(){
	
	fmt.Println("Hello World")

	// Trying object syntax
	someGuy := person{id: 1234, name: "Phil"}
	someGuy.printMe()

	// Trying goroutines.  The wait at the end is necessary
	// because the program won't wait for goroutines to finish
	// and will let the process end.
	go printer("goroutine1")
	go printer("goroutine2")
	go func(msg string) {
		fmt.Println(msg)
	}("going")
	time.Sleep(time.Second)
	fmt.Println("done")
}