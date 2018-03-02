def cellCompete(states, days):
    for day in range(days):
        new_states = []
        for i in range(0,8):
            if i != 0 and i != 7:
                if states[i-1] == states[i+1]:
                    print(i)
                    new_states.append(0)
                else:
                    new_states.append(1) 
            else:
                if i == 0 and states[i+1] == 0:
                    new_states.append(0)
                    print(i)
                elif i == 0:
                    new_states.append(1)
                if i == 7 and states[i-1] == 0:
                    new_states.append(0)
                elif i == 7:
                    new_states.append(1)
        states = new_states
    return states

if __name__ == "__main__":
    print(cellCompete([1,0,0,0,0,1,0,0],1))