import torch
import os
from torchvision import datasets, transforms
from tqdm import tqdm

# ===== PARAMETRI AUGMENTATION =====
ruota = 1       # numero rotazioni 90° in senso orario
specchia = 1    # 1 = specchia dopo rotazione, 0 = no

# Trasformazione base
transform = transforms.ToTensor()

# Dataset EMNIST
emnist = datasets.EMNIST(
    root="./data",
    split="byclass",
    train=True,
    download=True,
    transform=transform
)

# ===== PATH OUTPUT =====
current_dir = os.path.dirname(os.path.abspath(__file__))
output_file = os.path.join(current_dir, "emnist_c_vectors.txt")
full_path = os.path.abspath(output_file)

print(f"Dataset esportato in: {full_path}")

with open(output_file, "w") as f:
    for image, label in tqdm(emnist, desc="Export EMNIST", unit="img"):

        # image shape = [1, 28, 28]
        img = image.squeeze(0)  # [28, 28]

        # ===== ROTAZIONE (clockwise) =====
        # torch.rot90 ruota in senso anti-orario,
        # quindi per orario usiamo 4 - k
        if ruota > 0:
            img = torch.rot90(img, k=(4 - (ruota % 4)), dims=(0, 1))

        # ===== SPECCHIO =====
        if specchia == 1:
            img = torch.flip(img, dims=[1])  # flip orizzontale

        # Flatten -> 784
        flat = img.reshape(-1)

        # formato C float
        values = ", ".join(f"{x.item():.6f}f" for x in flat)

        # scrittura
        f.write(f"{{{values}}}, {label}\n")

print(f"Dataset esportato in: {output_file}")