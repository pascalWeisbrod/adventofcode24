package days

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

type xy struct {
    x int
    y int
}

func mashine(a xy, b xy, prize xy) int {
    for i := 0; i < 100; i++ {
        for j := 0; j < 100; j++ {
            if i * a.x + j * b.x == prize.x && i * a.y + j * b.y == prize.y {
                return 3 * i + j
            }
        }
    }
    return 0
}

func secondMashine(a xy, b xy, prize xy) int {
    factor := float64(a.y) / float64(a.x)
    y := math.Round((float64(prize.y) - factor * float64(prize.x)) / (float64(b.y) - factor * float64(b.x)))
    x := math.Round((float64(prize.x) - float64(b.x) * y) / float64(a.x))

    if math.Floor(x) == x && math.Floor(y) == y {
        if a.x * int(x) + b.x * int(y) == prize.x && a.y * int(x) + b.y * int(y) == prize.y {
            return 3 * int(x) + int(y)
        }
    }
    return 0
}

func Day13Part1(text string) string {
    lines := strings.Split(text, "\n")
    
    var a []xy
    var b []xy
    var prize []xy
    for i := 0; i < len(lines); i += 4 {
        x, _ := strconv.Atoi(lines[i][len("Button A: X+"):(strings.Index(lines[i], ","))])
        y, _ := strconv.Atoi(lines[i][strings.LastIndex(lines[i], "+"):len(lines[i]) - 1])
        a = append(a, xy{x: x, y: y })
        x, _ = strconv.Atoi(lines[i + 1][len("Button B: X+"):(strings.Index(lines[i + 1], ","))])
        y, _ = strconv.Atoi(lines[i + 1][strings.LastIndex(lines[i + 1], "+"):len(lines[i + 1]) - 1])
        b = append(b, xy{x: x, y: y })
        x, _ = strconv.Atoi(lines[i + 2][len("Prize: X="):(strings.Index(lines[i + 2], ","))])
        y, _ = strconv.Atoi(lines[i + 2][strings.LastIndex(lines[i + 2], "=") + 1:len(lines[i + 2]) - 1])
        prize = append(prize, xy{x: x, y: y })
    }

    fmt.Println("Go!")
    
    result := 0
    second_result := 0
    for i := 0; i < len(a); i++ {
        result += secondMashine(a[i], b[i], prize[i])
        second_result += secondMashine(a[i], b[i], xy{prize[i].x + 10000000000000, prize[i].y + 10000000000000})
    }
    return "First result: " + strconv.Itoa(result) + "\nSecond result: " + strconv.Itoa(second_result)
}
