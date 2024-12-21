package main
import (
	"golang.org/x/sys/unix"
	"os"
	"fmt"
)

func main() {

	ws, err := unix.IoctlGetWinsize(int(os.Stdout.Fd()), unix.TIOCGWINSZ)

	fmt.Fprintf(os.Stderr, "ws=%v, err=%v, %d\n", ws, err, ws.Col)
}
