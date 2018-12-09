import smtplib
from email.message import EmailMessage
import getpass
import sys

try:
    with open('./.addresses') as f:
        lines = list(map(lambda l: l.strip(), f.readlines()))
        from_address = lines[0]
        to_address = lines[1]
except Exception:
    print("There must be a file in PWD called .addresses two lines each containing an email address")
    sys.exit(1)

from_smtp = 'smtp-mail.outlook.com'
password = getpass.getpass('Say password for user {} : '.format(from_address))

try:
    message_content = sys.argv[1]
except IndexError:
    print("ERROR: Message must be given as argument")
    sys.exit(1)

my_message = EmailMessage()
my_message.set_content(message_content)
my_message['Subject'] =  'Subject of message'
my_message['From'] = from_address
my_message['To'] = to_address

s = smtplib.SMTP(from_smtp, 587 )
s.ehlo()
s.starttls()
s.ehlo()
s.login(from_address, password)

s.sendmail(from_address, to_address, my_message.as_string())
s.quit()
