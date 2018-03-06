states = [1,2,3]
transitions = {
    # Labeled edges coming out of 1
    1 :
        {
            'a':2, # 1 ---a---> 2
            'b':3, # 1 ---b---> 3
            'c':1, # 1 ---c---> 1
        },
    2 :
        {
            'a': 1,
            'b': 2,
            'c': 3,
        },
    3:
        {
            'a': 1,
            'b': 2,
            'c': 3,
        }
}

def transition(current_state, inp):
    ''' Apply transition map or stay on current_state if there is no
    transition '''
    try:
        return transitions[current_state][inp]
    except KeyError:
        return current_state

class StateMachine:
    ''' Just a class having a self.state attribute and a consume input method'''
    def __init__(self):
        self.state = 1
    def consume_input(self, inp):
        self.state = transition(self.state, inp)


if __name__ == '__main__':
    m = StateMachine()
    inp = 0
    while inp != 'q':
        previous_state = m.state
        inp = input("Please input letter a-c or q to quit")
        m.consume_input(inp)
        print(inp + ' : ' + str(previous_state) + ' ---' + inp + '---> '
              + str(m.state))