package main

import (
	"os/exec"
	"fmt"
	"strings"
)

func runScript(exitCode int, stdoutStr string, stderrStr string, captureStderr bool){
	script := strings.Builder{}
	fmt.Fprintf(&script, "echo '%s' >&2\n", stderrStr)
	fmt.Fprintf(&script, "echo '%s'\n", stdoutStr)
	fmt.Fprintf(&script, "exit %d\n", exitCode)

	stderr := strings.Builder{}
	cmd := exec.Command("/bin/bash", "-c", script.String())


	if captureStderr {
		cmd.Stderr = &stderr
	}

	stdout, err := cmd.Output()
	fmt.Printf("stdout = '%s'\n", string(stdout))
	if captureStderr {
		fmt.Printf("stderr = '%s'\n", stderr.String())
	}
	fmt.Printf("err = %#v\n", err)
	if exitErr, ok := err.(*exec.ExitError) ; ok {
		// Syntax to say "if err is an *exec.ExitError, assign
		// err as an exec.ExitError to exitErr so I can get stuff
		// out of it.
		fmt.Printf("stderr = %s\n", exitErr.Stderr)
	}
	cmdExitCode := cmd.ProcessState.ExitCode()
	fmt.Printf("exit code = %d\n", cmdExitCode)
	fmt.Println("=========================================================")

}

func main() {
	// When the script returns a non-zero exit code, the `cmd.Output()`
	// function returns an error of type `*exec.ExitError` which has
	// two fields, ProcessState (of type *os.ProcessState) and Stderr
	// (of type []uint8).
	runScript(88, "stdout", "stderr", false)
	// If the script returns 0, then the error from `cmd.Output` will be
	// nil and we won't have access to the stderr of the command.
	runScript(0, "stdout", "stderr", false)
	// However if we change `cmd.Stderr` to something else like a
	// `strings.Builder` we will have access to the stderr of the command
	// regardless of whether the command exits with zero or non-zero exit
	// code.
	runScript(0, "stdout", "stderr", true)
	//  In that case, if there is a non-zero exit code, the error's
	// `Stderr` field will be an empty array of bytes.
	runScript(88, "stdout", "stderr", true)
}
