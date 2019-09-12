package main

import (
    "io"
    "os"
    "strings"
    "fmt"
)

type rot13Reader struct {
    r io.Reader
}

func rot13(b byte) byte {
    if 'A' <= b && b <= 'Z' {
        k := b - 'A'
        fmt.Println(k)
        return 'A' + (k - 13 + 26) % 26
    }
    if 'a' <= b && b <= 'z' {
        k := b - 'a'
        return 'a' + (k - 13 + 26) % 26
    }
    return b
}

func (rot *rot13Reader) Read(p []byte) (int, error){
    nr, ne := rot.r.Read(p)
    if ne != nil {
        return nr, ne
    }

    for i:=0; i<nr; i++ {
        p[i] = rot13(p[i])
    }

    return nr, nil
}

func main() {
    s := strings.NewReader(
        "Lbh penpxrq gur pbqr!")
    r := rot13Reader{s}
    io.Copy(os.Stdout, &r)
}