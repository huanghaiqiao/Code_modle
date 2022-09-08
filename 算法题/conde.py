# 合并两个有序列表，圈复杂度为O(n)
def combine_two_sorted_arr(list_a,list_b):
    i,j = 0, 0
    list_c = []
    while(i < len(list_a) and j < len(list_a)):
        if list_a[i] >= list_b[j]:
            list_c.append(list_b[j])
            j += 1
        else :
            list_c.append(list_a[i])
            i+= 1

    if i == len(list_a):
        for index in range(j,len(list_b)):
            list_c.append(list_b[index])
    else:
        for index in range(i,len(list_a)):
            list_c.append(list_a[index])
    
    return list_c

if __name__ == "__main__":
    list_a = [2, 3, 5, 7, 9]
    list_b = [2, 6, 9, 10, 11, 18]    
    print(combine_two_sorted_arr(list_a, list_b))
