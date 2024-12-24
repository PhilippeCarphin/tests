#!/usr/bin/env python3
import argparse
import subprocess
import io
import sys
import os

DESCRIPTION = """
Tool to send email from MacOS command line using Mail.app.

Syntax is similar to the UNIX tool 'mail':
- message is read from stdin (for this tool this is the only option)
- subject is specified as '-s subject'
- recipient is the only positional argument

Additionnally, the sender can be specified and must be one of the senders
available in Mail.app otherwise the default sender from Mail.app is used
without warning."""


def get_args():
    p = argparse.ArgumentParser( description=DESCRIPTION, formatter_class=argparse.RawTextHelpFormatter)
    p.add_argument('-s', '--subject', help="subject", required=True)
    p.add_argument( '-f', '--sender', help="Sender", default="phil103@hotmail.com")
    p.add_argument('-a', '--attach', help="File attachment", action='append')
    p.add_argument('-v', '--verbose', action='store_true')
    p.add_argument( '-w', '--wait', action='store_true', help="Don't send the message")
    p.add_argument('--show-script', action='store_true', help="Just show the generated script")
    p.add_argument('to_addr', nargs='+')

    args = p.parse_args()
    if not args.attach:
        args.attach = []

    return args


def main():

    args = get_args()
    for f in args.attach:
        if not is_valid_for_mail(f):
            return 1

    if sys.stdin.isatty():
        print("Reading message from STDIN, hit C-d on an empty line when finished, C-c to abort")

    content = sys.stdin.read()

    script = make_apple_script(args, content)

    if args.verbose or args.show_script:
        print(f"Apple script: \n\033[36m{script}\033[0m")
        if args.show_script:
            return 0

    # Maybe I should just show an error if it's not running
    ensure_mail_is_running()

    return run_apple_script(script)


def attachment_to_osascript(filename):
    return f"make new attachment with properties {{file name: \"{os.path.abspath(filename)}\"}} at after last paragraph"


def recipient_to_osascript(recipient):
    return f"make new to recipient with properties {{address:\"{recipient}\"}}"


def make_apple_script(args, content):
    def escape(s): return s.replace("\\", "\\\\").replace('"', '\\"')
    # Note: It seems like attachment paths must be absolute
    attachments = '\n                '.join([attachment_to_osascript(a) for a in args.attach])
    # ¬ = \u00ac is the line continuation character for Apple Script
    recipients = '\n                '.join([ recipient_to_osascript(r) for r in args.to_addr])
    return f"""
        tell application "Mail"
            set theMessage to make new outgoing message with properties {{¬
                visible:{"true" if args.wait else "false"},¬
                subject:"{escape(args.subject)}",¬
                content:"{escape(content)}",¬
                sender:"{args.sender}"¬
            }}
            tell theMessage
                {attachments}
                {recipients}
                delay 1
            end tell
            {"send theMessage" if not args.wait else ""}
        end tell
    """


def is_valid_for_mail(f):

    if not os.path.exists(f):
        print(f"Attachment (-a,--attach) '{f}': No such file or directory")
        return False

    # Doing links makes the mail app crash
    if os.path.islink(f):
        print(f"Attachment (-a,--attach) '{f}': Is a link (would make Mail.app crash)")
        return False

    # Directories just don't work
    if os.path.isdir(f):
        print(f"Attachment (-a,--attach) '{f}': Is a directory")
        return False

    # Catch other case I may not have thought of with islink and isdir
    if not os.path.isfile(f):
        print(f"Attachment (-a,--attach) '{f}' is not a regular file")
        return False

    return True


def ensure_mail_is_running():
    script = """
        if application "Mail" is not running
            run application "Mail"
        end if
    """
    subprocess.run(["/usr/bin/osascript", "-e", script])


def run_apple_script(script):
    p = subprocess.run(
        ["/usr/bin/osascript", "-e", script],
        universal_newlines=True,
        stdout=subprocess.PIPE
    )
    if p.stdout.strip() != 'true':
        print(f"Expected stdout of 'true' from email-sending script but got '{p.stdout.strip()}'")
        return 1
    return p.returncode


if __name__ == "__main__":
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        sys.exit(130)
