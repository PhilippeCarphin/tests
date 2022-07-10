#!/usr/bin/env python3

from enum import Enum
import enum

class DayOfWeek(Enum):
    MONDAY = 1
    TUESDAY = 2
    WEDNESDAY = 3
    THURSDAY = 4
    FRIDAY = 5
    SATURDAY = 6
    SUNDAY = 7

class Bits(enum.Flag):
    first   = 1
    second  = 2
    three   = 3
    third   = 4
    fourth  = 8
    fifth   = 16
    sixth   = 32
    seventh = 64
    eighth  = 128
    ninth   = 256

def main():
    first_week_day = DayOfWeek.MONDAY
    print(f"{first_week_day=}")
    print(f"{first_week_day.name=}")

    b = Bits.first | Bits.second | Bits.eighth
    print("===================")
    print(f"{b=}")
    print(f"{b.value=}")

    b = Bits.three
    print("===================")
    print(f"{b=}")
    print(f"{b.value=}")

    b = Bits.first | Bits.second
    print("===================")
    print(f"first|second: {b}")
    print(f"{b.value=}")

    day_name_from_user = "MONDAY"
    d = DayOfWeek[day_name_from_user]
    print("===================")
    print(f"{d=}")
    print(f"{d.value=}")

if __name__ == '__main__':
    main()
