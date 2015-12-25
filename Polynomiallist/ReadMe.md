# Polynomial multiplication #
- If sorted, we know where to insert later items (following the current node), search takes O(n^2)
- If not sorted, insert starts from the list head, search takes O(n^3)
- For example, f(x) = x3 + x2 + x + 1, g(x) = x3 + x2 + x + 1, to get f(x)*g(x)
- First let x3 *g(x), we have H-> x6 -> x5 -> x4 -> x3, always insert into the end, n insertions
- Then add to above x2 *g(x), H-> x6 -> 2x5 -> 2x4 -> 2x3 -> x2 , n+1 additions/insertion
- ∑(n + (n + 1) + … + (2n – 1)) = O (n^2)
