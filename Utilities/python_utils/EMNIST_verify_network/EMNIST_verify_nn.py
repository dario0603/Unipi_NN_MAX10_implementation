import os
import re
import numpy as np

import torch
import torch.nn as nn
import torch.nn.functional as F

from PIL import Image

CLASS_LABELS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

# =========================
# NETWORK
# =========================

class Net(nn.Module):

    def __init__(self):
        super(Net, self).__init__()

        self.fc1 = nn.Linear(784, 1024)
        self.fc2 = nn.Linear(1024, 512)
        self.fc3 = nn.Linear(512, 62)

    def forward(self, x):

        x = torch.flatten(x, 1)

        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))

        x = self.fc3(x)

        return x


# =========================
# PARSE C ARRAYS
# =========================

def extract_array(text, array_name):

    pattern = rf"static const float {array_name}\[.*?\]\s*=\s*\{{(.*?)\}};"

    match = re.search(pattern, text, re.S)

    if not match:
        raise ValueError(f"Array {array_name} non trovato")

    raw = match.group(1)

    raw = raw.replace('\n', ' ')
    raw = raw.replace('f', '')

    values = [float(x.strip()) for x in raw.split(',') if x.strip()]

    return np.array(values, dtype=np.float32)


# =========================
# LOAD WEIGHTS
# =========================

def load_weights(model, weights_file):

    with open(weights_file, "r") as f:
        text = f.read()
    
    fc1_weight = extract_array(text, "fc1_weight").reshape(1024, 784)
    fc1_bias   = extract_array(text, "fc1_bias")

    fc2_weight = extract_array(text, "fc2_weight").reshape(512, 1024)
    fc2_bias   = extract_array(text, "fc2_bias")

    fc3_weight = extract_array(text, "fc3_weight").reshape(62, 512)
    fc3_bias   = extract_array(text, "fc3_bias")

    with torch.no_grad():

        model.fc1.weight.copy_(torch.tensor(fc1_weight))
        model.fc1.bias.copy_(torch.tensor(fc1_bias))

        model.fc2.weight.copy_(torch.tensor(fc2_weight))
        model.fc2.bias.copy_(torch.tensor(fc2_bias))

        model.fc3.weight.copy_(torch.tensor(fc3_weight))
        model.fc3.bias.copy_(torch.tensor(fc3_bias))


# =========================
# LOAD INPUT
# =========================

def load_input(input_file):

    if not os.path.exists(input_file):
        print(f"Error: file '{input_file}' not found")
        exit(1)

    with open(input_file, "r") as f:
        content = f.read()

    content = content.replace(",", " ")
    content = re.sub(r'([0-9])f', r'\1', content)

    values = [float(x) for x in content.split()]

    if len(values) != 28 * 28:
        raise ValueError(f"Attended 784 values, found {len(values)}")

    return torch.tensor(values)

# =========================
# LOAD EXPECTED OUTPUT
# =========================

def load_expected_output(output_file):

    if not os.path.exists(output_file):
        print(f"Error: file '{output_file}' not found")
        exit(1)

    with open(output_file, "r") as f:
        content = f.read()

    # remove unwanted chars
    content = content.replace(",", " ")
    content = content.replace("f", "")
    content = content.replace("{", " ")
    content = content.replace("}", " ")
    content = content.replace("[", " ")
    content = content.replace("]", " ")

    values = [float(x) for x in content.split()]

    if len(values) != 62:
        raise ValueError(f"Expected 62 output values, found {len(values)}")

    return torch.tensor(values, dtype=torch.float32)

# =========================
# MAIN
# =========================

if __name__ == "__main__":

    base_dir = os.path.dirname(os.path.abspath(__file__))

    weights_path = os.path.join(base_dir, "weight_matrix.txt")
    input_path = os.path.join(base_dir, "input.txt")
    output_path = os.path.join(base_dir, "output.txt")

    model = Net()

    print("Loading weights...")
    load_weights(model, weights_path)

    print("Loading input...")
    x = load_input(input_path).unsqueeze(0)

    pixels = np.array(x) * 255
    pixels = pixels.astype(np.uint8)
    pixels = pixels.reshape((28, 28))
    img = Image.fromarray(pixels, mode='L')
    scale = 10
    img = img.resize((28 * scale, 28 * scale), Image.NEAREST)

    img.show()

    print("Loading expected output...")
    expected_output = load_expected_output(output_path).unsqueeze(0)

    print("Running inference...")

    model.eval()

    with torch.no_grad():

        output = model(x)

        probabilities = F.softmax(output, dim=1)

        predicted_class = torch.argmax(probabilities, dim=1)

        # difference
        error = output - expected_output

    print("\nProbabilities:")
    print(probabilities)

    print("\nPredicted class:")
    print(predicted_class.item())
    print("Corresponding character:")
    print(CLASS_LABELS[predicted_class.item()])

    print("\nRaw output:")
    print(output)

    print("\nExpected output:")
    print(expected_output)

    print("\nOutput error:")
    print(error)