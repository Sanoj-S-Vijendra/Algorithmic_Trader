Part 1
======
1. When a new trade comes, you must first check if it is a valid trade (this is done by applying the “cancellation rules.” keep reading)
2. At any given point of time, there is a set of orders per stock (different for different stocks), let us call it S (let us assume only one stock, for now, wlog since all stocks are treated INDEPENDENTLY), which are the active orders on a particular stock (an active order is one that has not been invalidated or been traded on by you, more on this later)
3. Suppose a buy order comes in A 100 b. Another order A 120 b, exists as an active order, then this new order becomes invalid, and you must output No Trade (your strategy is irrelevant here; the output for an invalid order is No Trade). A 120 b remains as an active order. Analogously, if there was an active order A 80 b; it gets immediately cancelled since A 100 b is a better order.
4. Suppose a sell order comes in A 120 s. Another order A 100 s exists as an active order, then this new order becomes invalid, and you must output No Trade (your strategy is irrelevant here; the output for an invalid order is No Trade). A 100 s remains as an active order. Analogously, if there was an active order A 140 s; it gets immediately cancelled since A 120 s is a better order.
5. Remember, a “higher” price buy order is better, and a “lower” price sell order is better.
6. If the order has not been cancelled (Invalidated by rules 3,4) till now, check if the corresponding opposite side order exists. For instance, suppose A 100 b is the NEW order, and A 100 s exists in the set of active orders for stock A; then both A 100 b and A 100 s get cancelled (only works when the prices of both are EXACTLY THE SAME, no greater than, no less than comparisons). A 100 s does not remain an active order any more and is REMOVED from the set of active orders.
7. If none of the above apply, then the order is valid. Now, you must check if you want to take this order (based on your strategy). For instance, suppose your estimated value of the stock is 100 (assume you accepted some 100 priced trade earlier). Now, A 120 b order comes in and remains valid (is not cancelled by points 3-6 above), then you must output A 120 s.
8. Suppose you do not trade on a valid order (say A 80 b came in when your estimated price for A was 100), then A 80 b will be added to the list of active orders for stock A.
9. Move on to the next order.
10.Follow the instructions for each order until the last.
11.Note that the set of active orders for each stock at the beginning is null.

Part 2
=======
1. Instead of individual stocks, you will be working with linear combinations.
2. Two linear combinations are EXACTLY the same if the coefficients for each stock are EXACTLY the same. A 1 B 1 and B 1 A 1 are the same, but A -1 B -1 is not the same as A 1 B 1. You will NOT see input of the form A 1 B 0 C 1 D 0. This will be A 1 C 1. You can print A 1 B 1 in place of B 1 A 1 as well
3. If two linear combinations are not EXACTLY the same, then there is NO cancellation rule that applies to them. Yes, this means A -1 B -1 can never ever “cancel” A 1 B 1. They may be both used in an arbitrage cycle. The takeaway here is that every linear combination must be treated INDEPENDENTLY.
4. At any given point of time, there is a set of orders, per linear combination (different for different linear combinations), let us call it S (let us assume only one stock, for now, wlog since all stock linear combinations are treated INDEPENDENTLY), which are the active orders on a particular stock linear combination (an active order is one that has not been cancelled or been traded on by you)
5. Suppose a buy order comes in A 1 100 b. Another order A 1 120 b, exists as an active order, then this new order becomes invalid, and you must output No Trade (your strategy is irrelevant here; the output for an invalid order is No Trade). A 1 120 b remains as an active order.  Analogously, if there was an active order A 1 80 b; it gets immediately cancelled since A 1 100 b is a better order.
6. Suppose a sell order comes in A 1 120 s. Another order A 1 100 s exists as an active order, then this new order becomes invalid, and you must output No Trade (your strategy is irrelevant here; the output for an invalid order is No Trade). A 1 100 s remains as an active order. Analogously, if there was an active order A 1 140 s; it gets immediately cancelled since A 1 120 s is a better order.
7. Remember, a “higher” price buy order is better, and a “lower” price sell order is better.
8. If the order has not been cancelled(invalidated) till now, check if the corresponding opposite side order exists. For instance, suppose A 1 100 b is the NEW order, and A 1 100 s exists in the set of active orders for linear combination A 1; then both A 1 100 b and A 1 100 s get cancelled (only works when the prices of both are EXACTLY THE SAME, no greater than, no less than comparisons). A 1 100 s does not remain an active order any more and is REMOVED from the set of active orders.
9. If none of the above apply, then the order is valid. Now, you must check if you want to take this order (based on your strategy). If this order forms an arbitrage with other orders, then you must accept all these orders in reverse order in which they came. For instance, suppose there was A followed by B followed by C, and A,B,C form an arbitrage, with A and B being active orders and C being the new order, then you must output the corresponding output for C,B,A. Note that B,A will be removed from the list of active orders for their corresponding stock structures.
10.Suppose you do not trade on a valid order, then this order will be added to the list of active orders corresponding to this stock structure.
11.Move on to the next order.
12.Follow the instructions for each order until the last.
13.Note that the set of active orders for each stock linear combination at the beginning is null.
14.Note: An arbitrage is a group of trades which, do not result in any net transfer of stocks but result in leftover money with the trader.

Part 3
=======
1. Instead of individual stocks, you will be working with linear combinations and with each order being associated with a quantity and an order book.
2. Two linear combinations are EXACTLY the same if the coefficients for each stock are EXACTLY the same. A 1 B 1 and B 1 A 1 are the same, but A -1 B -1 is not the same as A 1 B 1. You will NOT see input of the form A 1 B 0 C 1 D 0. This will be A 1 C 1.
3. You can print A 1 B 1 in place of B 1 A 1 as well
4. If two linear combinations are not EXACTLY the same, then there is NO cancellation rule that applies to them. Yes, this means A -1 B -1 can never ever “cancel” A 1 B 1. They may be both used in an arbitrage cycle. The takeaway here is that every linear combination must be treated INDEPENDENTLY.
5. Suppose a buy order comes in A 1 100 1 b. Another order A 1 120 1 b, exists as an active order, then this new order remains valid.
6. Suppose a sell order comes in A 1 120 1 s. Another order A 1 100 1 s exists as an active order, then this new order remains valid.
7. If the order has not been cancelled(invalidated) till now, check if the corresponding opposite side order exists. For instance, suppose A 1 100 1 b is the NEW order, and A 1 100 1 s exists in the set of active orders for linear combination A 1; then both A 1 100 1 b and A 1 100 1 s get cancelled (only works when the prices of both are EXACTLY THE SAME, no greater than, no less than comparisons). A 1 100 1 s does not remain an active order any more and is REMOVED from the set of active orders.
8. Since we deal with quantity, suppose you have A 1 100 3 b and A 1 100 2 s, then A 1 100 1 b remains since 2 buy and 2 sell cancel each other. You can simply treat quantity=k as k lines having the same order
9. If none of the above apply, then the order is valid. Now, you must check if you want to take this order (based on your strategy). If this order forms an arbitrage with other orders, then you must accept all these orders in reverse order in which they came. For instance, suppose there was A followed by B followed by C, and A,B,C form an arbitrage, with A and B being active orders and C being the new order, then you must output the corresponding output for C,B,A. Note that B,A will be removed from the list of active orders for their corresponding stock structures. (Read the point below)
10.Since you are dealing with multiple quantities, there are multiple ways to print/accept an arbitrage.
11.Suppose you do not trade on a valid order, then this order will be added to the list of active orders corresponding to this stock structure.
12.Move on to the next order.
13.Follow the instructions for each order until the last.
14.Note that the set of active orders for each stock linear combination at the beginning is null.
15.Note: If A 1 100 3 b and  A 1 100 2 b are both active orders, then you can “add” them up to become A 1 100 5 b, even if they are not consecutive.



