import notify2
notify2.init('app name')
n = notify2.Notification("Summary",
                         "Some body text",
                         "notification-message-im"   # Icon name
                        )
n.show()

while 1:
    pass
