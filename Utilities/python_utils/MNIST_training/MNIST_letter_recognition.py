import os
import numpy as np
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
import torch.nn.functional as F

from torchvision import datasets, transforms
from torch.utils.data import DataLoader
from tqdm import tqdm

transform = transforms.ToTensor()

train_dataset = datasets.MNIST(
    root="./data",
    train=True,
    download=True,
    transform=transform
)

test_dataset = datasets.MNIST(
    root="./data",
    train=False,
    download=True,
    transform=transform
)

train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=1000, shuffle=False)

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        
        #input matrix 28x28 
        self.fc1 = nn.Linear(784, 256)
        self.fc2 = nn.Linear(256, 128)
        #output vector of 10 numbers
        self.fc3 = nn.Linear(128, 10)

    # x represents our data
    def forward(self, x):
        
        x = torch.flatten(x, 1)

        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))

        x = self.fc3(x)
        
        return x

model = Net() 

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
