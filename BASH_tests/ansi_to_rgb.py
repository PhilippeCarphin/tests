def ansi_to_rgb(ansi):
    if ansi < 16:
        return "no"

    if 16 <= ansi <= 231:
        val = ansi - 16
        b = val % 6
        val = val // 6
        g = val % 6
        r = val // 6
        rgb = (r,g,b)
        true_values = [0,95,135, 175 ,215,255]
        RGB = (true_values[r], true_values[g], true_values[b])
        return RGB

def ansi_to_grayscale(ansi):
    R, G, B = ansi_to_rgb(ansi)
    return (30*R + 59*G + 11*B)//100

def ansi_to_ansi_grayscale(ansi):
    gray = ansi_to_grayscale(ansi)
    return 232 + (gray*(255 - 232))//255

import sys
print(ansi_to_rgb(int(sys.argv[1])))
print(ansi_to_ansi_grayscale(int(sys.argv[1])))
