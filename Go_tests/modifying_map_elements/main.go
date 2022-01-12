package main
// This test shows how maps with actual values seem implicitely constant.
// The test demonstrates that
// For MyMap
// - b := MyMap["B"] creates a copy that is modifiable
// - MyMap["B"].Value causes a compilation error
// - MyMap["C"] = new thing works (we can assing something new)
// - &MyMap["B"] causes a compilation error : cannot take address of ...
//
// MyPointerMap
// - c := MyPointerMap["C"] gives us a pointer allowing us to modify the thing
//   that is pointed to.
// - Although we cannot modify the thing in the map for the key "C", we can assign
//   something new there
//
// A map holding pointers to structs will allow us to modify the attributes of
// the structs "contained" in the map (where containted is in quotes because
// the map holds pointers).
//
// PYTHON:
//
// See the python test that shows how the 'almost everything is a pointer'
// paradigm of python causes a difference
//
// b = MyMap["B"]
// b.Value = 8
//
// modifies MyMap["B"].Value
//
// however if MyMap["C"] is a string, then
//
// c = MyMap["C"]
// c = "New string"
//
// does not change MyMap["C"].

import (
	"fmt"
)

type MyThing struct {
	Description string
	Name string
	Value string
}

var MyMap = map[string]MyThing{
	"A": {
		Description: "desc a",
		Name: "a",
		Value: "value A",
	},
	"B": {
		Description: "desc b",
		Name: "b",
		Value: "value B",
	},
	"C": {
		Description: "desc c",
		Name: "c",
		Value: "value C",
	},
}

var MyPointerMap = map[string]*MyThing{
	"A": &MyThing{
		Description: "desc a",
		Name: "a",
		Value: "value A",
	},
	"B": &MyThing{
		Description: "desc b",
		Name: "b",
		Value: "value B",
	},
	"C": &MyThing{
		Description: "desc c",
		Name: "c",
		Value: "value C",
	},
}

func main(){
	fmt.Printf("MyMap : %+v\n", MyMap)

	fmt.Println("We create b := MyMap[B]")
	b := MyMap["B"]
	fmt.Printf("%+v\n", b)

	fmt.Println("We change the Value of the b copy")
	b.Value = "NEW Value"

	fmt.Println("We see that our copy was modified as expected")
	fmt.Printf("%+v\n", b)

	fmt.Println("We can confirm that this is a copy because MyMap[B] was not modified")
	fmt.Printf("%+v\n", MyMap["B"])

	fmt.Printf("Attempts at modifying MyMap[B].Value did not work and are commented\n")
	//
	// var c *MyThing
	//
	// c = &MyMap["C"]
	// ====> ./main.go:x:x: cannot take the address of MyMap["C"]
	//
	// c = MyMap["C"]
	// ====> main.go:x:x: cannot use MyMap["C"] (type MyThing) as type *MyThing in assignment
	//
	// MyMap["B"].Value = "NEW VALUE"
	// ====> ./main.go:x:x: cannot assign to struct field MyMap["B"].Value in map

	c := MyPointerMap["C"]
	c.Value = "NewValue"

	fmt.Println("Although I couldn't modify elements of MyMap, I was to modify MyPointerMap[C].Value")
	fmt.Printf("%+v\n", *MyPointerMap["C"])

	fmt.Println("Assigning something new to MyPointerMap[C]")
	MyPointerMap["C"] = &MyThing{Description: "d", Name:"C", Value: "NewThingValue"}
	fmt.Printf("%+v\n", *MyPointerMap["C"])

	fmt.Println("Assigning something new to MyMap[C]")
	MyMap["C"] = MyThing{Description: "d", Name:"C", Value: "NewThingValue"}
	fmt.Printf("%+v\n", MyMap["C"])
}
