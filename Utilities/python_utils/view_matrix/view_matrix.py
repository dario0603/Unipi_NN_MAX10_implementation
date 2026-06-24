from PIL import Image
import numpy as np
import re
import os

# ===== PATH AUTOMATICO =====
# Cartella dove si trova questo script Python
current_dir = os.path.dirname(os.path.abspath(__file__))

# File input nella stessa cartella dello script
input_file = os.path.join(current_dir, "input.txt")

# File output nella stessa cartella
output_image = os.path.join(current_dir, "output.png")

# ===== VERIFICA FILE =====
if not os.path.exists(input_file):
    print(f"Errore: file '{input_file}' non trovato")
    exit(1)

# ===== LETTURA FILE =====
with open(input_file, "r") as f:
    content = f.read()

# Rimuove virgole e caratteri 'f'
content = content.replace(",", " ")
content = re.sub(r'([0-9])f', r'\1', content)

# Converte in float
values = [float(x) for x in content.split()]

# Verifica numero elementi
if len(values) != 28 * 28:
    raise ValueError(f"Attesi 784 valori, trovati {len(values)}")

# ===== CREAZIONE IMMAGINE =====
pixels = np.array(values) * 255
pixels = pixels.astype(np.uint8)
pixels = pixels.reshape((28, 28))

# Immagine grayscale
img = Image.fromarray(pixels, mode='L')

# Salvataggio
img.save(output_image)

print(f"Immagine salvata in:\n{output_image}")