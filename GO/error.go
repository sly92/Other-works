package main

import (
	"fmt"
	"math"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("Cannot Sqrt negativ number : %g", float64(e))
}

func Sqrt(x float64) (float64, error) {
 
 if x < 0 { return 0, ErrNegativeSqrt(x) }
 	if x==0 { return 0, nil }
    z := 1.0
    for i := 0; i < int(x); i++ {
        z = z - ((math.Pow(z, 2) - x) / (2 * z))
    }
    return z, nil
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))

}
