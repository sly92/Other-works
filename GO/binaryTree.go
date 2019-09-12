package main

import (
		"golang.org/x/tour/tree"
	    "fmt"
)


func Walk(t *tree.Tree, ch chan int) {
	walkRecur(t, ch)
	close(ch)
}

func walkRecur(t *tree.Tree, ch chan int) {
	if t == nil {
		return
	}
	walkRecur(t.Left, ch)
	ch <- t.Value
	walkRecur(t.Right, ch)
}

func Same(t1, t2 *tree.Tree) bool {
    ch1 := make(chan int)
    ch2 := make(chan int)
    go Walk(t1, ch1)
    go Walk(t2, ch2)
    for v1 := range ch1 {
        v2, ok := <-ch2
        if !ok || v1 != v2 {
            return false
        }
    }
    return true
}

func main() {
    ch := make(chan int)
    go Walk(tree.New(1), ch)
    for v := range ch {
        println("tree:", v)
    }
    fmt.Println("same 1,1", Same(tree.New(1), tree.New(1)))
    fmt.Println("same 1,2", Same(tree.New(1), tree.New(2)))
}
