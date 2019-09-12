package main

import "fmt"
import "math/rand"
import "time"

type Result int

const (
	ResultTrips = Result(iota)
	ResultDubs
	ResultNone
)

func play(a, b, c int) Result {
	switch {
	case a == b && b == c:
		return ResultTrips
	case a == b || b == c || a == c:
		return ResultDubs
	default:
		return ResultNone
	}
}

func show(r Result) {
	switch r {
	case ResultTrips:
		fmt.Println("You got trips")
	case ResultDubs:
		fmt.Println("You got dubs")
	case ResultNone:
		fmt.Println("You didn't get trips or dubs")
	default:
		fmt.Println("Invalid result")
	}
}

func main() {

	rand.Seed(time.Now().Unix())

	var (
		a = rand.Intn(9)
		b = rand.Intn(9)
		c = rand.Intn(9)
		r = play(a, b, c)
	)

	show(r)
}
