"""
This is just a milion ways to compute the winning or draw values when
using Chinese rules in go
"""

def min_black_win(komi, size):
    """
    (note : w is white points including komi)
    b - w > 0
    b - (s^2 - b + k) > 0
    2b - s^2 + k > 0
    2b > s^2 + k > 0
    b > (s^2 + k)/2
    Note: int truncates, so int(0.99) == 1, So for example, if komi is 6.5,
    and s == 9, then the inequality becomes  b > (81+6.5)/2 == 87.5/2 == 43.75
    which means black needs 44 points and int(43.75) is 43 and 43+1 is 44.
    """
    return int((size ** 2 + komi)/2) + 1

def display_black_win_fractional_komi(komi, size):
    mbw = min_black_win(komi, size)
    print(f"On a {size}x{size} with {komi} points komi, black needs {mbw} points to win")

def min_white_win(komi, size):
    """
    (note : w is white points including komi, w-k is white's points on the board)
    wb + k > b
    wb + k > s^2 - wb
    2wb + k > s^2
    2wb > s^2 - k
    wb > (s^2 - k)/2
    Ex: size == 99, komi == 6.5 gives
    int((81 - 6.5)/2) + 1 == int(37.25) + 1 == 38.
    This makes sense if we compare to the values we are used to for 9x9 on
    GoQuest.  It's a draw with 44 for black and 37 for white.  If we reduce komi
    by 0.5, it should be easier for black to win and harder for white.

    Indeed, the draw value of 44 for black becomes the minimum points to win.
    And for white, the minimum draw value becomes a loss and the minimum points
    to win becomes 38.
    """
    return int((size**2 - komi)/2) + 1

def black_draw(komi, size):
    """
    black_points - white_points == 0
    black_board_points - (size^2 - black_board_points + komi) == 0
    2*black_board_points - size^2 - komi == 0
    2*black_board_points == size^2 + komi
    black_board_points == (size^2 + komi)/2
    """
    return (size**2 + komi)/2

def white_draw(komi, size):
    """
    bp - wp == 0
    (size^2 - white_board_points) - (white_board_points + komi) == 0
    size^2 - 2*white_board_points - komi == 0
    size^2 - komi == 2*white_board_points
    (1j2)*(size^2 - komi) == white_board_points
    """
    return (size**2 - komi)/2

def show_black_draw(komi, size):
    draw_pts = black_draw(komi, size)
    print(f"On a {size}x{size} with {komi} points komi, black needs {draw_pts} points on the board for a draw")

def show_white_draw(komi, size):
    draw_pts = white_draw(komi, size)
    print(f"On a {size}x{size} with {komi} points komi, white needs {draw_pts} points on the board for a draw")

def white_score(pts, komi, size):
    black_points = size**2 - pts
    white_points = pts + komi
    return white_points - black_points

def black_score(pts, komi, size):
    return -1 * white_score(pts, komi, size)

def show(pts, komi, size):
    result = white_score(pts, komi, size)
    if result == 0:
        result_str = f"draw"
    elif result < 0:
        result_str = f"black by {-result}"
    else:
        result_str = f"white by {result}"

    print(f"{size}x{size}, komi={komi} white board points: {pts} -> {result_str}")

def show_draws_for_various_values():
    show_black_draw(7, 9)
    show_white_draw(7, 9)
    show_black_draw(7, 13)
    show_white_draw(7, 13)
    show_black_draw(7, 19)
    show_white_draw(7, 19)
    show_black_draw(6.5, 19)
    show_white_draw(6.5, 19)

def goquest_win_percentage(w,l):
    t = w+l
    return w / t

def goquest_win_stat(w,l):
    t = w+l
    return (t/2 - l) / 2

def show_goquest_stats(w,l):
    ws = goquest_win_stat(w,l)
    p = goquest_win_percentage(w,l)
    print(f"Wins: {w}, Losses: {l}, Winstat: {ws}, Percent: {p}")

if __name__ == "__main__":

    show_draws_for_various_values()
    # show(81, 7, 13)
    # show(45, 7, 9)
    # show(37, 7, 9)
    # show_goquest_stats(w=844, l=669)
    # show_goquest_stats(w=169, l=144)


