# Josephus problem #

- N people form a circle, eliminate a person every k people
- Label each person with 0, 1, 2, …, n-1, denote J(n, k) the labels of survivors when there are n people 
- First eliminate the person labeled k-1, re-label the rest, starting with 0 for the one originally labeled k
0, 1, 2, 3, …k-2, k-1, k, k+1,… n-1
   …            k-2,        0, 1 …
- Dynamic programming
J(n, k) = (J(n-1, k) + k) % n, if n > 1,
J(1, k) = 0
- We may implement this with iterations in O(n) time
