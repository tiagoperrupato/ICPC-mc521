def max_activities(activities):
    # Sort by finish time
    activities.sort(key=lambda x: x[1])
    
    count = 0
    last_finish = 0
    
    for start, end in activities:
        if start > last_finish:
            count += 1
            last_finish = end
    
    return count

# Reading input
n = int(input())
activities = [tuple(map(int, input().split())) for _ in range(n)]

# Output result
print(max_activities(activities))