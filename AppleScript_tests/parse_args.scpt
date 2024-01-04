#!/usr/bin/env osascript

on run argv

    if item 1 of argv is "something"
        log "argv1 is indeed something"
    else
        log "argv1 is not something but is in fact " & item 1 of argv
    end if

    if item 2 of argv is not "the thing"
        log "argv2 is actually not the thing, in fact it is " & item 2 of argv
    end if

    log "argv3 = " & (item 3 of argv)

end run
