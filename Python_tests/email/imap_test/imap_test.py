import easyimap
import getpass

# Working demo of getting email with python.
# Tested on imac with python2.
# With Python3, I could not get it to find the modula easyimap
# even though I pip3 installed it with pip3.5, pip3.7
# and tried a bunch of other stuff.

login = 'phil103@hotmail.com'

password = getpass.getpass("enter password for user {} : ".format(login))

imapper = easyimap.connect('imap-mail.outlook.com', login, password)

def save_kifu_mail_to_file(kifu_mail):
    game_name = '_'.join(mail.title.split()[2:])
    if game_name == '':
        game_name = 'fallback_name'
    print("WE HAVE A GAME!")
    print(game_name)
    print(mail.body)

for mail_id in imapper.listids(limit=10):
    mail = imapper.mail(mail_id)
    print(mail.from_addr)
    print(mail.title)

    # The intention is to have this on a raspberry pi to
    # get the kifu in recent emails and save them to files automatically
    if mail.title.startswith('GoQuest Kifu'):
        save_kifu_mail_to_file(mail)
