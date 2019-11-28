import sys

print(sys.argv)

#  item-id, name, price, quantity-ordered
#  1,shampoo,20,30|2,beta,60,44

# print(sys.argv[1].split(|))

for item_ordered in sys.argv[1].split('|'):
    print(item_ordered.split(','))