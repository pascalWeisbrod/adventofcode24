package days

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func Day17C1(input string) string {
    lines := strings.Split(input, "\n")
    var registers [3]int
    
    for i := 0; i < 3; i++ {
        value, _ := strconv.Atoi(lines[i][len("Register A: "):len(lines[i]) - 1])
        registers[i] = value 
    }

    var operations []int
    for _, op := range strings.Split(lines[4][len("Program: "):], ",") {
        dat, _ := strconv.Atoi(op)
        operations = append(operations, dat)
    }


    // Go!
    
    fmt.Println(registers)
    fmt.Println(operations)
    var outputs []int
    for i := 0; i < len(operations); i++ {
        fmt.Println(operations[i])
        switch operations[i] {
        case 0:
            combo := 0
            numerator := registers[0]
            denominator := 2 ^ combo
            registers[0] = numerator / denominator
            break
        case 1:
            combo := 1
            registers[1] = xor(registers[1], combo)
            break
        case 2:
            combo := 2
            registers[1] = combo % 8 
            break
        case 3:
            //combo := 3
            if registers[0] == 0 {
                break
            }
            i = registers[0] - 1
            break
        case 4:
            //combo := registers[0]
            registers[1] = xor(registers[1], registers[2]) 
            break
        case 5:
            combo := registers[1]
            outputs = append(outputs, combo % 8)
            break
        case 6:
            combo := registers[2]
            numerator := registers[0]
            denominator := 2 ^ combo
            registers[1] = numerator / denominator
        case 7:
            combo := 7
            numerator := registers[0]
            denominator := 2 ^ combo
            registers[2] = numerator / denominator
            break
        }
    }
    output := ""
    for _, o := range outputs {
        output += strconv.Itoa(o) + ","
    }

    return output[0:len(output) - 1]
}


func xor(a int, b int) int {
    length := int(math.Log2(float64(a))) + 1
    value := 0
    for j := 0; j < length; j++ {
        bb := (a & 2 ^ j) != 0
        cb := (b & 2 ^ j) != 0
        if bb != cb {
            value += 2 ^ j
        }
    }
    return value
}
