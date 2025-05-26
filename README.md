## Cerințe proiect
[See here](./progress_gallery/cerinte.md)
## Setup
Installing the prerequisites, on debian based Operating Systems:
```bash
sudo apt-get update && sudo apt-get install -y \
    cmake g++ libsfml-dev
```

Clone the repository:
```bash
git clone https://github.com/voaidesr/raytracing.git
cd raytracing
```

Then run, in order to compile:
```bash
mkdir build && cd build
cmake .. && make -j
```

To execute:
```bash
./raytracer > img.ppm
```

This will enable a live display of the image generation process and simultaneously store the image in img.ppm. After the image is generated, you can open the image with any image viewer that supports the `.ppm` format (e.g., [feh](https://feh.finalrewind.org/)).

To run tests:
```bash
ctest
```
