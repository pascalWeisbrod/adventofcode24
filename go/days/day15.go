package days

import (
	"fmt"
	"strconv"
	"strings"
)

func replaceAtIdx(input string, idx int, new_rune rune) string {
    var new_block []rune
    for i := 0; i < len(input); i++ {
        if idx == i {
            new_block = append(new_block, new_rune)
            continue
        }
        new_block = append(new_block, rune(input[i]))
    }
    return string(new_block)
}

func boxPoints(lines []string) int {
    result := 0
    for i, line := range lines {
        for j, c := range line {
            if c == 'O' {
                result += 100 * i + j
            }
        }
    }
    return result
}

func runeAt(lines []string, pos xy) rune {
    if pos.x < 0 || pos.x > len(lines[0]) || pos.y < 0 || pos.y > len(lines) {
        return '#'
    }
    return rune(lines[pos.y][pos.x])
}

func moveBox(lines []string, pos xy, dir xy) {
    if runeAt(lines, pos) != 'O' {
        return 
    }
    nextPos := xy{x: pos.x + dir.x, y: pos.y + dir.y}
    r := runeAt(lines, nextPos)
    if r == '#' {
        return 
    }
    if r == 'O' {
        moveBox(lines, nextPos, dir)
    }
    r = runeAt(lines, nextPos)
    if r == 'O' || r == '#' {
        return
    }

    lines[nextPos.y] = replaceAtIdx(lines[nextPos.y], nextPos.x, 'O')
    lines[pos.y] = replaceAtIdx(lines[pos.y], pos.x, '.')
}

func moveRobo(lines []string, pos xy, dir xy) bool {
    newPos := xy{x: pos.x + dir.x, y: pos.y + dir.y}
    moveBox(lines, newPos, dir)
    return runeAt(lines, newPos) == '.'
}

func Day15(input string) string {
    lines := strings.Split(input, "\n")
    var robo_pos xy 
    var endoffield int
    for y, line := range lines {
        for x, c := range line {
            if c == '@' {
                robo_pos = xy{x: x, y: y}
            }
        }
        if !strings.Contains(line, "#") {
            endoffield = y
            break
        }
    }
    
    lines = lines[:endoffield]

    var idx int
    for i, c := range input {
        if c == '<' || c == '>' || c == '^' || c == 'v' {
            idx = i
            break
        }
    }

    commands := input[idx:]
    
    fmt.Println("Go!")


    for _, c := range commands {
        var dir xy
        switch c {
        case '^':
            dir = xy{x: 0, y: -1}
            break
        case '>':
            dir = xy{x: 1, y: 0}
            break
        case 'v':
            dir = xy{x: 0, y: 1}
            break
        case '<':
            dir = xy{x: -1, y: 0}
            break
        default:
            break
        }
        canMove := moveRobo(lines, robo_pos, dir)
        if canMove {
            lines[robo_pos.y] = replaceAtIdx(lines[robo_pos.y], robo_pos.x, '.')
            robo_pos = xy{x: robo_pos.x + dir.x, y: robo_pos.y + dir.y} 
            lines[robo_pos.y] = replaceAtIdx(lines[robo_pos.y], robo_pos.x, '@')
        }
    }
    
    return "Result: " + strconv.Itoa(boxPoints(lines))
}
