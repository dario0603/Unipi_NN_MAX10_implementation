import numpy as np

# Parameters
LUT_SIZE = 1024
MIN_VAL_FLOAT = 0.00005

# Functions
def sigmoid_fn(x):
    return np.where(x >= 0,
                    1/(1+np.exp(-x)),
                    np.exp(x)/(1+np.exp(x)))

def tanh_fn(x):
    return np.tanh(x)

#Find the right x0 value for sigmoid function
x1 = 0.0
while True:
    dif = 1.0 - sigmoid_fn(x1)

    if abs(dif) < MIN_VAL_FLOAT:
        break

    x1 += 0.1

print("sigmoid", round(x1,4), "\n")

#Find the right x0 value for tanh function
x2 = 0.0
while True:
    dif = 1.0 - tanh_fn(x2)

    if abs(dif) < MIN_VAL_FLOAT:
        break

    x2 += 0.1

print("tanh", round(x2,4), "\n")

# Generate x axis
xtanh = np.linspace(-x2, x2, LUT_SIZE)
xsigm = np.linspace(-x1, x1, LUT_SIZE)

sigmoid = sigmoid_fn(xsigm)
tanh = tanh_fn(xtanh)

# Function to print C arrays
def print_c_array(name, data):
    print(f"static const float {name}[{len(data)}] = {{")
    for i, v in enumerate(data):
        print(f"    {v:.6f}f,", end="")
        if (i + 1) % 8 == 0:
            print()
    print("\n};\n")

# Output
print_c_array("sigmoid_lut", sigmoid)
print_c_array("tanh_lut", tanh)
