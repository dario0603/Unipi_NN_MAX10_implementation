import torch
import os
from torchvision import datasets, transforms
from tqdm import tqdm

# Trasformazione: converte l'immagine in tensor float [0,1]
transform = transforms.ToTensor()

# Download dataset MNIST
mnist = datasets.MNIST(
    root="./data",
    train=True,
    download=True,
    transform=transform
)

# ===== PATH AUTOMATICO =====
# Cartella dove si trova questo script Python
current_dir = os.path.dirname(os.path.abspath(__file__))

# File output nella stessa cartella
output_file = os.path.join(current_dir, "mnist_c_vectors.txt")

# path assoluto
full_path = os.path.abspath(output_file)

print(f"Dataset esportato in: {full_path}")

with open(output_file, "w") as f:
    # tqdm con lunghezza esplicita per percentuale corretta
    for image, label in tqdm(mnist, total=len(mnist), desc="Export MNIST", unit="img"):
        
        # image shape = [1, 28, 28]
        flat = image.view(-1)

        # Converti in stringhe float stile C
        values = ", ".join(f"{x.item():.6f}f" for x in flat)

        # Scrivi nel file
        f.write(f"{{{values}}}, {label}\n")

print(f"Dataset esportato in: {output_file}")