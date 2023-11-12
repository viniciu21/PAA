def bin_packing_dynamic_programming(weights, bin_capacity):
    n = len(weights)
    dp = [[float('inf')] * (bin_capacity + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        dp[i][0] = 0

    for i in range(1, n + 1):
        for j in range(1, bin_capacity + 1):
            dp[i][j] = dp[i - 1][j]
            if j >= weights[i - 1]:
                dp[i][j] = min(dp[i][j], 1 + dp[i][j - weights[i - 1]])

    # Backtracking to find the items in each bin
    bins_used = []
    i, j = n, bin_capacity
    while i > 0 and j > 0:
        if dp[i][j] == dp[i - 1][j]:
            i -= 1
        else:
            bins_used.append(i - 1)
            j -= weights[i - 1]

    bins_used.reverse()  # Reverse to get the correct order of items in each bin
    return dp[n][bin_capacity], bins_used

# Example usage:
weights = [2, 5, 4, 7, 1, 3, 8]
bin_capacity = 10
result, bins_used = bin_packing_dynamic_programming(weights, bin_capacity)
print("Minimum number of bins:", result)
print("Items in each bin:", bins_used)
