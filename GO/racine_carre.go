package main

import( 
		"fmt"
		"math"
)

const TOLERANCE = 0.000001

var(
		z=2.
		s=0.
		i=0
		
)

func SQRT(x float64) float64 {
	
	for {
		s = z
		z = s - (math.Pow(s,2) - x )/(2*s)
		fmt.Println("s = ",s)
		fmt.Println("z = ",z)
		if diff := math.Abs(s - z); diff < TOLERANCE {
			break
		}
		
	}
	return s
}

func main(){

	fmt.Println(SQRT(2))
	fmt.Println(math.Sqrt(2))	
}	