class Node:
    def __init__(self, next=None, prev=None, cylinder=None):
        self.next = next
        self.prev = prev
        self.cylinder = cylinder

def create_list(fname, schedule):
    with open(fname, 'w') as file:
        for line in file:
            schedule.append(line)

def insert_and_get_idx(schedule, val):
    idx = 0
    #base case where insert into first element
    if schedule[0] > val:
        schedule.insert(0, val)
        return idx

    for i in range(len(schedule)):
        idx = i
        if schedule[i] < val:
            continue

    if idx == len(schedule) - 1:
        schedule.append(val)
        return idx + 1
    else:
        schedule.insert(idx, val)
        return idx


def FCFS(schedule, start):
    total = abs(start - schedule[0])
    #idx = insert_and_get_idx(schedule, start)
    idx = 0
    with open("fcfsPY.csv", "w") as file:
        while idx + 1 < len(schedule):
            file.write(str(schedule[idx]))
            file.write(",")
            total = total + abs(schedule[idx] - schedule[idx + 1])
            idx = idx + 1
        file.write(str(schedule[idx]))
    file.close()
    return total

def SSTF(schedule, start, num_cylinder):
    idx = insert_and_get_idx(schedule, start)
    total = 0
    with open("sstfPY.csv", "a") as file:
        while len(schedule) > 0:
            if len(schedule) == 1: #case where there is only one element left
                file.write(str(schedule[0]))
                file.write("\n")
                file.close()
                del schedule[0]
                return total
            elif idx + 1 == len(schedule): #case where we have hit the far right
                file.write(str(schedule[idx]))
                file.write("\n")
                total = total + abs(schedule[idx] - schedule[idx - 1])
                del schedule[idx]
                idx = idx - 1
            elif idx - 1 < 0: #
                file.write(str(schedule[idx]))
                file.write("\n")
                total = total + abs(schedule[idx] - schedule[idx + 1])
                del schedule[idx]
                idx = idx + 1
            else:
                #case right is bigger and elems on both side of idx
                if abs(schedule[idx] - schedule[idx + 1]) >= abs(schedule[idx] - schedule[idx - 1]):
                    file.write(str(schedule[idx]))
                    file.write("\n")
                    total = total + abs(schedule[idx] - schedule[idx + 1])
                    del schedule[idx]
                    idx = idx + 1
                else:
                    file.write(str(schedule[idx]))
                    file.write("\n")
                    total = total + abs(schedule[idx] - schedule[idx - 1])
                    del schedule[idx]
                    idx = idx - 1

    return total


def main():
    schedule = []
    mode = input("Please enter 1 for user interactive mode or 2 for batch mode: ")

    num_cylinder = int(input("Enter total cylinders: "))
    start = int(input("Enter starting position of disk head: "))
    size = int(input("Enter size of list: "))

    #create list in either interactive mode or batch mode
    print("Enter the cylinder values:\n")
    if mode == "1":
        for i in range(size):
            position = int(input())
            schedule.append(position)
    else:
        create_list(input("Please enter name of file: "), schedule)

    #FCFS
    fcfsList = schedule.copy()
    fcfsSum = FCFS(fcfsList, start)
    print("FCFS =", fcfsSum)

    #SSTF
    sstfList = schedule.copy()
    sstfList.sort()
    sstfSum = SSTF(sstfList, start)
    print("SSTF =", sstfSum)

main()








