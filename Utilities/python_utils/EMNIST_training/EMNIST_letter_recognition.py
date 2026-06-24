import os
import numpy as np
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
import torch.nn.functional as F

from torchvision import datasets, transforms
from torch.utils.data import DataLoader
from tqdm import tqdm

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

if torch.cuda.is_available():
    print("Using CUDA")
else:
    print("Using CPU")

transform = transforms.ToTensor()

train_dataset = datasets.EMNIST(
    root="./data",
    split="byclass",
    train=True,
    download=True,
    transform=transform
)

test_dataset = datasets.EMNIST(
    root="./data",
    split="byclass",
    train=False,
    download=True,
    transform=transform
)

train_loader = DataLoader(train_dataset, batch_size=256, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=2000, shuffle=False)

"""
def transform_image(x, rotate=1, mirror=1):
    # x: [B, 1, 28, 28] or [1, 28, 28]

    # remove channel dimension
    x = x.squeeze(1)  # -> [B, 28, 28]

    # clockwise rotation
    if rotate > 0:
        x = torch.rot90(x, k=(4 - (rotate % 4)), dims=(1, 2))

    # horizontal flip (mirror)
    if mirror == 1:
        x = torch.flip(x, dims=[2])

    # add channel back
    x = x.unsqueeze(1)

    return x
"""

def transform_image(x, rotate=1, mirror=1, scale=0.9):
    # x: [B, 1, 28, 28]

    B = x.size(0)

    # ===== ROTAZIONE =====
    if rotate > 0:
        x = torch.rot90(x, k=(4 - (rotate % 4)), dims=(2, 3))

    # ===== MIRROR =====
    if mirror == 1:
        x = torch.flip(x, dims=[3])

    # ===== SCALING =====
    new_size = int(28 * scale)   # 25 se scale=0.9

    # ridimensiona immagine
    x_small = F.interpolate(
        x,
        size=(new_size, new_size),
        mode='bilinear',
        align_corners=False
    )

    # canvas nero 28x28
    x_out = torch.zeros((B, 1, 28, 28), device=x.device)

    # centra immagine
    start = (28 - new_size) // 2

    x_out[:, :, start:start+new_size, start:start+new_size] = x_small

    return x_out

class Net1(nn.Module):
    def __init__(self):
        super(Net1, self).__init__()
        
        #input matrix 28x28 
        self.fc1 = nn.Linear(784, 1024)
        self.fc2 = nn.Linear(1024, 512)
        self.fc3 = nn.Linear(512, 256)
        self.fc4 = nn.Linear(256, 128)

        #output vector of 62 numbers
        self.fc5 = nn.Linear(128, 62)

    # x represents our data
    def forward(self, x):
        
        x = torch.flatten(x, 1)

        x = F.leaky_relu(self.fc1(x))
        x = F.leaky_relu(self.fc2(x))
        x = F.leaky_relu(self.fc3(x))
        x = F.leaky_relu(self.fc4(x))

        x = self.fc5(x)
        
        return x

class Net2(nn.Module):
    def __init__(self):
        super(Net2, self).__init__()
        
        #input matrix 28x28 
        self.fc1 = nn.Linear(784, 1024)
        self.fc2 = nn.Linear(1024, 512)

        #output vector of 62 numbers
        self.fc3 = nn.Linear(512, 62)

    # x represents our data
    def forward(self, x):
        
        x = torch.flatten(x, 1)

        x = F.leaky_relu(self.fc1(x))
        x = F.leaky_relu(self.fc2(x))

        x = self.fc3(x)
        
        return x

#model = Net1().to(device)
model = Net2().to(device) 

loss_fn = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

def train(model, loader, loss_fn, optimizer):
    model.train()

    total_loss = 0

    # tqdm wrapper
    pbar = tqdm(
        loader,
        desc=f"Epoch {epoch+1}",
        dynamic_ncols=True,
        colour="green"
    )

    for batch_idx, (x, y) in enumerate(pbar):

        x = x.to(device)
        y = y.to(device)
        
        y = y.long()

        # ===== DATA AUGMENTATION =====
        x = transform_image(x, rotate=1, mirror=1)

        optimizer.zero_grad()

        # forward
        pred = model(x)

        # loss
        loss = loss_fn(pred, y)

        # backward
        loss.backward()

        # update pesi
        optimizer.step()

        total_loss += loss.item()

        avg_loss = total_loss / (batch_idx + 1)
        pbar.set_postfix({
            "batch_loss": f"{loss.item():.4f}",
            "avg_loss": f"{avg_loss:.4f}"
        })

    return total_loss / len(loader)

def test(model, loader):
    model.eval()

    correct = 0
    total = 0

    with torch.no_grad():
        for x, y in loader:

            x = x.to(device)
            y = y.to(device)

            # ===== DATA AUGMENTATION =====
            x = transform_image(x, rotate=1, mirror=1)

            pred = model(x)
            predicted = torch.argmax(pred, dim=1)

            correct += (predicted == y).sum().item()
            total += y.size(0)

    accuracy = correct / total
    return accuracy

initial_acc = test(model, test_loader)
print("Accuracy before training:", initial_acc)

epochs = 30

train_losses = []
test_accuracies = []

for epoch in range(epochs):
    train_loss = train(model, train_loader, loss_fn, optimizer)
    test_acc = test(model, test_loader)

    train_losses.append(train_loss)
    test_accuracies.append(test_acc)

    print(f"Epoch {epoch+1}: loss={train_loss:.4f}, accuracy={test_acc:.4f}")

for name, param in model.named_parameters():
    print(name)
    print(param)
    print("-" * 50)

print("Saving weights...")

np.set_printoptions(threshold=np.inf)

save_path = os.path.join(os.path.dirname(__file__), "weights.txt")

with open(save_path, "w") as f:
    for name, param in model.named_parameters():
        print("writing:", name)  # debug

        array = param.detach().cpu().numpy().flatten()

        c_name = name.replace('.', '_')
        size = len(array)

        f.write(f"static const float {c_name}[{size}] = {{\n    ")

        for i, x in enumerate(array):
            f.write(f"{x:.6f}f")

            if i != size - 1:
                f.write(", ")

            # nuova riga ogni 8 elementi
            if (i + 1) % 8 == 0:
                f.write("\n    ")

        f.write("\n};\n\n")

print("DONE. File saved in:", save_path)

# ===== GRAPH =====

epochs_range = range(1, epochs + 1)

plt.figure(figsize=(10, 5))

# accuracy
plt.plot(epochs_range, test_accuracies, marker='o', label='Test Accuracy')

# loss
plt.plot(epochs_range, train_losses, marker='s', label='Train Loss')

plt.xlabel("Epoch")
plt.ylabel("Value")
plt.title("Training Metrics")
plt.legend()
plt.grid(True)

graph_path = os.path.join(os.path.dirname(__file__), "graph.png")

plt.savefig(graph_path)
plt.close()

print("Graph saved in:", graph_path)
