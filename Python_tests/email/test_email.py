#!/usr/bin/env python3
import smtplib
from email.message import EmailMessage
import getpass
import sys

def make_message_object(origin, destination, subject, content):
    m = EmailMessage()
    m.set_content(content)
    m['Subject'] = subject
    m['From'] = origin
    m['To'] = destination
    return m

def make_hotmail_connection():
    from_smtp = 'smtp-mail.outlook.com'
    from_address = 'phil103@hotmail.com'
    password = getpass.getpass('Say password for user {} : '.format(from_address))

    s = smtplib.SMTP(from_smtp, 587 )
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(from_address, password)
    return s

def send_mail(origin, destination, subject, content):
    message = make_message_object(origin, destination, subject, content)
    hc = make_hotmail_connection()
    hc.send_message(message, origin, destination)
    hc.quit()


def test_send_mail():
    send_mail("phil103@hotmail.com", "pcarphin@gmail.com", "el subjecto", "el contento")


def send_cmc_command():
    import sys
    usage = "Fist argument : subject\nSecondArgument : content\n\n Message will be sent to my CMC address from my hotmail address"
    subject = ""
    content = ""
    try:
        subject = sys.argv[1]
    except IndexError:
        print("send_mail ERROR: Missing argument\n\n" + usage)
        quit()

    try:
        content = sys.argv[2]
    except IndexError:
        print("send_mail ERROR: Missing argument\n\n" + usage)
        quit()

    send_mail(
        "phil103@hotmail.com",
        "pcarphin@gmail.com",
        subject, content)

def resolve_nicknames(potential_nickname):
    if potential_nickname in addresses:
        return addresses[potential_nickname]

addresses = {
    "cmc": "philippe.carphin2@canada.ca",
    "hotmail": "phil103@hotmail.com",
    "poly": "philippe.carphin@polymtl.ca"
    }
def test_send_cmc_command():
    send_cmc_command()
if __name__ == "__main__":
    # test_send_mail()
    test_send_cmc_command()
