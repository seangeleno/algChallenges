def generalizedGCD(num, arr):
    GCD = 1
    for i in range(num):
        if arr[i] % GCD == 0:
            candidate = arr[i]
            flag = 0
            for j in range(num):
                if arr[j] % candidate != 0:
                    flag = 1
            if arr[i] > GCD and flag == 0:
                GCD = candidate
    return GCD


if __name__ == "__main__":
    print(generalizedGCD(5,[2,4,6,8,10]))