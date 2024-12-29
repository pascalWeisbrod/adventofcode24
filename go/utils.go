package main

import (
    "os"
    "strconv"
)


func GetInput(day int) string {
    path := "C:\\Users\\pe190\\Desktop\\GitHub\\aoc\\adventofcode24\\inputs\\input" + strconv.Itoa(day) + ".txt"
    dat, err := os.ReadFile(path)
    if err != nil {
        panic(err)
    }
    return string(dat) 
}
