package main

// Special thanks to https://jarv.org/posts/command-with-timeout/

import (
	"time"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"syscall"
	"strings"
)

func main () {
	fmt.Fprintf(os.Stderr, "Hello\n")
	timeout, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "Could not convert timeout to int: %v\n", err)
		os.Exit(1)
	}
	fmt.Fprintf(os.Stderr, "timeout = %v\n", timeout)
	fmt.Fprintf(os.Stderr, "cmd = %v\n", os.Args[2:])

	cmd := exec.Command(os.Args[2], os.Args[3:]...)
	cmd.SysProcAttr = &syscall.SysProcAttr{Setpgid: true}
	errorStr := strings.Builder{}
	cmd.Stderr = &errorStr

	cmdDoneCh := make(chan error, 1)
	go func(){
		cmdDoneCh <- cmd.Run()
	}()

	if timeout <= 0 {
		<- cmdDoneCh
	} else {
		select {
		case <- time.After(time.Duration(timeout) * time.Second):
			// Timeout can happen while cmd.Process is still nil
			// but that is unlikely since timeout is at least 1sec.
			if cmd.Process != nil {
				syscall.Kill(-cmd.Process.Pid, syscall.SIGTERM)
			}
			fmt.Fprintf(os.Stderr, "Command timed out (timeout=%ds)\n", timeout)
			return
		case <- cmdDoneCh:
		}
	}

	if !cmd.ProcessState.Success() {
		fmt.Fprintf(os.Stderr, "Command exited non-zero: \n%s", errorStr.String())
	}
}
